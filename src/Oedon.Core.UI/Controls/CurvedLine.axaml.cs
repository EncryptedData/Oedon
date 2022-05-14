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
    }

    private void StyledElement_OnInitialized(object sender, EventArgs e)
    {
        _path = sender as Avalonia.Controls.Shapes.Path;
    }

    private Avalonia.Controls.Shapes.Path _path;
}