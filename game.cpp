#include "game.hpp"

#include "pranks/prankBookThrow.hpp"

#include "items/itemPot.hpp"

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
            executeMouseEvents(&event);
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
    if (cat.isIdle())
	{
		if (Utils::chance(0.01))
		{
			int availablePranks = 0;
			for (auto p : pranks) {
				availablePranks += p->isAvailable();
			}
			if (availablePranks == 0) {
				///WYGRA£EŒ
			}
			int i;
			//do
			//{
			//	i = Utils::randInt(0, pranks.size());
			//}
			//while (pranks[i]->isAvailable());
			//cat.setNextPrank(pranks[i]);
		}
    }
}

void Game::executeMouseEvents(sf::Event* ev){
    if (ev->type == sf::Event::MouseButtonPressed){
        if (ev->mouseButton.button == sf::Mouse::Left){
            isMouseDown=true;
            for(const auto& p: items){
                if(Utils::isMouseOnSprite(*p.second, &window)){
                    isMouseDown=true;
                    p.second->onClick();
                    draggedItem = p.second;
                }
            }
        }
    }
    if (ev->type == sf::Event::MouseMoved){
        if(isMouseDown && draggedItem != nullptr){
            draggedItem->onDrag(ev->mouseMove.x, ev->mouseMove.y);
        }
    }
    if(ev->type == sf::Event::MouseButtonReleased){
        if (ev->mouseButton.button == sf::Mouse::Left && isMouseDown==true && draggedItem != nullptr){
            isMouseDown=false;
            draggedItem->onDrop();
            draggedItem=nullptr;
        }
    }
}

void Game::createObjects(){
    assets.cat.loadFromFile("files/graphics/tajny_wspolpracownik.png");


    anims["testCat"] = new Anim(&assets.cat);
    items["test"] = new ItemPot(anims["testCat"]);

    pranks.push_back(new PrankBookThrow(&items));
}
