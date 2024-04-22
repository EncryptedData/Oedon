using Autofac;
using OedonEditor.Extensions;
using OedonEditor.ViewModels;
using OedonEditor.Views;
using Serilog;
using Serilog.Extensions.Autofac.DependencyInjection;

namespace OedonEditor;

public class OedonEditorModule : Module
{
    protected override void Load(ContainerBuilder builder)
    {
        builder.RegisterType<App>().AsSelf().AsImplementedInterfaces();
        builder.RegisterViewModel<MainWindow, MainWindowViewModel>();
    }
}