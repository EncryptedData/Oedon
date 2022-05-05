using Oedon.Core.UI.Controls;
using Oedon.Core.UI.Views;
using Oedon.Designer.Core.UI.Pins;
using Oedon.Designer.Core.UI.Views;
using ReactiveUI;

namespace Oedon.Designer.Core.UI.Nodes.Float;

[View(typeof(ValueNodeView))]
public class ConstantFloatNode : BlueprintNodeVM
{
    public ConstantFloatNode()
    {
        OutputPins = new BlueprintPinVM[]
        {
            new FloatOutputPinVM(this, "Output", GetOutputPin),
        };
    }

    public float Value
    {
        get => _value;
        set => this.RaiseAndSetIfChanged(ref _value, value);
    }

    private Task<float> GetOutputPin()
    {
        return Task.FromResult(Value);
    }
    
    public override string Name => "Float Value";

    public override BlueprintPinVM[] InputPins { get; } = null;
    
    public override BlueprintPinVM[] OutputPins { get; }

    public override double Height => 75.0;

    public override double Width => 350.0;

    private float _value = 0.0f;
}