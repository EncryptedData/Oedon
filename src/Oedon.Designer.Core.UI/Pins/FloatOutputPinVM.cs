using Avalonia.Media;
using Oedon.Core.UI.Controls;

namespace Oedon.Designer.Core.UI.Pins;

public class FloatOutputPinVM : BlueprintPinValueVM<float>
{
    public FloatOutputPinVM(BlueprintNodeVM parent, string name, Func<Task<float>> accessor) : 
        base(parent, name, BlueprintPinType.Output, accessor)
    {
    }

    public override IBrush PinColor => Brushes.LightBlue;
    
    public override bool AllowConnection(BlueprintPinVM other)
    {
        return other is FloatInputPinVM;
    }
}