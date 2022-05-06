using Avalonia;
using Avalonia.Collections;
using Avalonia.Controls;
using Avalonia.Controls.PanAndZoom;
using Avalonia.Input;
using Avalonia.Markup.Xaml;
using Avalonia.VisualTree;
using JetBrains.Annotations;
using Oedon.Core.UI.ViewModels;

namespace Oedon.Core.UI.Controls;

public partial class Blueprint : UserControl
{
    public Blueprint()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }
    
    #region SelectedNodes

    public static readonly DirectProperty<Blueprint, IList<BlueprintNodeVM>> SelectedNodesProperty =
        AvaloniaProperty.RegisterDirect<Blueprint, IList<BlueprintNodeVM>>(
            nameof(SelectedNodes),
            o => o.SelectedNodes,
            (o, v) => o.SelectedNodes = v);

    private IList<BlueprintNodeVM> _selectedNodes = new AvaloniaList<BlueprintNodeVM>();

    public IList<BlueprintNodeVM> SelectedNodes
    {
        get => _selectedNodes;
        set => SetAndRaise(SelectedNodesProperty, ref _selectedNodes, value);
    }
    #endregion
    
    #region SelectedConnections

    public static readonly DirectProperty<Blueprint, IList<BlueprintConnectionVM>> SelectedConnectionsProperty =
        AvaloniaProperty.RegisterDirect<Blueprint, IList<BlueprintConnectionVM>>(
            nameof(SelectedConnections),
            o => o.SelectedConnections,
            (o, v) => o.SelectedConnections = v);

    private IList<BlueprintConnectionVM> _selectedConnections = new AvaloniaList<BlueprintConnectionVM>();

    public IList<BlueprintConnectionVM> SelectedConnections
    {
        get => _selectedConnections;
        set => SetAndRaise(SelectedConnectionsProperty, ref _selectedConnections, value);
    }
    #endregion

    protected override void OnPointerReleased(PointerReleasedEventArgs e)
    {
        if (DataContext is not BlueprintDocumentVM documentVm)
        {
            return;
        }

        if (SelectedConnections.Any())
        {
            var connectionVm = SelectedConnections[0];
            
            // Probe under our cursor for a pin
            var control = HitTestFirstOf(e, a => a.DataContext is BlueprintPinVM);

            if (control?.DataContext is BlueprintPinVM belowPinVm)
            {
                BlueprintPinVM startingPinVm = null;

                if (belowPinVm.PinType == BlueprintPinType.Input &&
                    connectionVm.OutputPin is not null)
                {
                    startingPinVm = connectionVm.OutputPin;
                }
                else if (belowPinVm.PinType == BlueprintPinType.Output &&
                         connectionVm.InputPin is not null)
                {
                    startingPinVm = connectionVm.InputPin;
                }
                
                // Check if something is wrong
                if (startingPinVm is not null && 
                    
                    // Check for Self-cest (which is very bad)
                    startingPinVm.Parent != belowPinVm.Parent &&
                    
                    // Check with each pin to see if they want to connect with each other
                    startingPinVm.AllowConnection(belowPinVm) &&
                    belowPinVm.AllowConnection(startingPinVm))
                {
                    // The pin we just dropped on had a connection already so destroy it
                    if (belowPinVm.Connection is not null)
                    {
                        DestroyConnection(belowPinVm.Connection);
                    }
                    
                    belowPinVm.Connection = connectionVm;

                    switch (belowPinVm.PinType)
                    {
                        case BlueprintPinType.Input:
                            connectionVm.InputPin = belowPinVm;
                            break;
                        case BlueprintPinType.Output:
                            connectionVm.OutputPin = belowPinVm;
                            break;
                    }
                    
                    SelectedConnections.Clear();
                    
                    return;
                }
            }
            
            DestroyConnection(connectionVm);
        }
    }

    protected override void OnPointerMoved(PointerEventArgs e)
    {
        // Only care if we are left clicking
        if (!e.GetCurrentPoint(null).Properties.IsLeftButtonPressed)
        {
            return;
        }
        
        // Get the cursor relative to the zoomed in Canvas
        var newClickPos = e.GetPosition(_canvas);
        var delta = newClickPos - _clickPos;

        if (SelectedConnections.Any())
        {
            var connectionVm = SelectedConnections[0];

            if (connectionVm.OutputPin is not null)
            {
                connectionVm.InputPos = newClickPos;
            }
            else
            {
                connectionVm.OutputPos = newClickPos;
            }
        }
        else if (SelectedNodes.Any())
        {
            foreach (var node in SelectedNodes)
            {
                node.XPos += delta.X;
                node.YPos += delta.Y;

                if (node.InputPins is not null)
                {
                    foreach (var pinVm in node.InputPins)
                    {
                        if (pinVm.Connection is not null)
                        {
                            pinVm.Connection.InputPos += delta;
                        }
                    }
                }

                if (node.OutputPins is not null)
                {
                    foreach (var pinVm in node.OutputPins)
                    {
                        if (pinVm.Connection is not null)
                        {
                            pinVm.Connection.OutputPos += delta;
                        }
                    }
                }
            }
        }

        _clickPos = newClickPos;
    }

    protected override void OnPointerPressed(PointerPressedEventArgs e)
    {
        if (DataContext is not BlueprintDocumentVM documentVm)
        {
            return;
        }
        
        if (!e.GetCurrentPoint(null).Properties.IsLeftButtonPressed)
        {
            return;
        }

        // If there are already selected nodes then clear them
        if (SelectedNodes.Any())
        {
            SelectedNodes.Clear();
        }

        if (SelectedConnections.Any())
        {
            SelectedConnections.Clear();
        }

        // Find a Node or Pin under our cursor
        var control = HitTestFirstOf(e, a => a.DataContext is BlueprintNodeVM || 
                                             a.DataContext is BlueprintPinVM);
        
        // Get the cursor relative to the zoomed in Canvas
        _clickPos = e.GetPosition(_canvas);
        
        if (control is not null)
        {
            // Was it a Node?
            if (control.DataContext is BlueprintNodeVM nodeVm)
            {
                SelectedNodes.Add(nodeVm);

                _offset = e.GetPosition(control);
            }
            // Was it a Pin?
            else if (control.DataContext is BlueprintPinVM pinVm)
            {
                // Check if there is a connection already on that pin and destroy it
                if (pinVm.Connection is not null)
                {
                    DestroyConnection(pinVm.Connection);
                }
                
                // Make a new connection
                BlueprintConnectionVM connectionVm = new();
                
                // Set both points to our cursor location
                connectionVm.OutputPos = _clickPos;
                connectionVm.InputPos = _clickPos;

                switch (pinVm.PinType)
                {
                    case BlueprintPinType.Input:
                        connectionVm.InputPin = pinVm;
                        break;
                    case BlueprintPinType.Output:
                        connectionVm.OutputPin = pinVm;
                        break;
                }

                pinVm.Connection = connectionVm;
                
                documentVm.BlueprintItems.Add(connectionVm);
                
                SelectedConnections.Add(connectionVm);
            }
            
        }
    }

    private Point GetRootCoords(PointerEventArgs e)
    {
        var root = (TopLevel)this.GetVisualRoot();
        return e.GetPosition(root);
    }
    
    [CanBeNull]
    private IEnumerable<IVisual> HitTestBelow(PointerEventArgs e)
    {
        var root = (TopLevel)this.GetVisualRoot();

        return root.Renderer.HitTest(GetRootCoords(e), root, null);
    }

    [CanBeNull]
    private IControl HitTestFirstOf(PointerEventArgs e, Func<IControl, bool> pred)
    {
        return HitTestBelow(e)?.Cast<IControl>().FirstOrDefault(pred);
    }

    private void DestroyConnection(BlueprintConnectionVM connectionVm)
    {
        if (connectionVm.OutputPin?.Connection == connectionVm)
        {
            connectionVm.OutputPin.Connection = null;
        }

        if (connectionVm.InputPin?.Connection == connectionVm)
        {
            connectionVm.InputPin.Connection = null;
        }

        connectionVm.OutputPin = null;
        connectionVm.InputPin = null;

        SelectedConnections.Remove(connectionVm);

        if (DataContext is BlueprintDocumentVM documentVm)
        {
            documentVm.BlueprintItems.Remove(connectionVm);
        }
    }


    private void ZoomBorder_Initialized(object? sender, EventArgs e)
    {
        _zoomBorder = sender as ZoomBorder;

    }
    
    private void Canvas_OnInitialized(object sender, EventArgs e)
    {
        _canvas = sender as Canvas;
    }
    
    private Point _offset = new Point();
    private Point _clickPos = new();
    private ZoomBorder _zoomBorder;
    private Canvas _canvas;

}