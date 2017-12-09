#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>

class Game {
public:
	Game(int width, int height, std::string title);
	sf::RenderWindow window;
	void run();
	void draw();
};
