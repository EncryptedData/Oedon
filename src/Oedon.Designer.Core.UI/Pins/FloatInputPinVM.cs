using Avalonia.Media;
using Oedon.Core.UI.Controls;

namespace Oedon.Designer.Core.UI.Pins;

public class FloatInputPinVM : BlueprintPinVM
{
    public FloatInputPinVM(BlueprintNodeVM parent, string name) : 
        base(parent, name, BlueprintPinType.Input)
    {
    }

    public override IBrush PinColor => Brushes.LightBlue;
    
    public override bool AllowConnection(BlueprintPinVM other)
    {
        return other is FloatOutputPinVM;
    }
}