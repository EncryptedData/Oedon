using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace Oedon.Designer.Core.UI.Views;

public partial class BasicNodeView : UserControl
{
    public BasicNodeView()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }
}