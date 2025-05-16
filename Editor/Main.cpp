#include "Editor.hpp"

int main()
{ 
    Editor* l_editor = new Editor();

    l_editor->Init();
    l_editor->Update();
    l_editor->Destroy();

    delete l_editor;

    l_editor = nullptr;
    return 0;
}