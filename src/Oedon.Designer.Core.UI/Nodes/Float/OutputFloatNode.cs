using Oedon.Core.UI.Controls;
using Oedon.Core.UI.Views;
using Oedon.Designer.Core.UI.Pins;
using Oedon.Designer.Core.UI.Views;
using ReactiveUI;

namespace Oedon.Designer.Core.UI.Nodes.Float;

[View(typeof(BasicNodeView))]
public class OutputFloatNode : BlueprintNodeVM
{
    public OutputFloatNode()
    {
        InputPins = new BlueprintPinVM[]
        {
            new FloatInputPinVM(this, "Input")
        };
    }

    public async Task<float> GetValue()
    {
        float result = 0.0f;

        BlueprintConnectionVM connectionVm = InputPins[0].Connection;
        if (connectionVm is not null && connectionVm.OutputPin is FloatOutputPinVM outputPinVm)
        {
            result = await outputPinVm.GetValue();
        }
        
        return result;
    }
    
    
    public override string Name => "Float Output";
    
    public override BlueprintPinVM[] InputPins { get; }

    public override BlueprintPinVM[] OutputPins { get; } = null;

    public override double Height => 75.0;

    public override double Width => 100.0;
}