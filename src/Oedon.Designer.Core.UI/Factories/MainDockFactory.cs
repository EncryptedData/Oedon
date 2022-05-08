using Avalonia.Data;
using Dock.Avalonia.Controls;
using Dock.Model.Controls;
using Dock.Model.Core;
using Dock.Model.ReactiveUI;
using Dock.Model.ReactiveUI.Controls;
using Oedon.Core.UI.ViewModels;
using Oedon.Designer.Core.UI.Documents;
using ReactiveUI;

namespace Oedon.Designer.Core.UI.Factories;

public class MainDockFactory : Factory
{
    private IDocumentDock _documentDock;
    private readonly object _context;

    public MainDockFactory(object context)
    {
        _context = context;
    }

    public override IRootDock CreateLayout()
    {
        var document1 = new GraphDocumentVM()
        {
            Id = nameof(GraphDocumentVM),
            Title = "Graph Document"
        };

        document1.CanFloat = false;

        var documentDock = new DocumentDock()
        {
            Id = "DocumentsPane",
            Title = "DocumentsPane",
            Proportion = double.NaN,
            ActiveDockable = document1,
            VisibleDockables = CreateList<IDockable>(document1)
        };

        var mainLayout = new ProportionalDock
        {
            Id = "MainLayout",
            Title = "MainLayout",
            Proportion = double.NaN,
            Orientation = Orientation.Horizontal,
            ActiveDockable = null,
            VisibleDockables = CreateList<IDockable>
            (
                documentDock
            )
        };

        var rootDockVm = new RootDockViewModel()
        {
            Id = "Main",
            Title = "Main",
            ActiveDockable = mainLayout,
            VisibleDockables = CreateList<IDockable>(mainLayout)
        };

        var root = CreateRootDock();
        root.Id = "Root";
        root.Title = "Root";
        root.ActiveDockable = rootDockVm;
        root.DefaultDockable = rootDockVm;
        root.VisibleDockables = CreateList<IDockable>(rootDockVm);

        _documentDock = documentDock;
        return root;
    }

    public override void InitLayout(IDockable layout)
    {
        this.ContextLocator = new Dictionary<string, Func<object>>
        {
            [nameof(IRootDock)] = () => _context,
            [nameof(IProportionalDock)] = () => _context,
            [nameof(IDocumentDock)] = () => _context,
            [nameof(IToolDock)] = () => _context,
            [nameof(IProportionalDockSplitter)] = () => _context,
            [nameof(IDockWindow)] = () => _context,
            [nameof(IDocument)] = () => _context,
            [nameof(ITool)] = () => _context,
            [nameof(GraphDocumentVM)] = () => new GraphDocument(),
            ["LeftPane"] = () => _context,
            ["LeftPaneTop"] = () => _context,
            ["LeftPaneTopSplitter"] = () => _context,
            ["LeftPaneBottom"] = () => _context,
            ["RightPane"] = () => _context,
            ["RightPaneTop"] = () => _context,
            ["RightPaneTopSplitter"] = () => _context,
            ["RightPaneBottom"] = () => _context,
            ["DocumentsPane"] = () => _context,
            ["LeftSplitter"] = () => _context,
            ["RightSplitter"] = () => _context,
            ["MainLayout"] = () => _context,
            ["Main"] = () => _context,
        };

        this.HostWindowLocator = new Dictionary<string, Func<IHostWindow>>()
        {
            [nameof(IDockWindow)] = () =>
            {
                var hostWindow = new HostWindow()
                {
                    [!HostWindow.TitleProperty] = new Binding("ActiveDockable.Title")
                };
                return hostWindow;
            }
        };

        this.DockableLocator = new Dictionary<string, Func<IDockable?>>()
        {
        };

        base.InitLayout(layout);

        SetActiveDockable(_documentDock);
        SetFocusedDockable(_documentDock, _documentDock.VisibleDockables?.FirstOrDefault());
    }
}