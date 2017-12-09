#include "itemTrash.hpp"

ItemTrash::ItemTrash(Anim *a, float _layer)
    :Item(a, Item::TRASH, _layer),
      clickable(false)
{
    // WOW CONGRATS YOU CONSTRUCTED TRASH
}

void ItemTrash::changeState() {

}
