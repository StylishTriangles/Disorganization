#ifndef ITEM_DOOR_HPP
#define ITEM_DOOR_HPP

#include "../item.hpp"

#include "../game.hpp"

class ItemDoor : public Item
{
public:
    ItemDoor(Anim *a, bool leftDoors, float layer);

    void onClick() override;

    void onDrag(int dx, int dy) override;

    void onDrop() override;

    void changeState() override;

    void setGame(Game *gam);


    bool leftDoors;
protected:
    Game* g;
};

#endif // ITEM_POT_HPP
