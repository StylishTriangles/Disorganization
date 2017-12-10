#include "prankBed.hpp"

#include "../game.hpp"

PrankBed::PrankBed(Game *g)
    : Prank(g)
{

    catAnim = g->anims["catPrankBed"];
}

bool PrankBed::isAvailable()
{
    prankTime = 4000;
    std::vector<Item *> beds;
    for (auto item : game->items)
    {
        if (item.second->type == Item::BED && item.second->state == Item::DEFAULT)
        {
            beds.push_back(item.second);
        }
    }
    if (beds.empty())
        return false;
    else
    {
        activeItem = beds[Utils::randInt(0, beds.size())];
        return true;
    }
}

void PrankBed::onStart()
{
    SoundHandler::playSound(Sounds::steppy);
}

void PrankBed::onFinish()
{
    available = false;
    std::vector<Item *> beds;
    for (auto item : game->items)
    {
        if (item.second->type == Item::BED && item.second->state == Item::DEFAULT)
        {
            beds.push_back(item.second);
        }
    }
    if (beds.empty())
        activeItem = nullptr;
    else
        activeItem = beds[Utils::randInt(0, beds.size())];
}
