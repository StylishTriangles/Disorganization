#include "prankBookThrow.hpp"

#include "../game.hpp"

PrankBookThrow::PrankBookThrow(Game* g)
:Prank(g)
{
	std::vector<Item*> books;
	for (auto item : game->items) {
		if (item.second->type == Item::BOOK && item.second->state == Item::DEFAULT) {
			books.push_back(item.second);
		}
	}
	activeItem = books[Utils::randInt(0, books.size())];
	catAnim = g->anims["catPrankBookThrow"];
	prankTime = 3000;
}

bool PrankBookThrow::isAvailable(){
	for (auto item : game->items) {
		if (item.second->type == Item::BOOK && item.second->state == Item::DEFAULT) {
			return true;
		}
	}
	return false;
}

void PrankBookThrow::onStart() {

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
