using Oedon.Core.UI.ViewModels;
using Oedon.NativeInterop;
using System;
using System.Collections.Generic;
using System.Text;

namespace Oedon.Designer.ViewModels
{
    public class MainWindowViewModel : BaseViewModel
    {
        public string Greeting => $"Calling stub: {OedonNative.Stub(1,1)}";
        public MainWindowViewModel()
        {
            string operations = @"
[
	""Write"": {
		""output"": 0
		""mesh"":
		{
			}
		}
	""Scale"": {
		""input"": 0,
		""output"": 1,
		""scale"": 2
	},
	""Bevel"": {
		""input"": 2,
		""output"": 3,
		""bevel_size"": 0.2
	},
	""Union"": {
		""input_1"": 1,
		""input_2"": 2,
		""output"": 4,
	},
	""fancywa"": {
		""input_1"": 1,
		""input_2"": 4,
		""input_3"": 5,
		""output"": 6,
		""output2"": 7,
		""float_output"": 0
	}
}";

            OedonNative.DoOperations(IntPtr.Zero, operations);
        }
    }
}
