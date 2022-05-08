namespace Oedon.Core.UI.Attributes;

[AttributeUsage(AttributeTargets.Class)]
public class DocumentAttribute : Attribute
{
    public DocumentAttribute(string displayName)
    {
        DisplayName = displayName;
    }
    
    public string DisplayName { get; }
}