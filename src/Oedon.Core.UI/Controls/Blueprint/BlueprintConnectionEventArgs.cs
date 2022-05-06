using Avalonia.Interactivity;

namespace Oedon.Core.UI.Controls;

public class BlueprintConnectionEventArgs : RoutedEventArgs
{
    public BlueprintConnectionEventArgs(IReadOnlyList<BlueprintConnectionVM> connections)
    {
        Connections = connections;
    }
    
    public IReadOnlyList<BlueprintConnectionVM> Connections { get; }
}