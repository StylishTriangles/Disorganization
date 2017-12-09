#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>


#include "game.hpp"
int main()
{
    Game g(1280, 720, "kotel");
    g.run();
    return 0;
}
