using Oedon.Core.UI.ViewModels;
using Oedon.NativeInterop;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using EncryptedData.EventAggregator;
using EncryptedData.EventAggregator.Avalonia;
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
    public class MainWindowViewModel : BlueprintDocumentVM
    {
        public MainWindowViewModel()
        {
            AddTestNodeCommand = ReactiveCommand.CreateFromTask(OnAddTestNode);
            DoCalculationCommand = ReactiveCommand.CreateFromTask(OnDoCalculation);
            AddAddNodeCommand = ReactiveCommand.CreateFromTask(OnAddAddNode);
            AddOutputNodeCommand = ReactiveCommand.CreateFromTask(OnAddOutputNode);
            AddMultiplyNodeCommand = ReactiveCommand.CreateFromTask(OnAddMultiplyNode);
        }

        public string StatusBarText => $"Calling stub: {OedonCpp.Sum(1,1)}";

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
        
        // Ideally use DI
        private IEventAggregator _eventAggregator = new AvaloniaEventAggregator();
    }
}
