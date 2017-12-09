#include "game.hpp"

#include "pranks/prankBookThrow.hpp"

#include "items/itemPot.hpp"
#include "items/itemDoor.hpp"
#include "items/itemClock.hpp"
#include "items/itemSink.hpp"
#include "items/itemPool.hpp"
#include "items/itemTrash.hpp"

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
    secondsPassed += (dT.asSeconds()/1.0)*timeSpeed;

	window.draw(roomSprite);
    drawStats();
    window.setView(view);

    for (auto it = items.cbegin(); it != items.cend(); ){
        if (it->second->state == Item::DELETED){
            items.erase(it++);
        }
        else
            ++it;
    }

    std::vector<Item*> vItems;
    vItems.reserve(items.size());
    for(const auto& p: items) {
        p.second->update(dT);
        vItems.push_back(p.second);
    }
    std::sort(vItems.rbegin(), vItems.rend(), Item::cmpLayer);
    for(Item *item: vItems) {
        window.draw(*item);
        Utils::drawBoundingBox(*item, &window);
    }

    window.draw(cat);
    if (cat.isIdle()) {
		if (Utils::chance(1)) {
			int availablePranks = 0;
			for (auto p : pranks) {
				availablePranks += p->isAvailable();
			}
			if (availablePranks != 0) {
                int i;
                do{
                    i = Utils::randInt(0, pranks.size());
                }
                while (!pranks[i]->isAvailable());

                cat.setNextPrank(pranks[i]);
			}
            else{

            }
		}
    }
    cat.update(dT);
}

void Game::executeMouseEvents(sf::Event* ev){
    if (ev->type == sf::Event::MouseButtonPressed){
        if (ev->mouseButton.button == sf::Mouse::Left){
            if(Utils::isMouseOnSprite(cat, &window) && hasWaterGun){
                shotWater();
            }
            else{
                isMouseDown=true;
                lastMouseX = window.mapPixelToCoords(sf::Mouse::getPosition(window)).x;
                lastMouseY = window.mapPixelToCoords(sf::Mouse::getPosition(window)).y;
                bool shouldMakePool=true;
                for(const auto& p: items){
                    if(Utils::isMouseOnSprite(*p.second, &window)){
                        shouldMakePool=false;
                        isMouseDown=true;
                        if(p.second->clickable)
                            p.second->onClick();
                        if(p.second->draggable)
                            draggedItem = p.second;
                    }
                }
                if(shouldMakePool && hasWaterGun){
                    ItemPool* pool = new ItemPool(anims["pool"]);
                    pool->setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x,
                                      window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
                    items["pool"+Utils::stringify(objectNamesCtr)] = pool;
                    objectNamesCtr++;
                    hasWaterGun=false;
                }
            }
        }
    }
    if (ev->type == sf::Event::MouseMoved){
        if(isMouseDown && draggedItem != nullptr){
            sf::Vector2f temp = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            draggedItem->onDrag(temp.x - lastMouseX,
                                temp.y - lastMouseY);
            lastMouseX = temp.x;
            lastMouseY = temp.y;
        }
    }

    if(ev->type == sf::Event::MouseButtonReleased){
        if (ev->mouseButton.button == sf::Mouse::Left && isMouseDown==true && draggedItem != nullptr){
            bool dumped=false;
            for(const auto& p: items){
                if(draggedItem->type != Item::TRASH && p.second->type == Item::TRASH && Collision::PixelPerfectTest(*draggedItem, *p.second)){
                    dumped = true;
                    draggedItem->onTrash();
                    std::cout << "on trash\n";
                }

            }
            if(!dumped)
                draggedItem->onDrop();

            isMouseDown=false;
            draggedItem=nullptr;
        }
    }
}

void Game::drawStats(){
    std::string str = "Time left " + Utils::stringifyf(totalTimeInSeconds - secondsPassed) + "s";

    sf::Text textMum(str, font);
    textMum.setColor(sf::Color::Red);
    textMum.setCharacterSize(20);
    window.draw(textMum);
}

void Game::shotWater(){
    hasWaterGun=false;
    cat.getRekt();
}

void Game::createObjects(){
    assets.pot.loadFromFile("files/graphics/doniczka.png");
    assets.catIdle.loadFromFile("files/graphics/catIdle.png");
    assets.catMove.loadFromFile("files/graphics/catMove.png");
    assets.room1.loadFromFile("files/graphics/pokoj.png");
    assets.room2.loadFromFile("files/graphics/pokoj2.png");
    assets.catPrankBookThrow.loadFromFile("files/graphics/catPrankBookThrow.png");
    assets.doorRight.loadFromFile("files/graphics/drzwi_prawe.png");
    assets.clock.loadFromFile("files/graphics/clock.png");
    assets.clockHand.loadFromFile("files/graphics/clockhand.png");
    assets.sink.loadFromFile("files/graphics/sink.png");
    assets.pool.loadFromFile("files/graphics/pool0.png");
    assets.trash.loadFromFile("files/graphics/trash.png");

    anims["pot"] = new Anim(&assets.pot);
    anims["catIdle"] = new Anim(&assets.catIdle);
    anims["catPrankBookThrow"] = new Anim(&assets.catPrankBookThrow);
    anims["catMove"] = new Anim(&assets.catMove, 170, sf::milliseconds(300));
    anims["door"] = new Anim(&assets.doorRight);
    anims["clock"] = new Anim(&assets.clock);
    anims["clockHand"] = new Anim(&assets.clockHand);
    anims["sink"] = new Anim(&assets.sink);
    anims["pool"] = new Anim(&assets.pool);
    anims["trash"] = new Anim(&assets.trash);

    items["pot"] = new ItemPot(anims["pot"], 1.0f);
    items["pot"]->move(600, 100);
    items["pot2"] = new ItemPot(anims["pot"], 1.0f);
    items["pot2"]->move(200, 400);
    items["pot3"] = new ItemPot(anims["pot"], 1.0f);
    items["pot3"]->move(400, 200);

    ItemClockHand* itemClockHand = new ItemClockHand(anims["clockHand"], 1.0f);
    items["clockHand"] = itemClockHand;
    items["clock"] = new ItemClock(anims["clock"], itemClockHand, &secondsPassed, &totalTimeInSeconds, 1.0f);
    items["clock"]->setPosition(200, 100);
    items["clock"]->setScale(0.4, 0.4);

    ItemDoor* doorRight = new ItemDoor(anims["door"], false, 1.0f);
    doorRight->setGame(this);
    items["doorRight"] = doorRight;
    items["doorRight"]->move(1150, 400);

    ItemDoor* doorLeftSecondRoom = new ItemDoor(anims["door"], true, 1.0f);
    doorLeftSecondRoom->setScale(-1, 1);
    doorLeftSecondRoom->setGame(this);
    items["doorLeftSecondRoom"] = doorLeftSecondRoom;
    items["doorLeftSecondRoom"]->move(130+1280, 400);

    items["sink"] = new ItemSink(anims["sink"], this, 1.0f);
    items["sink"]->move(600+1280, 100);

    items["trash1"] = new ItemTrash(anims["trash"], 1.0f);
    items["trash1"]->move(300, 500);

    pranks.push_back(new PrankBookThrow(this));

    roomSprite = sf::Sprite(assets.room2);
    roomSprite.setScale(window.getSize().x * 2.0f / roomSprite.getGlobalBounds().width,
                        window.getSize().y / roomSprite.getGlobalBounds().height);
    font.loadFromFile("files/fonts/Digital_7.ttf");

    cat.move(640, 400);
}
