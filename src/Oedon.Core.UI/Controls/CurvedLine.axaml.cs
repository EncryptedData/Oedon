using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using Avalonia.Media;

namespace Oedon.Core.UI.Controls;

public partial class CurvedLine : UserControl
{
    public CurvedLine()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }

    #region CurvedLine

    // StartPos is the point that represents the start of our curved line
    public static readonly DirectProperty<CurvedLine, Point> StartPosProperty =
        AvaloniaProperty.RegisterDirect<CurvedLine, Point>(
            nameof(StartPos),
            o => o.StartPos,
            (o, v) => o.StartPos = v);

    private Point _startPos = new Point();

    public Point StartPos
    {
        get => _startPos;
        set
        {
            // When changed we need to recalculate the curve
            SetAndRaise(StartPosProperty, ref _startPos, value);
            CalculateBezierCurve();
        } 
    }

    #endregion
    
    #region EndPos

    // EndPos is the point that represents the end of our curved line
    public static readonly DirectProperty<CurvedLine, Point> EndPosProperty =
        AvaloniaProperty.RegisterDirect<CurvedLine, Point>(
            nameof(EndPos),
            o => o.EndPos,
            (o, v) => o.EndPos = v);

    private Point _endPos = new Point();

    public Point EndPos
    {
        get => _endPos;
        set 
        {
            // When changed we need to recalculate the curve
            SetAndRaise(EndPosProperty, ref _endPos, value);
            CalculateBezierCurve();
        }
    }

    #endregion
    
    #region Thickness

    // Thickness is the StrokeThicknes for the Path
    public static readonly DirectProperty<CurvedLine, double> ThicknessProperty =
        AvaloniaProperty.RegisterDirect<CurvedLine, double>(
            nameof(Thickness),
            o => o.Thickness,
            (o, v) => o.Thickness = v);

    private double _thickness = 5;

    public double Thickness
    {
        get => _thickness;
        set 
        {
            // Set the Path.Stroke if the Path is valid
            SetAndRaise(ThicknessProperty, ref _thickness, value);
            if (_path is not null)
            {
                _path.StrokeThickness = _thickness;  
            }
            
        }
    }

    #endregion
    
    
    #region Stroke

    // Stroke is the Stroke for the Path
    public static readonly DirectProperty<CurvedLine, Avalonia.Media.IBrush> StrokeProperty =
        AvaloniaProperty.RegisterDirect<CurvedLine, Avalonia.Media.IBrush>(
            nameof(Stroke),
            o => o.Stroke,
            (o, v) => o.Stroke = v);

    private Avalonia.Media.IBrush _stroke = new SolidColorBrush(Colors.Black);

    public Avalonia.Media.IBrush Stroke
    {
        get => _stroke;
        set 
        {
            // Set the Path.Stroke if the Path is valid
            SetAndRaise(StrokeProperty, ref _stroke, value);
            if (_path is not null)
            {
                _path.Stroke = _stroke;  
            }
            
        }
    }

    #endregion
    
    /// <summary>
    /// Create the string representing a bezier curve to be passed to the path data
    /// </summary>
    public void CalculateBezierCurve()
    {
        if (_path is null)
        {
            return;
        }

        // How the string should look: "M x,y C x,y x,y x,y"
        string path = $"M {StartPos.X},{StartPos.Y} C {(StartPos.X + EndPos.X) / 2},{StartPos.Y} {(StartPos.X + EndPos.X) / 2},{EndPos.Y} {EndPos.X},{EndPos.Y}";

        _path.Data = PathGeometry.Parse(path);
        _path.StrokeThickness = Thickness;
    }

    private void StyledElement_OnInitialized(object sender, EventArgs e)
    {
        _path = sender as Avalonia.Controls.Shapes.Path;
        // Set our other variables
        if (_path is not null)
        {
            _path.StrokeThickness = Thickness;
            _path.Stroke = Stroke;
        }
    }
    
    

    private Avalonia.Controls.Shapes.Path _path;
}