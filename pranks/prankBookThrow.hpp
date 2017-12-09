#ifndef PRANK_BOOK_THROW_HPP
#define PRANK_BOOK_THROW_HPP

#include "../Prank.hpp"

class PrankBookThrow: public Prank{
public:
    PrankBookThrow(std::map<std::string, Item*>* its);
    bool isAvailable() override;
    void onStart() override;
    void onFinish() override;
};

#endif // PRANK_BOOK_THROW_HPP
