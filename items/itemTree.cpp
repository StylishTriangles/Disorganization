#include "itemTree.hpp"
#include <iostream>
using std::cout;

ItemTree::ItemTree(Anim *a, float _layer)
    :Item(a, TREE, _layer)
{}

void ItemTree::onClick(){

}

void ItemTree::onDrop() {
    //cout << this->getPosition().x << " " << this->getPosition().y << "\n";
}
