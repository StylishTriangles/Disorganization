#ifndef PRANK_GLASS_HPP
#define PRANK_GLASS_HPP

#include "../Prank.hpp"
#include "../item.hpp"
#include "../items/itemGlass.hpp"

class PrankGlass : public Prank
{
  public:
    PrankGlass(Game *g);
    bool isAvailable() override;
    void onStart() override;
    void onFinish() override;
};

#endif // PRANK_GLASS_HPP
