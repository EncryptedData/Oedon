using System;
using System.Reflection;
using Avalonia.Controls;
using Avalonia.Controls.Templates;
using Dock.Model.Core;
using Oedon.Core.UI.ViewModels;
using Oedon.Core.UI.Views;
using Oedon.Designer.ViewModels;

namespace Oedon.Designer
{
    public class ViewLocator : IDataTemplate
    {
        public IControl Build(object data)
        {
            Type type = data.GetType();
            ViewAttribute? viewAttribute = type.GetCustomAttribute<ViewAttribute>();

            if (viewAttribute is not null)
            {
                return (Control)Activator.CreateInstance(viewAttribute.ViewType)!;
            }

            return new TextBlock { Text = $"View Not Found for {type.FullName}" };
        }

        public bool Match(object data)
        {
            return data is BaseViewModel or IDockable;
        }
    }
}