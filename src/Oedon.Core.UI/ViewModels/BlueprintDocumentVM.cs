using System.Collections.ObjectModel;
using DynamicData;
using Oedon.Core.UI.Controls;
using ReactiveUI;

namespace Oedon.Core.UI.ViewModels;

public abstract class BlueprintDocumentVM : BaseDocumentVM
{

    protected void AddItem(IBlueprintItemVM item)
    {
        BlueprintItems.Add(item);
    }

    protected void AddItems(params IBlueprintItemVM[] items)
    {
        BlueprintItems.AddRange(items);
    }

    public ObservableCollection<IBlueprintItemVM> BlueprintItems
    {
        get => _blueprintItems;
        set => this.RaiseAndSetIfChanged(ref _blueprintItems, value);
    }

    private ObservableCollection<IBlueprintItemVM> _blueprintItems = new();
}