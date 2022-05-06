using Avalonia.Media;
using Oedon.Core.UI.ViewModels;
using ReactiveUI;

namespace Oedon.Core.UI.Controls;

public abstract class BlueprintPinVM : BaseViewModel, IBlueprintItemVM
{
    protected BlueprintPinVM(BlueprintNodeVM parent, string name, BlueprintPinType type)
    {
        Parent = parent;
        PinType = type;
        Name = name;
    }
    
    public BlueprintNodeVM Parent { get; }
    
    public BlueprintPinType PinType { get; }
    
    public string Name { get; }

    public BlueprintConnectionVM Connection
    {
        get => _connection;
        set => this.RaiseAndSetIfChanged(ref _connection, value);
    }
    
    public abstract IBrush PinColor { get; }

    /// <summary>
    /// Should we allow the connection?
    /// </summary>
    /// <param name="other">The other pin to test</param>
    /// <returns>TRUE if you want the connection, FALSE otherwise</returns>
    public abstract bool AllowConnection(BlueprintPinVM other);

    private BlueprintConnectionVM _connection = null;
}