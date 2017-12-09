#include "game.hpp"

#include "pranks/prankBookThrow.hpp"

#include "items/itemPot.hpp"
#include "items/itemDoor.hpp"

Game::Game(int width, int height, std::string title)
    : window(sf::VideoMode(width, height), title), view(sf::FloatRect(0, 0, width, height))
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
    window.setView(view);
    window.draw(roomSprite);

    std::vector<Item*> vItems;
    vItems.reserve(items.size());
    for(const auto& p: items) {
        vItems.push_back(p.second);
    }
    std::sort(vItems.rbegin(), vItems.rend(), Item::cmpLayer);
    for(Item *item: vItems) {
        window.draw(*item);
        Utils::drawBoundingBox(*item, &window);
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
    assets.room1.loadFromFile("files/graphics/pokoj.png");
    assets.room2.loadFromFile("files/graphics/pokoj2.png");
    assets.catPrankBookThrow.loadFromFile("files/graphics/catPrankBookThrow.png");
    assets.doorRight.loadFromFile("files/graphics/drzwi_prawe.png");


    anims["pot"] = new Anim(&assets.pot);
    anims["catIdle"] = new Anim(&assets.catIdle);
    anims["catPrankBookThrow"] = new Anim(&assets.catPrankBookThrow);
    anims["doorRight"] = new Anim(&assets.doorRight);

    items["pot"] = new ItemPot(anims["pot"], 1.0f);
    items["pot"]->move(600, 100);
    ItemDoor* doorRight = new ItemDoor(anims["doorRight"], 1.0f);
    doorRight->setGame(this);
    items["doorRight"] = doorRight;
    items["doorRight"]->move(1150, 400);

    //items["pot2"] = new ItemPot(anims["pot"], -3.f);
    //items["pot2"]->move(100, 100);
    //items["pot3"] = new ItemPot(anims["pot"]);
    //items["pot3"]->move(200, 200);

    pranks.push_back(new PrankBookThrow(this));

    roomSprite = sf::Sprite(assets.room2);
    roomSprite.setScale(window.getSize().x * 2.0f / roomSprite.getGlobalBounds().width,
                        window.getSize().y / roomSprite.getGlobalBounds().height);

}
