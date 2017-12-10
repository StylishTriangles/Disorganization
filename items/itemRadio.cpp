#include "itemRadio.hpp"

#include "../Game.hpp"

ItemOnOffButton::ItemOnOffButton(Anim* a, float layer)
:Item(a, ONOFF_BUTTON, layer)
{

}

void ItemOnOffButton::onClick() {
    std::cout << "on off action\n";
}

ItemRadio::ItemRadio(Anim* a, ItemOnOffButton* onoff, Game* g, float layer)
:Item(a, RADIO, layer), game(g)
{
    //setScale(0.5, 0.5);
}

void ItemRadio::onClick() {
    std::cout << "radio clicked\n";
}

void ItemRadio::update(sf::Time dt){
    game->items["radioOnOff"]->setPosition(this->getPosition());
}
