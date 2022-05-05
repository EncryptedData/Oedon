namespace Oedon.Core.UI.Controls;

public class BlueprintNodeTraveler
{
    public BlueprintNodeTraveler(Action<BlueprintNodeVM> func, Action<BlueprintPinVM> pinFunc)
    {
        _func = func;
        _pinFunc = pinFunc;
    }

    public void Travel(BlueprintNodeVM startingNode, BlueprintNodeTravelDirection direction)
    {
        if (startingNode is null)
        {
            throw new ArgumentNullException(nameof(startingNode));
        }
        
        // Reset from previous travel
        _toVisit.Clear();
        _visited.Clear();

        _toVisit.Push(startingNode);    

        while (_toVisit.Any())
        {
            var node = _toVisit.Pop();
            
            VisitNode(node, direction);
        }
    }

    private void VisitNode(BlueprintNodeVM node, BlueprintNodeTravelDirection direction)
    {
        // Visit all the InputPins if we want to travel there
        if (direction != BlueprintNodeTravelDirection.Outputs)
        {
            AddConnectedNodes(node.InputPins);
        }

        // Visit all the OutputPins if we want to travel there
        if (direction != BlueprintNodeTravelDirection.Inputs)
        {
            AddConnectedNodes(node.OutputPins);
        }

        _func?.Invoke(node);
        
        _visited.Add(node);
    }

    private void AddConnectedNodes(IEnumerable<BlueprintPinVM> pins)
    {
        if (pins is null)
        {
            return;
        }

        foreach (var pin in pins)
        {
            // Visit this pin
            _pinFunc?.Invoke(pin);
            
            if (pin.Connection is null)
            {
                continue;
            }

            BlueprintNodeVM connectedNode = null;
            
            switch (pin.PinType)
            {
                case BlueprintPinType.Input:
                    connectedNode = pin.Connection.InputPin.Parent;
                    break;
                case BlueprintPinType.Output:
                    connectedNode = pin.Connection.OutputPin.Parent;
                    break;
            }

            if (!_visited.Contains(connectedNode))
            {
                _toVisit.Push(connectedNode);
            }
        }
    }
    
    private readonly List<BlueprintNodeVM> _visited = new();
    private readonly Stack<BlueprintNodeVM> _toVisit = new();
    private readonly Action<BlueprintNodeVM> _func;
    private readonly Action<BlueprintPinVM> _pinFunc;

}