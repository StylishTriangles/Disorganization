#ifndef ITEM_HPP
#define ITEM_HPP

#include "AnimatedSprite.hpp"



class Item: public AnimSprite{
public:
	enum ItemType {
		BOOK,
		GLASS
	};

	enum ItemState {
		BROKEN,
		DEFAULT
	};

    Item(Anim* a, ItemType i, float _layer = 1.0f);
    virtual ~Item() = default;

    bool clickable;
    bool dragndrop;
    float layer;
    ItemType type;
    ItemState state = DEFAULT;

    virtual void onClick() = 0;
    virtual void onDrag(int dx, int dy);
    virtual void onDrop();
    virtual void changeState() = 0;

    static bool cmpLayer(Item* lhs, Item* rhs) {
        return lhs->layer < rhs->layer;
    }
};

#endif // ITEM_HPP
