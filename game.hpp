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
#include "cat.hpp"
#include "Utils.hpp"

class Game {
public:
	Game(int width, int height, std::string title);
	~Game();
	sf::RenderWindow window;
	void run();
	void executeMouseEvents(sf::Event* ev);
	void createObjects();
	void draw(sf::Time);

	sf::Event event;
    TextureContainer assets;
    sf::Clock deltaClock;

    std::vector<Prank*> pranks;
    std::map<std::string, Item*> items;
    std::map<std::string, Anim*> anims;

    Cat cat;

protected:
    bool isMouseDown=false;
    Item* draggedItem=nullptr;
};

#endif // GAME_HPP
