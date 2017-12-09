#include "game.hpp"

#include "pranks/prankBookThrow.hpp"

#include "items/itemPot.hpp"

Game::Game(int width, int height, std::string title)
:window(sf::VideoMode(width, height), title)
{
	window.setFramerateLimit(60);
    createObjects();
    cat.create(anims);
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
		draw(deltaClock.restart());
		window.display();
	}
}

void Game::draw(sf::Time dT){
	std::cout << dT.asMilliseconds() << std::endl;
    for(const auto& p: items){
        window.draw(*p.second);
        Utils::drawBoundingBox(*p.second, &window);
    }
    window.draw(cat);
    if (cat.isIdle())
	{
		if (Utils::chance(1))
		{
			int availablePranks = 0;
			for (auto p : pranks) {
				availablePranks += p->isAvailable();
			}
			if (availablePranks == 0) {
				///Winner winner chicken dinner
				std::cout << "cookol";
			}
			int i;
			do
			{
				i = Utils::randInt(0, pranks.size());
			}
			while (!pranks[i]->isAvailable());

			cat.setNextPrank(pranks[i]);
		}
    }
    cat.update(dT);
}

void Game::executeMouseEvents(sf::Event* ev){
    if (ev->type == sf::Event::MouseButtonPressed){
        if (ev->mouseButton.button == sf::Mouse::Left){
            isMouseDown=true;
            lastMouseX = ev->mouseButton.x;
            lastMouseY = ev->mouseButton.y;
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
            draggedItem->onDrag(ev->mouseMove.x-lastMouseX, ev->mouseMove.y-lastMouseY);
            lastMouseX = ev->mouseMove.x;
            lastMouseY = ev->mouseMove.y;
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
    assets.pot.loadFromFile("files/graphics/doniczka.png");
    assets.catIdle.loadFromFile("files/graphics/catIdle.png");


    anims["pot"] = new Anim(&assets.pot);
    anims["catIdle"] = new Anim(&assets.catIdle);

    items["pot"] = new ItemPot(anims["pot"]);
    items["pot"]->move(100, 100);

    pranks.push_back(new PrankBookThrow(&items));
}
