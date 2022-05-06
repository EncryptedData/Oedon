using ReactiveUI;

namespace Oedon.Core.UI.Controls;

public abstract class BlueprintPinValueVM<T> : BlueprintPinVM
{
    protected BlueprintPinValueVM(BlueprintNodeVM parent, string name, BlueprintPinType type, Func<Task<T>> accessor) : 
        base(parent, name, type)
    {
        _accessor = accessor ?? throw new ArgumentNullException(nameof(accessor));
    }

    public Task<T> GetValue()
    {
        return _accessor();
    }

    private readonly Func<Task<T>> _accessor;
}