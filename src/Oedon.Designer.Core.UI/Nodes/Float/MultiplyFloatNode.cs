using Oedon.Core.UI.Controls;
using Oedon.Core.UI.Views;
using Oedon.Designer.Core.UI.Pins;
using Oedon.Designer.Core.UI.Views;

namespace Oedon.Designer.Core.UI.Nodes.Float;

[View(typeof(BasicNodeView))]
public class MultiplyFloatNode : BlueprintNodeVM
{
    public MultiplyFloatNode()
    {
        InputPins = new BlueprintPinVM[]
        {
            new FloatInputPinVM(this, "A"),
            new FloatInputPinVM(this, "B"),
        };

        OutputPins = new BlueprintPinVM[]
        {
            new FloatOutputPinVM(this, "Output", GetOutput)
        };
    }

    private async Task<float> GetOutput()
    {
        float result = 0.0f;

        BlueprintPinVM? pinA = InputPins[0].Connection?.OutputPin;
        BlueprintPinVM? pinB = InputPins[1].Connection?.OutputPin;

        if (pinA is FloatOutputPinVM outputA && pinB is FloatOutputPinVM outputB)
        {
            float a = await outputA.GetValue();
            float b = await outputB.GetValue();

            result = a * b;
        }

        return result;
    }

    public override string Name => "Multiply Floats";
    
    public override BlueprintPinVM[] InputPins { get; }
    
    public override BlueprintPinVM[] OutputPins { get; }

    public override double Height => 100.0f;

    public override double Width => 100.0f;
}