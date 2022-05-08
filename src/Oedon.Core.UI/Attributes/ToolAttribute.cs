namespace Oedon.Core.UI.Attributes;

[AttributeUsage(AttributeTargets.Class)]
public class ToolAttribute : Attribute
{
    public ToolAttribute(string displayName)
    {
        DisplayName = displayName;
    }
    
    public string DisplayName { get; }
}