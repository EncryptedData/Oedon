using Avalonia;
using Avalonia.Controls;
using Avalonia.Input;
using Avalonia.Markup.Xaml;

namespace Oedon.Designer.Core.UI.Views;

public partial class ValueNodeView : UserControl
{
    public ValueNodeView()
    {
        InitializeComponent();
    }

    private void InitializeComponent()
    {
        AvaloniaXamlLoader.Load(this);
    }

    private void InputElement_OnTextInput(object? sender, TextInputEventArgs e)
    {
        try
        {
            string text = e.Text ?? throw new ArgumentNullException(nameof(e.Text));
            float.Parse(text);
        }
        catch (Exception)
        {
            e.Handled = true;
        }
    }
}