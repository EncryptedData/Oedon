using System;
using Avalonia.Controls;
using Oedon.Designer.ViewModels;

namespace Oedon.Designer.Views
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void StyledElement_OnDataContextChanged(object? sender, EventArgs e)
        {
            if (DataContext is MainWindowViewModel vm)
            {
                vm.Window = this;
            }
        }
    }
}