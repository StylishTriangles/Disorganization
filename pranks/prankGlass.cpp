#include "prankGlass.hpp"

#include "../game.hpp"

#include "../items/itemPool.hpp"

PrankGlass::PrankGlass(Game *g)
    : Prank(g)
{

    catAnim = g->anims["catPrankGlass"];
}

bool PrankGlass::isAvailable()
{
    prankTime = 500;
    std::vector<Item *> glass;
    for (auto item : game->items)
    {
        if (item.second->type == Item::GLASS && item.second->state == Item::DEFAULT)
        {
            glass.push_back(item.second);
        }
    }
    if (glass.empty())
        return false;
    else
    {
        activeItem = glass[Utils::randInt(0, glass.size())];
        return true;
    }
}

void PrankGlass::onStart()
{
    SoundHandler::playSound(Sounds::pef);
    SoundHandler::playSound(Sounds::plum);
    EffectHandler::addEffect(TextureContainer::spsSmoke, activeItem->getPosition(), 134, sf::milliseconds(100));
}

void PrankGlass::onFinish()
{
    activeItem->move(0, Settings::floorLevel - activeItem->getPosition().y);
    ItemPool *pool = new ItemPool(game->anims["pool"]);
    pool->setPosition(activeItem->getPosition().x, std::max(int(activeItem->getPosition().y), Settings::floorLevel));
    game->items["pool" + Utils::stringify(game->objectNamesCtr)] = pool;
    game->objectNamesCtr++;

    available = false;
    std::vector<Item *> glass;
    for (auto item : game->items)
    {
        if (item.second->type == Item::GLASS && item.second->state == Item::DEFAULT)
        {
            glass.push_back(item.second);
        }
    }
    if (glass.empty())
        activeItem = nullptr;
    else
        activeItem = glass[Utils::randInt(0, glass.size())];
}
