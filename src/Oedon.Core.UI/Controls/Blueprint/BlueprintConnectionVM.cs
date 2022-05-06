using Avalonia;
using Oedon.Core.UI.ViewModels;
using ReactiveUI;

namespace Oedon.Core.UI.Controls;

public class BlueprintConnectionVM : BaseViewModel, IBlueprintItemVM
{
    public Point OutputPos
    {
        get => _outputPos;
        set => this.RaiseAndSetIfChanged(ref _outputPos, value);
    }

    public BlueprintPinVM OutputPin
    {
        get => _outputPin;
        set => this.RaiseAndSetIfChanged(ref _outputPin, value);
    }

    public Point InputPos
    {
        get => _inputPos;
        set => this.RaiseAndSetIfChanged(ref _inputPos, value);
    }

    public BlueprintPinVM InputPin
    {
        get => _inputPin;
        set => this.RaiseAndSetIfChanged(ref _inputPin, value);
    }

    private Point _outputPos = new();
    private Point _inputPos = new();
    private BlueprintPinVM _outputPin = null;
    private BlueprintPinVM _inputPin = null;
}