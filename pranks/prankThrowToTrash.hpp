#ifndef PRANK_THROW_TO_TRASH_HPP
#define PRANK_THROW_TO_TRASH_HPP

#include "../prank.hpp"

class PrankThrowToTrash: public Prank{
public:
    PrankThrowToTrash(Game* g);

    bool isAvailable() override;
    void onFinish() override;
    void onPranking(sf::Time dt) override;
};

#endif // PRANK_THROW_TO_TRASH_HPP
