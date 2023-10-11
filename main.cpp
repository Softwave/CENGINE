#include <iostream>
#include <GL/gl.h>
#include "cengine.h"
#include "imgui.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

class MyGame : public Cengine
{
    public:
        void Draw();
};

void MyGame::Draw()
{

}




int main(int, char**)
{
    MyGame* cengine = new MyGame();

    cengine->Init(WINDOW_WIDTH, WINDOW_HEIGHT, "CENGINE Test", true);
    cengine->CreateImgui();

    while (cengine->isRunning)
    {
        cengine->HandleInput();
        cengine->Update();
        cengine->UpdateGui();
        cengine->Draw();
    }

    cengine->Clean();

    return 0;
}
