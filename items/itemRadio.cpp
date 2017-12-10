#include "itemRadio.hpp"

#include "../Game.hpp"

ItemOnOffButton::ItemOnOffButton(Anim* a, float layer)
:Item(a, ONOFF_BUTTON, layer)
{
    isTrashable=true;
}

void ItemOnOffButton::onClick() {
    if(game->music.getStatus() == sf::Music::Paused)
        game->music.play();
    else if(game->music.getStatus() == sf::Music::Playing)
        game->music.pause();
}

void ItemOnOffButton::setGame(Game* g){
    game=g;
}

ItemRadio::ItemRadio(Anim* a, ItemOnOffButton* of, Game* g, float layer)
:Item(a, RADIO, layer), game(g), onoff(of)
{
    isTrashable=true;
    onoff->setGame(g);
    //setScale(0.5, 0.5);
}

void ItemRadio::onClick() {

}

void ItemRadio::update(sf::Time dt){
    game->items["radioOnOff"]->setPosition(this->getPosition());
}
