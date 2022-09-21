


namespace Oedon::Editor
{
    struct BlueprintViewModel;

    class BlueprintView
    {
    public:

        void View(BlueprintViewModel* vm);

    private:
        int _createNodeSelected = 0;
    };
}