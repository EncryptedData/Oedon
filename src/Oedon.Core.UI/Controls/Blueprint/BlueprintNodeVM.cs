using Oedon.Core.UI.ViewModels;
using ReactiveUI;

namespace Oedon.Core.UI.Controls;

public abstract class BlueprintNodeVM : BaseViewModel, IBlueprintItemVM
{
    public abstract string Name { get; }
    
    public abstract BlueprintPinVM[] InputPins { get; }
    
    public abstract BlueprintPinVM[] OutputPins { get; }
    
    public abstract double Height { get; }
    
    public abstract double Width { get; }
    
    public double XPos
    {
        get => _xpos; 
        set => this.RaiseAndSetIfChanged(ref _xpos, value);
    }

    public double YPos
    {
        get => _ypos;
        set => this.RaiseAndSetIfChanged(ref _ypos, value);
    }

    private double _xpos = 0.0f;
    private double _ypos = 0.0f;
}