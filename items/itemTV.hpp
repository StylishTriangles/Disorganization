#ifndef ITEM_TV_HPP
#define ITEM_TV_HPP

#include "../item.hpp"

class ItemTVScreen: public Item{
public:
    ItemTVScreen(Anim* a, float layer=-1.0)
    :Item(a, TV, layer)
    {

    }

    void onClick() override {
        std::cout << "tv clicked\n";
    }
};

class ItemTV: public Item{
public:
    ItemTV(Anim* a, ItemTVScreen* screen, float layer=-1.0)
    :Item(a, TV, layer), itemScreen(screen)
    {

    }

    void onClick() override {
        enabled = !enabled;
        if(!enabled)
            SoundHandler::playSound(Sounds::tv_off);
    }

    void update(sf::Time dt){
        if(enabled){
            itemScreen->setColor(Utils::randColor());
        }
        else{
            itemScreen->setColor(sf::Color::White);
        }
    }

    ItemTVScreen* itemScreen;
    bool enabled=false;
};

#endif // ITEM_TV_HPP
