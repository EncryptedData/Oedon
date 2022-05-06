using Oedon.Core.UI.Controls;
using Oedon.Core.UI.Views;
using Oedon.Designer.Core.UI.Pins;
using Oedon.Designer.Core.UI.Views;

namespace Oedon.Designer.Core.UI.Nodes.Float;

[View(typeof(BasicNodeView))]
public class AddFloatNode : BlueprintNodeVM
{
    public AddFloatNode()
    {
        InputPins = new BlueprintPinVM[]
        {
            new FloatInputPinVM(this, "A"),
            new FloatInputPinVM(this, "B")
        };

        OutputPins = new BlueprintPinVM[]
        {
            new FloatOutputPinVM(this, "Output", OnOutput)
        };
    }

    private async Task<float> OnOutput()
    {
        float result = 0.0f;
        
        if (InputPins[0].Connection is not null)
        {
            FloatOutputPinVM? inputVm = InputPins[0].Connection.OutputPin as FloatOutputPinVM;

            result += await inputVm!.GetValue();
        }

        if (InputPins[1].Connection is not null)
        {
            FloatOutputPinVM? inputVm = InputPins[1].Connection.OutputPin as FloatOutputPinVM;

            result += await inputVm!.GetValue();
        }

        return result;
    }
    
    public override string Name => "Add Floats";
    
    public override BlueprintPinVM[] InputPins { get; }
    
    public override BlueprintPinVM[] OutputPins { get; }
    
    public override double Height => 100.0;
    
    public override double Width => 100.0;
}