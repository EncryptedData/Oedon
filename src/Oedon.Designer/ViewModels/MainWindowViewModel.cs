using Oedon.Core.UI.ViewModels;
using Oedon.NativeInterop;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using Oedon.Core.UI.Controls;
using Oedon.Core.UI.Views;
using Oedon.Designer.Core.UI.Nodes;
using Oedon.Designer.Core.UI.Nodes.Float;
using Oedon.Designer.Core.UI.Pins;
using Oedon.Designer.Views;
using ReactiveUI;

namespace Oedon.Designer.ViewModels
{
    [View(typeof(MainWindow))]
    public class MainWindowViewModel : BaseDockWindow
    {
        public MainWindowViewModel()
        {
            
        }

        public string StatusBarText => $"Calling stub: {OedonCpp.Sum(1,1)}";
    }
}
