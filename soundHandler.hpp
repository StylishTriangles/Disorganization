
#ifndef SOUNDHANDLER_HPP
#define SOUNDHANDLER_HPP

#include "SFML/Audio.hpp"

class SoundHandler{
public:

    static std::vector<sf::Sound*> playedSounds;

    static void update() {
		for (int i = playedSounds.size()-1; i >=0; i--) {
			if (playedSounds[i]->getStatus() == sf::Sound::Stopped) {
				delete playedSounds[i];
				playedSounds.erase(playedSounds.begin()+i);
			}
		}
    }

    static void playSound(sf::SoundBuffer& buffer, bool looped = false) {
		sf::Sound* sound = new sf::Sound(buffer);
		sound->setLoop(looped);
		sound->play();
		playedSounds.push_back(sound);
    }
};

#endif // SOUNDHANDLER_HPP
