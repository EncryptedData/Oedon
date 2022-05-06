using Oedon.Core.UI.ViewModels;
using Oedon.NativeInterop;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using Avalonia;
using Avalonia.Controls;
using Oedon.Designer.Core.Resources;
using Oedon.Designer.Core.UI.ViewModels;
using ReactiveUI;

namespace Oedon.Designer.ViewModels
{
    public class MainWindowViewModel : BaseViewModel
    {
        public MainWindowViewModel()
        {
            NewCommand = ReactiveCommand.Create(OnNew);
            OpenCommand = ReactiveCommand.CreateFromTask(OnOpen);
            SaveCommand = ReactiveCommand.CreateFromTask(OnSave);
            SaveAsCommand = ReactiveCommand.CreateFromTask(OnSaveAs);
            
            _menuItems.Add(new MenuItemViewModel()
            {
                Header = $"_{Resources.MenuLabel_File}",
                Items = new ObservableCollection<MenuItemViewModel>()
                {
                    new()
                    {
                        Header = "_New",
                        Command = NewCommand
                    },
                    new()
                    {
                        Header = "_Open",
                        Command = OpenCommand
                    },
                    new()
                    {
                        Header = "_Save",
                        Command = SaveCommand
                    },
                    new()
                    {
                        Header = "_Save As...",
                        Command = SaveAsCommand
                    }
                    
                }
            });
        }

        public string Greeting => $"Calling stub: {OedonNative.Stub(1, 1)}";

        public ObservableCollection<MenuItemViewModel> MenuItems
        {
            get => _menuItems;
            set => this.RaiseAndSetIfChanged(ref _menuItems, value);
        }
        
        public ICommand NewCommand { get; }

        public ICommand OpenCommand { get; }
        
        public ICommand SaveCommand { get; }
        
        public ICommand SaveAsCommand { get; }
        
        public Window Window { get; set; }

        private void OnNew()
        {
            System.Diagnostics.Debug.Write("Creating new project...");
        }
        

        private async Task OnOpen()
        {
            var dialog = new OpenFileDialog();
            dialog.Title = "Open Project";


            var result = await dialog.ShowAsync(Window);

            if (result != null)
            {
                //TODO: Load project file
            }
        }

        private async Task OnSave()
        {
           
        }

        private async Task OnSaveAs()
        {
            var dialog = new SaveFileDialog();
            dialog.Title = "Save As";
            dialog.InitialFileName = "OedenProject";
            dialog.DefaultExtension = "odn";

            var result = await dialog.ShowAsync(Window);

            if (result != null)
            {
                

            }
            
        }
        
        

        private ObservableCollection<MenuItemViewModel> _menuItems = new();
    }
}
