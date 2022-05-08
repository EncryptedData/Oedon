using Dock.Model.Core;
using ReactiveUI;

namespace Oedon.Core.UI.ViewModels;

public class BaseDockWindow : BaseViewModel
{
    protected IFactory _factory;
    protected IDock _layout;
    protected string _currentView;

    public IFactory Factory
    {
        get => _factory;
        set => this.RaiseAndSetIfChanged(ref _factory, value);
    }

    public IDock Layout
    {
        get => _layout;
        set => this.RaiseAndSetIfChanged(ref _layout, value);
    }

    public string CurrentView
    {
        get => _currentView;
        set => this.RaiseAndSetIfChanged(ref _currentView, value);
    }
}