using System.Collections;
using System.Globalization;
using Avalonia;
using Avalonia.Data.Converters;

namespace Oedon.Core.UI.Converters;

public class MultiEnumerationConverter : IMultiValueConverter
{
    public object? Convert(IList<object?> values, Type targetType, object? parameter, CultureInfo culture)
    {
        List<object?> result = new();
        
        foreach (var item in values)
        {
            if (item is IEnumerable enumerable)
            {
                foreach (var subitem in enumerable)
                {
                    result.Add(subitem);
                }
            }
            else if (item is UnsetValueType)
            {
                // Do nothing
            }
            else
            {
                result.Add(item);
            }
        }

        return result;
    }
}