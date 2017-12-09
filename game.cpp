#include "game.hpp"

Game::Game(int width, int height, std::string title)
:window(sf::VideoMode(width, height), title)
{
	window.setFramerateLimit(60);
}

void Game::run() {
	while (window.isOpen()) {
		window.clear(sf::Color::Black);
		draw();
		window.display();
	}
}

void Game::draw(){

}

