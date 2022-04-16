using Oedon.Core.UI.ViewModels;
using Oedon.NativeInterop;
using System;
using System.Collections.Generic;
using System.Text;

namespace Oedon.Designer.ViewModels
{
    public class MainWindowViewModel : BaseViewModel
    {
        public string Greeting => $"Calling stub: {OedonNative.Stub(1,1)}";
    }
}
