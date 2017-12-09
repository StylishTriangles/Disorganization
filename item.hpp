#ifndef ITEM_HPP
#define ITEM_HPP

#include "AnimatedSprite.hpp"


class Item: public AnimSprite{
public:
	enum ItemType {
        BOOK,
        CLOCK,
        CLOCK_HAND,
        DOOR,
        GLASS,
        POOL,
        SINK,
        TRASH,
        GAMEPAD
	};

	enum ItemState {
		BROKEN,
		DEFAULT,
        DELETED,
        TRASHED,
	};

    Item(Anim* a, ItemType i, float _layer = 1.0f);
    virtual ~Item() = default;

    bool clickable=true;
    bool draggable=true;
    bool isTrashable=false;
    float layer;
    ItemType type;
    ItemState state = DEFAULT;


    virtual void update(sf::Time);
    virtual void onClick() = 0;
    virtual void onDrag(int dx, int dy);
    virtual void onDrop();
    virtual void onRightClick();
    virtual void onTrash(Item* trash);
    virtual void changeState();

    static bool cmpLayer(Item* lhs, Item* rhs) {
        return lhs->layer < rhs->layer;
    }
};

#endif // ITEM_HPP
