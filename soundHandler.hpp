
#ifndef SOUNDHANDLER_HPP
#define SOUNDHANDLER_HPP

#include "SFML/Audio.hpp"

class SoundHandler{
public:

    static void update() {
		for (int i = playedSounds.size()-1; i >=0; i--) {
			if (playedSounds[i]->getStatus() == sf::Sound::Stopped) {
				delete playedSounds[i];
				playedSounds.erase(playedSounds.begin()+i);
			}
		}
    }

    static void stop(sf::SoundBuffer& buffer) {
		for (int i = playedSounds.size()-1; i >=0; i--) {
			if (playedSounds[i]->getBuffer() == &buffer) {
				playedSounds[i]->stop();
			}
		}
    }

    static void playSound(sf::SoundBuffer& buffer, float volume = 100, bool looped = false) {
		sf::Sound* sound = new sf::Sound(buffer);
		sound->setLoop(looped);
		sound->play();
		sound->setVolume(volume);
		playedSounds.push_back(sound);
    }

protected:

    static std::vector<sf::Sound*> playedSounds;

};

#endif // SOUNDHANDLER_HPP
