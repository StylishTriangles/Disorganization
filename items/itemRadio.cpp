#include "itemRadio.hpp"

#include "../Game.hpp"

ItemCD::ItemCD(Anim* a, bool isFirst, ItemRadio* ir, float layer)
:Item(a, CD, layer), itemRadio(ir), isFirstAlbum(isFirst)
{

}

void ItemCD::onClick(){

}

void ItemCD::onDrop(){
    if(Collision::PixelPerfectTest(*itemRadio, *this)){
        itemRadio->changeState();
    }
}

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
    changeState();
    //setScale(0.5, 0.5);
}

void ItemRadio::onClick() {

}

void ItemRadio::update(sf::Time dt){
    game->items["radioOnOff"]->setPosition(this->getPosition()+sf::Vector2f(0, 20));
    int targetRoom=0;
    if(getPosition().x > Settings::windowSize.x)
        targetRoom=1;
    if(getPosition().x > Settings::windowSize.x*2)
        targetRoom=2;
    if(Settings::room == targetRoom){
        game->music.setVolume(30);
    }
    else{
        game->music.setVolume(8);
    }
}

void ItemRadio::changeState(){
    track1=!track1;
    if(track1){
        game->music.openFromFile("files/tunes/disorganization2.ogg");
    }
    else{
        game->music.openFromFile("files/tunes/disorganization.ogg");
    }
    game->music.setLoop(true);
    game->music.play();
}
