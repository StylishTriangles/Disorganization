#include "itemSink.hpp"

#include "../game.hpp"

ItemSink::ItemSink(Anim* a, Game* g, float layer)
:Item(a, SINK, layer), game(g)
{
    draggable=false;
}

void ItemSink::onClick() {
    std::cout << "sink clicked\n";
    game->hasWaterGun = true;
}
