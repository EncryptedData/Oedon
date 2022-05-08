using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;
using Dock.Model.Core;
using Oedon.Designer.Core.UI.Factories;
using Oedon.Designer.ViewModels;
using Oedon.Designer.Views;

namespace Oedon.Designer
{
    public partial class App : Application
    {
        public override void Initialize()
        {
            AvaloniaXamlLoader.Load(this);
        }

        public override void OnFrameworkInitializationCompleted()
        {
            var factory = new MainDockFactory(new object());
            var layout = factory.CreateLayout();
            factory.InitLayout(layout);

            var mainWindowVm = new MainWindowViewModel()
            {
                Factory = factory,
                Layout = layout
            };

            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop)
            {
                var mainWindow = new MainWindow()
                {
                    DataContext = mainWindowVm
                };

                mainWindow.Closing += (_, _) =>
                {
                    if (layout is IDock dock && dock.Close.CanExecute(null))
                    {
                        dock.Close.Execute(null);
                    }
                };

                desktop.MainWindow = mainWindow;

                desktop.Exit += (_, _) =>
                {
                    if (layout is IDock dock && dock.Close.CanExecute(null))
                    {
                        dock.Close.Execute(null);
                    }
                };

            }

            base.OnFrameworkInitializationCompleted();
        }
    }
}