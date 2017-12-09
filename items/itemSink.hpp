#ifndef ITEM_SINK_HPP
#define ITEM_SIN_HPP

#include "../item.hpp"

class Game;

class ItemSink: public Item{
public:
    ItemSink(Anim* a, Game* g, float layer=0.0);

    void onClick() override ;
    Game* game;
};

#endif // ITEM_SINK_HPP
