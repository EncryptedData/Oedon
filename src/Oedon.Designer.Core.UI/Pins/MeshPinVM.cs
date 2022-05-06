using Avalonia.Media;
using Oedon.Core.UI.Controls;

namespace Oedon.Designer.Core.UI.Pins;

public class MeshPinVM : BlueprintPinVM
{
    public MeshPinVM(BlueprintNodeVM parent, string name, BlueprintPinType type) : 
        base(parent, name, type)
    {
    }

    public override IBrush PinColor => Brushes.Orange;
    
    public override bool AllowConnection(BlueprintPinVM other)
    {
        return other is MeshPinVM;
    }
}