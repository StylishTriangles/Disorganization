#ifndef ITEM_CLOCK_SH
#define ITEM_CLOCK_SH

#include "../item.hpp"

class ItemClockHand: public Item{
public:
    ItemClockHand(Anim* a, float layer=-1.0)
    :Item(a, CLOCK_HAND, layer)
    {
        setScale(0.5, 0.5);
    }

    void onClick() override {
        std::cout << "clock hand clicked\n";
    }
};

class ItemClock: public Item{
public:
    ItemClock(Anim* a, ItemClockHand* clockHand, float* timeLeft, float* totalTime, float layer=0.0)
    :Item(a, CLOCK, layer), itemClockHand(clockHand), secondsLeft(timeLeft), secondsTotal(totalTime)
    {
        itemClockHand->setOrigin(0, itemClockHand->getLocalBounds().height/2.0f);
        itemClockHand->setRotation(270);
    }

    void onClick() override {
        std::cout << "clock clicked\n";
        SoundHandler::playSound(Sounds::tik_tok);
    }

    void update(sf::Time dt) override {
        itemClockHand->setPosition(getPosition());
        //itemClockHand->rotate(dt.asSeconds());
        itemClockHand->setRotation(270.0 + 360.0*(*secondsLeft/ *secondsTotal));
    }

    ItemClockHand* itemClockHand;
    float* secondsLeft;
    float* secondsTotal;
};

#endif // ITEM_CLOCK_SH
