#include "prankThrowToTrash.hpp"

#include "../game.hpp"

PrankThrowToTrash::PrankThrowToTrash(Game* g)
:Prank(g)
{
    catAnim = g->anims["catPrankBookThrow"];
}

bool PrankThrowToTrash::isAvailable(){
	prankTime = 3600*1000*10;
	std::vector<Item*> gamepads;
	for (auto item : game->items) {
		if (item.second->type == Item::GAMEPAD && item.second->state == Item::DEFAULT) {
			gamepads.push_back(item.second);
		}
	}
	if (gamepads.empty())
		return false;
	else {
		activeItem = gamepads[Utils::randInt(0, gamepads.size())];
		return true;
	}
}

void PrankThrowToTrash::onFinish() {
    activeItem->onTrash(game->items["trash1"]);

	available = false;
	std::vector<Item*> gamepads;
	for (auto item : game->items) {
		if (item.second->type == Item::GAMEPAD && item.second->state == Item::DEFAULT) {
			gamepads.push_back(item.second);
		}
	}
	if(gamepads.empty())
        activeItem=nullptr;
    else
        activeItem = gamepads[Utils::randInt(0, gamepads.size())];
}

void PrankThrowToTrash::onPranking(sf::Time dT){
    Item* trash = game->items["trash1"];
    if(trash->getPosition().x > game->cat.getPosition().x){
        game->cat.travelDirection = direction::RIGHT;
        game->cat.setScale(abs(game->cat.getScale().x), game->cat.getScale().y);
    }
    else{
        game->cat.travelDirection = direction::LEFT;
        game->cat.setScale(-abs(game->cat.getScale().x), game->cat.getScale().y);
    }

    game->cat.move(Utils::normalized(trash->getPosition() - game->cat.getPosition()) * (float)dT.asMilliseconds() / 3.0f);
    sf::Vector2f addToHead = sf::Vector2f(-5, -30);
    if(game->cat.travelDirection == direction::RIGHT){
        addToHead = sf::Vector2f(game->cat.getGlobalBounds().width-160,-30);
    }
    activeItem->setPosition(game->cat.getPosition()+addToHead);

    if(Collision::PixelPerfectTest(*trash, game->cat)){
        prankTime = 0;
    }
    else{
        prankTime = 3600*1000*10;
    }
}
