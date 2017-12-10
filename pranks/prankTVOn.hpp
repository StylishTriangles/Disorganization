#ifndef PRANK_TV_ON_HPP
#define PRANK_TV_ON_HPP

#include "../prank.hpp"

class Game;

class PrankTVOn: public Prank{
public:
    PrankTVOn(Game* g);

    bool isAvailable() override;
    void onFinish() override;
};

#endif // PRANK_TV_ON_HPP
