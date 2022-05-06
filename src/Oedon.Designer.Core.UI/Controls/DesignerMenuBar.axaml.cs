using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace Oedon.Designer.Core.UI.Controls;

public partial class DesignerMenuBar : UserControl
{
    public DesignerMenuBar()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }
}