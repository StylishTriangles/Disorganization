#include "prankBookThrow.hpp"

#include "../game.hpp"

PrankBookThrow::PrankBookThrow(Game* g)
:Prank(g)
{
	catAnim = g->anims["catPrankBookThrow"];
}

bool PrankBookThrow::isAvailable(){
	prankTime = 3000;
	std::vector<Item*> books;
	for (auto item : game->items) {
		if (item.second->type == Item::BOOK && item.second->state == Item::DEFAULT) {
			books.push_back(item.second);
		}
	}
	if (books.empty())
		return false;
	else {
		activeItem = books[Utils::randInt(0, books.size())];
		return true;
	}
}

void PrankBookThrow::onStart() {
	EffectHandler::addEffect(TextureContainer::spsSmoke, activeItem->getPosition(), 134, sf::milliseconds(100), 2, 5);
	SoundHandler::playSound(Sounds::scratch_paw);
	game->cat.flip();
}

void PrankBookThrow::onFinish() {
	available = false;
	std::vector<Item*> books;
	for (auto item : game->items) {
		if (item.second->type == Item::BOOK && item.second->state == Item::DEFAULT) {
			books.push_back(item.second);
		}
	}
	if(books.empty())
        activeItem=nullptr;
    else
        activeItem = books[Utils::randInt(0, books.size())];
}
