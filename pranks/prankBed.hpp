#ifndef PRANK_BED_HPP
#define PRANK_BED_HPP

#include "../Prank.hpp"
#include "../item.hpp"
#include "../items/itemBed.hpp"

class PrankBed : public Prank
{
  public:
    PrankBed(Game *g);
    bool isAvailable() override;
    void onStart() override;
    void onFinish() override;
};

#endif // PRANK_BED_HPP
