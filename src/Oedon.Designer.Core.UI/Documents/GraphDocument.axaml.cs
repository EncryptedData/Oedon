using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;

namespace Oedon.Designer.Core.UI.Documents;

public partial class GraphDocument : UserControl
{
    public GraphDocument()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }
}