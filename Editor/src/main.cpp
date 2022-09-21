//
// Created by Russell Johnson on 9/4/22.
//

#include "SDLWindow.h"
#include "MainWindowView.h"
#include "MainWindowViewModel.h"

int main()
{
    Oedon::Editor::SDLWindow window{};
    Oedon::Editor::MainWindowViewModel mainWindowViewModel;
    Oedon::Editor::MainWindowView mainWindowView{&mainWindowViewModel.dispatcher};

    while(window.ShouldContinue())
    {
        window.Update();

        window.StartFrame();

        mainWindowView.View(&mainWindowViewModel);

        window.EndFrame();
    }

    return 0;
}