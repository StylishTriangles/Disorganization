#ifndef EFFECTHANDLER_HPP
#define EFFECTHANDLER_HPP

#include "AnimatedSprite.hpp"

class EffectHandler{
public:

    static void update(double delta) {
		for (int i = effects.size()-1; i >=0; i--) {
			effects[i]->update(delta);
			if (effects[i]->shouldDestroy()) {
				delete effects[i];
				effects.erase(effects.begin()+i);
				anims.erase(anims.begin()+i);
			}
		}
    }

    static void addEffect(sf::Texture& sps, sf::Vector2f position, int frameWidth, sf::Time dur, float scale = 1.0f) {
    	Anim* a = new Anim(&sps, frameWidth, dur);
    	AnimSprite* aS = new AnimSprite(a, false);
    	aS->centerOrigin();
    	aS->setPosition(position);
    	aS->setScale(scale, scale);
    	effects.push_back(aS);
    	anims.push_back(a);
    }

    static void draw(sf::RenderTarget* target) {
		for (int i = effects.size()-1; i >=0; i--) {
			target->draw(*effects[i]);
		}
	}

protected:

    static std::vector<AnimSprite* > effects;
    static std::vector<Anim*> anims;

};

#endif // EFFECTHANDLER_HPP
