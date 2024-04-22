using ReactiveUI;

namespace OedonEditor.ViewModels;

public class MainWindowViewModel : BaseViewModel
{
    private double _windowHeight = 720;
    public double WindowHeight
    {
        get => _windowHeight;
        set => this.RaiseAndSetIfChanged(ref _windowHeight, value);
    }

    private double _windowWidth = 1280;
    public double WindowWidth
    {
        get => _windowWidth;
        set => this.RaiseAndSetIfChanged(ref _windowWidth, value);
    }
}
