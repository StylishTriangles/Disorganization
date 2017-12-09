#include "game.hpp"

#include "pranks/prankBookThrow.hpp"

Game::Game(int width, int height, std::string title)
:window(sf::VideoMode(width, height), title)
{
	window.setFramerateLimit(60);
    createObjects();
}

Game::~Game(){
    for(const auto& p: items)
        delete p.second;
    for(const auto& p: anims)
        delete p.second;
    for(const auto& p: pranks)
        delete p;
}

void Game::run() {
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                window.close();
			}
            else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                window.close();
            }
		}
		window.clear(sf::Color::Black);
		draw();
		window.display();
	}
}

void Game::draw(){
    for(const auto& p: items){
        window.draw(*p.second);
    }
}

void Game::createObjects(){
    assets.cat.loadFromFile("files/graphics/kot.png");


    anims["testCat"] = new Anim(&assets.cat);
    items["test"] = new Item(anims["testCat"]);

    pranks.push_back(new PrankBookThrow(&items));
}
