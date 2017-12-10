//#pragma once
#include "../item.hpp"

class ItemTree : public Item {
public:
    ItemTree(Anim* a, float _layer=2.9f);

    void onClick() override;
    void onDrop() override;
};
