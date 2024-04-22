using System;
using Autofac;
using Avalonia.Controls;
using Avalonia.Controls.Templates;
using OedonEditor.ViewModels;
using Serilog;

namespace OedonEditor;

public class ViewLocator : IDataTemplate
{
    private readonly IContainer _container;
    
    public ViewLocator()
    {
        _container = Program.Container;
    }
    
    
    public Control? Build(object? data)
    {
        if (data is null)
            return null;
        
        // Ask Autofac to find the View for this ViewModel
        var control = _container.ResolveOptionalKeyed<Control>(data.GetType());

        if (control is null)
        {
            Log.Error("Cannot find View type for {ViewModelName}", data.GetType().FullName);
            return new TextBlock { Text = $"Not Found: {data.GetType().FullName}" };
        }

        return control;
    }

    public bool Match(object? data)
    {
        return data is BaseViewModel;
    }
}
