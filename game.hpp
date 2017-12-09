#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

#include "prank.hpp"
#include "item.hpp"
#include "texture_container.hpp"

class Game {
public:
	Game(int width, int height, std::string title);
	~Game();
	sf::RenderWindow window;
	void run();
	void createObjects();
	void draw();

	sf::Event event;
    TextureContainer assets;

    std::vector<Prank*> pranks;
    std::map<std::string, Item*> items;
    std::map<std::string, Anim*> anims;
};

#endif // GAME_HPP
