#ifndef ITEM_TV_HPP
#define ITEM_TV_HPP

#include "../item.hpp"

class ItemTVOnOffButton: public Item{
public:
    ItemTVOnOffButton(Anim* a, float layer=-5.0)
    :Item(a, TV_ON_OFF, layer)
    {
        draggable=false;
    }

    void onClick() override {
        shouldBeChanged=true;
    }

    bool shouldBeChanged = false;
};

class ItemTVScreen: public Item{
public:
    ItemTVScreen(Anim* a, float layer=-1.0)
    :Item(a, TV, layer)
    {

    }

    void onClick() override {

    }
};

class ItemTV: public Item{
public:
    ItemTV(Anim* a, ItemTVScreen* screen, ItemTVOnOffButton* onoff, float layer=-1.0)
    :Item(a, TV, layer), itemScreen(screen), itemOnOff(onoff)
    {

    }

    void changeState() override {
        enabled = ! enabled;
        if(enabled)
            state = BROKEN;
        else
            state = DEFAULT;
    }

    void onClick() override {

    }

    void update(sf::Time dt){
        if(itemOnOff->shouldBeChanged){
            itemOnOff->shouldBeChanged=false;
            changeState();
        }
        if(enabled){
            itemScreen->setColor(Utils::randColor());
        }
        else{
            itemScreen->setColor(sf::Color::White);
        }
    }

    ItemTVScreen* itemScreen;
    ItemTVOnOffButton* itemOnOff;
    bool enabled=false;
};

#endif // ITEM_TV_HPP
