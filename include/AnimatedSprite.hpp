#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Utils.hpp"

class Anim {
public:
    Anim () {}
    Anim (sf::Texture* SpriteSheet, int frameWidth, sf::Time dur) {
        spriteSheet = SpriteSheet;
        width = frameWidth;
        frames = spriteSheet->getSize().x/width;
        height = spriteSheet->getSize().y;
        frameDurations.resize(frames, dur);
    }
    Anim (sf::Texture* SpriteSheet) {
        spriteSheet = SpriteSheet;
        width = SpriteSheet->getSize().x;
        frames = 1;
        height = spriteSheet->getSize().y;
        frameDurations.resize(frames, sf::seconds(3600.0*24));
    }
    Anim (sf::Texture* SpriteSheet, int frameWidth, std::vector <sf::Time> framesDur) {
        spriteSheet = SpriteSheet;
        width = frameWidth;
        frames = spriteSheet->getSize().x/width;
        height = spriteSheet->getSize().y;
        frameDurations = framesDur;
    }
    sf::Texture* spriteSheet;
    std::vector <sf::Time> frameDurations;
    int frames;
    int width;
    int height;
    void setSpriteSheet (sf::Texture* t, int frameWidth, sf::Time dur) {
        spriteSheet = t;
        width = frameWidth;
        frames = spriteSheet->getSize().x/width;
        height = spriteSheet->getSize().y;
        frameDurations.resize(frames, dur);
    }
    void setSpriteSheet (sf::Texture* t, int frameWidth, std::vector <sf::Time> framesDur) {
        spriteSheet = t;
        width = frameWidth;
        frames = spriteSheet->getSize().x/width;
        height = spriteSheet->getSize().y;
        frameDurations = framesDur;
    }
    void setDurationVector(std::vector <sf::Time> framesDur) {
        frameDurations = framesDur;
    }
    void setFrameDuration(int frame, sf::Time t) {
        frameDurations[frame]=t;
    }
};

class AnimSprite: public sf::Sprite {
public:
    AnimSprite() {}
    AnimSprite(Anim* anim, bool looped = true) {
        setAnimation(anim);
        m_looped = looped;
    }
    bool isLooped() {return m_looped;}
    bool shouldDestroy() {return m_destroy;}
    int currentFrame = 0;
    void update (double delta) {
        runTime+=delta;
//            move(velocity);
        if (runTime*playSpeed > animation->frameDurations[currentFrame].asMilliseconds()) {
            runTime = 0;
            currentFrame++;
            if (currentFrame>=animation->frames) {
                if (m_looped) {
                    loops++;
                    currentFrame = 0;
                }
                else {
                    currentFrame--;
                    m_destroy = true;
                }
            }
            setTextureRect(sf::IntRect(currentFrame*animation->width, 0, animation->width, animation->height));
        }
        else if (runTime*playSpeed < -animation->frameDurations[currentFrame].asMilliseconds()) {
            runTime = 0;
            currentFrame--;
            if (currentFrame<0) {
                if (m_looped) {
                    loops++;
                    currentFrame = animation->frames-1;
                }
                else {
                    m_destroy = true;
                    currentFrame = 0;
                }
            }
            setTextureRect(sf::IntRect(currentFrame*animation->width, 0, animation->width, animation->height));
        }
    }
    void setAnimation(Anim* a) {
    	loops = 0;
        animation = a;
        currentFrame = 0;
        runTime = 0;
        setTexture(*(animation->spriteSheet));
        setTextureRect(sf::IntRect(0, 0, animation->width, animation->height));
    }
    void setLooped (bool t) {
        m_looped = t;
    }
    int getLoops () {
        return loops;
    }
    void setPlaySpeed (float speed) {
        playSpeed = speed;
        if (playSpeed<0) {
            currentFrame = animation->frames-currentFrame;
        }
    }
    float getPlaySpeed() {
        return playSpeed;
    }
    void playBack() {
        playSpeed = -playSpeed;
    }
    void centerOrigin() {
        setOrigin(getLocalBounds().width/2, getLocalBounds().height/2);
    }
    Anim* getAnim() {
        return animation;
    }
    void reset() {
        runTime = 0;
        loops = 0;
        m_destroy = false;
    }
    void nextFrame() {
        runTime = 0;
        currentFrame++;
        if (currentFrame>=animation->frames) {
            loops++;
            currentFrame = 0;
            if (!m_looped)
                m_destroy = true;
        }
        setTextureRect(sf::IntRect(currentFrame*animation->width, 0, animation->width, animation->height));
    }
    void setFrame(int a) {
        currentFrame = a;
        runTime=0;
        setTextureRect(sf::IntRect(currentFrame*animation->width, 0, animation->width, animation->height));
    }
    void flip() {
		setScale(-getScale().x, getScale().y);
		move(Utils::sgn(getScale().x)*getGlobalBounds().width/2, 0);
    }
protected:
    bool m_destroy = false;
    bool m_looped = true;
    Anim* animation;
    double runTime = 0;
    int loops = 0;
    float playSpeed = 1;
};


#endif // ANIMATED_SPRITE_H
