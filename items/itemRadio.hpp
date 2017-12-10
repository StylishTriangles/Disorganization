#ifndef ITEM_RADIO_HPP
#define ITEM_RADIO_HPP

#include "../item.hpp"

class Game;

class ItemOnOffButton: public Item{
public:
    ItemOnOffButton(Anim* a, float layer=-5.0);

    void onClick() override ;
};

class ItemRadio: public Item{
public:
    ItemRadio(Anim* a, ItemOnOffButton* onoff, Game* g, float layer=0.0);

    void onClick() override ;
    void update(sf::Time dt) override ;

    Game* game;
};

#endif // ITEM_RADIO_HPP
