#ifndef ITEM_HPP
#define ITEM_HPP

#include "AnimatedSprite.hpp"
#include "soundBuffer_container.hpp"
#include "soundHandler.hpp"
#include "effectHandler.hpp"
#include "texture_container.hpp"


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
        TREE,
        GAMEPAD,
        BED,
        RADIO,
        ONOFF_BUTTON,
        TV,
        TABLE,
        CD
	};

	enum ItemState {
        ERRORSTATE  = 0,
        BROKEN      = 1,
        DEFAULT     = 1<<1,
        DELETED     = 1<<2,
        TRASHED     = 1<<3,
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
