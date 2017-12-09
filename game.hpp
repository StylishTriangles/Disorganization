#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "prank.hpp"
#include "item.hpp"

class Game {
public:
	Game(int width, int height, std::string title);
	sf::RenderWindow window;
	void run();
	void draw();


    std::vector<Prank*> pranks;
    std::map<std::string, Item*> items;
    std::map<std::string, Anim*> anims;
};

#endif // GAME_HPP
