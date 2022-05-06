using Avalonia;
using Avalonia.Collections;
using Avalonia.Controls;
using Avalonia.Controls.Primitives;
using Avalonia.Layout;

namespace Oedon.Core.UI.Controls;

public class BlueprintPinGroup : TemplatedControl
{
    #region Pins

    public static readonly DirectProperty<BlueprintPinGroup, IEnumerable<BlueprintPinVM>> PinsProperty =
        AvaloniaProperty.RegisterDirect<BlueprintPinGroup, IEnumerable<BlueprintPinVM>>(
            nameof(Pins),
            o => o.Pins,
            (o, v) => o.Pins = v);

    private IEnumerable<BlueprintPinVM> _pins = new AvaloniaList<BlueprintPinVM>();

    public IEnumerable<BlueprintPinVM> Pins
    {
        get => _pins;
        set => SetAndRaise(PinsProperty, ref _pins, value);
    }

    #endregion

    #region Orientation

    public static readonly StyledProperty<Orientation> OrientationProperty =
        StackLayout.OrientationProperty.AddOwner<StackPanel>();

    public Orientation Orientation
    {
        get => GetValue(OrientationProperty);
        set => SetValue(OrientationProperty, value);
    }

    #endregion
}