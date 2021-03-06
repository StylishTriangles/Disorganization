#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>

#include "prank.hpp"
#include "item.hpp"
#include "texture_container.hpp"
#include "soundBuffer_container.hpp"
#include "soundHandler.hpp"
#include "cat.hpp"
#include "Utils.hpp"
#include "Collision.hpp"
#include "Settings.hpp"

class Game {
public:
    enum GameState{
        INTRO,
        GAME,
        OUTRO
    };

	Game(int width, int height, std::string title);
	~Game();
	sf::RenderWindow window;
	void run();
	void executeMouseEvents(sf::Event* ev);
	void createObjects();
	void introLogic(sf::Time);
	void gameLogic(sf::Time);
	void draw(sf::Time);
    void drawStats();
    void shotWater();
    void setupOutro();
    int calcMessiness();

	sf::Event event;
    TextureContainer assets;
    sf::Clock deltaClock;

    std::vector<Prank*> pranks;
    std::map<std::string, Item*> items;
    std::map<std::string, Anim*> anims;
    std::vector<Item*> vItems; // items sorted by layer

    Cat cat;
    sf::Sprite roomSprite;
    sf::View view;
    bool hasWaterGun=true;
    int objectNamesCtr=0;
    sf::Music music;

protected:
    unsigned int gameState = INTRO;
    bool introClockStarted=false;
    bool isMouseDown=false;
    int lastMouseX, lastMouseY;
    Item* draggedItem=nullptr;

    sf::Font font;
    float secondsPassed=0;
    float totalTimeInSeconds=60*2;
    float timeSpeed = 1;
    AnimSprite mom;
    AnimSprite momCloud;
    sf::Text momText;
    sf::Text countText;
    sf::Clock introClock;
    sf::Sprite pointer;

};

#endif // GAME_HPP
