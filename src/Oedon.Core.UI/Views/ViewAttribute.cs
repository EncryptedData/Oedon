using Avalonia.Controls;

namespace Oedon.Core.UI.Views;

public class ViewAttribute : Attribute
{
    public ViewAttribute(Type viewType)
    {
        ViewType = viewType;

        if (!viewType.IsAssignableTo(typeof(Control)))
        {
            throw new Exception($"{viewType.FullName} must inherit from Avalonia Control!");
        }
    }
    
    public Type ViewType { get; }
}