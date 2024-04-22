using Autofac;
using Avalonia.Controls;
using OedonEditor.ViewModels;

namespace OedonEditor.Extensions;

public static class ContainerBuilderExtensions
{
    public static void RegisterViewModel<TView, TViewModel>(this ContainerBuilder builder) 
        where TView : Control
        where TViewModel : BaseViewModel
    {
        builder.RegisterType<TView>().AsSelf()
            .Keyed<Control>(typeof(TViewModel));
        builder.RegisterType<TViewModel>().AsSelf();
    }
}