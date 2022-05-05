using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace Oedon.Core.UI.Controls;

public partial class BlueprintConnection : UserControl
{
    public BlueprintConnection()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }
}