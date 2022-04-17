using Oedon.Core.UI.ViewModels;
using Oedon.NativeInterop;
using System;
using System.Collections.Generic;
using System.Text;

namespace Oedon.Designer.ViewModels
{
    public class MainWindowViewModel : BaseViewModel
    {
        public MainWindowViewModel()
        {
        }

        public string Greeting => $"Calling stub: {OedonCpp.Sum(2, 2)} {OedonCpp.Foo("Hello World")}";
    }
}
