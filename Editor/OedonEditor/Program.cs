using Avalonia;
using Avalonia.ReactiveUI;
using System;
using Autofac;
using ReactiveUI;
using Serilog;
using Serilog.Extensions.Autofac.DependencyInjection;
using Splat;
using Splat.Autofac;

namespace OedonEditor;

sealed class Program
{
    public static IContainer Container { get; private set; }
    
    [STAThread]
    public static int Main(string[] args)
    {
        Log.Logger = new LoggerConfiguration()
            .WriteTo.Console()
            .CreateLogger();

        Log.Information("Oedon starting up.");
        
        try
        {
            ContainerBuilder builder = new();
            builder.RegisterSerilog(new LoggerConfiguration().WriteTo.Console());
            builder.RegisterModule<OedonEditorModule>();
            
            AutofacDependencyResolver resolver = new(builder);
            Locator.SetLocator(resolver);

            Locator.CurrentMutable.InitializeSplat();
            Locator.CurrentMutable.InitializeReactiveUI();
        
            resolver.RegisterConstant(new AvaloniaActivationForViewFetcher(), typeof(IActivationForViewFetcher));
            resolver.RegisterConstant(new AutoDataTemplateBindingHook(), typeof(IPropertyBindingHook));
            RxApp.MainThreadScheduler = AvaloniaScheduler.Instance;

            Container = builder.Build();
            resolver.SetLifetimeScope(Container);
            
            BuildAvaloniaApp()
                .StartWithClassicDesktopLifetime(args);
        }
        catch (Exception e)
        {
            Log.Error(e, "Uncaught exception crashed program...");
        }
        finally
        {
            Log.CloseAndFlush();
        }

        return 0;
    }

    public static AppBuilder BuildAvaloniaApp()
        => AppBuilder.Configure(() => Container.Resolve<App>())
            .UsePlatformDetect()
            .WithInterFont()
            .LogToTrace();
}
