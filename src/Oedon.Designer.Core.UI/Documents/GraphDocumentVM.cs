using System.Windows.Input;
using Oedon.Core.UI.ViewModels;
using Oedon.Core.UI.Views;
using Oedon.Designer.Core.UI.Nodes.Float;
using ReactiveUI;

namespace Oedon.Designer.Core.UI.Documents;

[View(typeof(GraphDocument))]
public class GraphDocumentVM : BlueprintDocumentVM
{
    public GraphDocumentVM()
    {
        AddTestNodeCommand = ReactiveCommand.CreateFromTask(OnAddTestNode);
        DoCalculationCommand = ReactiveCommand.CreateFromTask(OnDoCalculation);
        AddAddNodeCommand = ReactiveCommand.CreateFromTask(OnAddAddNode);
        AddOutputNodeCommand = ReactiveCommand.CreateFromTask(OnAddOutputNode);
        AddMultiplyNodeCommand = ReactiveCommand.CreateFromTask(OnAddMultiplyNode);
    }
    
    public string OutputString
    {
        get => _outputString;
        set => this.RaiseAndSetIfChanged(ref _outputString, value);
    }
    
    public ICommand AddTestNodeCommand { get; }
        
    public ICommand AddAddNodeCommand { get; }
        
    public ICommand AddOutputNodeCommand { get; }
        
    public ICommand AddMultiplyNodeCommand { get; }

    public ICommand DoCalculationCommand { get; }
    
    private Task OnAddTestNode()
    {
        AddItem(new ConstantFloatNode());

        return Task.CompletedTask;
    }

    private Task OnAddAddNode()
    {
        AddItem(new AddFloatNode());
            
        return Task.CompletedTask;
    }

    private Task OnAddOutputNode()
    {
        AddItem(new OutputFloatNode());
            
        return Task.CompletedTask;
    }

    private Task OnAddMultiplyNode()
    {
        AddItem(new MultiplyFloatNode());
            
        return Task.CompletedTask;
    }

    private async Task OnDoCalculation()
    {
        var node = BlueprintItems.FirstOrDefault(e => e is OutputFloatNode);

        if (node is OutputFloatNode outputFloatNode)
        {
            float value = await outputFloatNode.GetValue();
            OutputString = $"{value}";
        }
    }

    private string _outputString = String.Empty;
}