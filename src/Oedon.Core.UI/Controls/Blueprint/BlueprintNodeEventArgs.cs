using Avalonia.Interactivity;

namespace Oedon.Core.UI.Controls;

public class BlueprintNodeEventArgs : RoutedEventArgs
{
    public BlueprintNodeEventArgs(IReadOnlyList<BlueprintNodeVM> nodes)
    {
        Nodes = nodes;
    }
    
    public IReadOnlyList<BlueprintNodeVM> Nodes { get; }
}