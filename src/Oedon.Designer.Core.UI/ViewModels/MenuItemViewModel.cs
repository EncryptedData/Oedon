using System.Collections.ObjectModel;
using System.Windows.Input;
using Oedon.Core.UI.ViewModels;

namespace Oedon.Designer.Core.UI.ViewModels;

public class MenuItemViewModel : BaseViewModel
{
    public string Header { get; set; }
    public ICommand Command { get; set; }
    public object CommandParameter { get; set; }
    public ObservableCollection<MenuItemViewModel> Items { get; set; }
}