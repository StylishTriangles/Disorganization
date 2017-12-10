#include "game.hpp"

#include "pranks/prankBookThrow.hpp"
#include "pranks/prankBed.hpp"
#include "pranks/prankGlass.hpp"
#include "pranks/prankThrowToTrash.hpp"

#include "items/itemPot.hpp"
#include "items/itemDoor.hpp"
#include "items/itemClock.hpp"
#include "items/itemSink.hpp"
#include "items/itemPool.hpp"
#include "items/itemTrash.hpp"
#include "items/itemGamepad.hpp"
#include "items/itemBed.hpp"
#include "items/itemRadio.hpp"
#include "items/itemTable.hpp"
#include "items/itemGlass.hpp"
#include "items/itemTree.hpp"

Game::Game(int width, int height, std::string title)
    : window(sf::VideoMode(width, height), title), view(sf::FloatRect(width, 0, width, height))
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
            if(introDone)
                executeMouseEvents(&event);
		}
		window.clear(sf::Color::Black);
		sf::Time dt = deltaClock.restart();
		if(!introDone)
            introLogic(dt);
		else{
            gameLogic(dt);
		}
		draw(dt);
		window.display();
	}
}

void Game::introLogic(sf::Time dT){
    mom.move(100*dT.asSeconds(), 0);
    momCloud.setPosition(mom.getPosition()+sf::Vector2f(175, -230));
    momText.setPosition(momCloud.getPosition());
    if(mom.getPosition().x >= Settings::windowSize.x*2+100){
        if(!introClockStarted){
            introClock.restart();
            introClockStarted=true;
        }
        if(!introDone && introClock.getElapsedTime().asSeconds() >= 4.0){
            introDone = true;
            //SoundHandler::playSound(Sounds::disorganization2, 50, true);
            music.play();
        }
    }
}

void Game::gameLogic(sf::Time dT){
    vItems.clear();
    for (auto it = items.cbegin(); it != items.cend(); ){
        if (it->second->state == Item::DELETED){
            items.erase(it++);
        }
        else {
            vItems.push_back(it->second);
            ++it;
        }
    }
    sort(vItems.rbegin(), vItems.rend(), Item::cmpLayer);
    if (cat.isIdle()) {
		if (Utils::chance(1.0/(60.0))) {
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
    SoundHandler::update();
    EffectHandler::update(dT.asMilliseconds());
    secondsPassed += (dT.asSeconds()/1.0)*timeSpeed;
}

void Game::draw(sf::Time dT){
    window.setView(view);
	window.draw(roomSprite);
    drawStats();
    window.draw(momCloud);
    window.draw(momText);
    window.draw(mom);
    if(introClockStarted && !introDone){
        if(introClock.getElapsedTime().asSeconds() < 4.0)
            countText.setString("Go Clean!\n");
        if(introClock.getElapsedTime().asSeconds() < 3.0)
            countText.setString("1...\n");
        if(introClock.getElapsedTime().asSeconds() < 2.0)
            countText.setString("2...\n");
        if(introClock.getElapsedTime().asSeconds() < 1.0)
            countText.setString("3...\n");
        countText.setPosition(Settings::windowSize.x*1.5 - countText.getGlobalBounds().width/2.f,
                          Settings::windowSize.y/2.0 - countText.getCharacterSize()/2.f);
        window.draw(countText);
    }

    for(Item *item: vItems) {
        item->update(dT);
        window.draw(*item);
        Utils::drawBoundingBox(*item, &window);
    }

    window.draw(cat);
    EffectHandler::draw(&window);
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
                for(Item* item: vItems){
                    if(Utils::isMouseOnSprite(*item, &window)){
                        shouldMakePool=false;
                        isMouseDown=true;
                        if(item->clickable)
                            item->onClick();
                        if(item->draggable)
                            draggedItem = item;
                    }
                }
                if(shouldMakePool && hasWaterGun){
                    ItemPool* pool = new ItemPool(anims["pool"]);
                    pool->setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x,
                                      std::max((int)window.mapPixelToCoords(sf::Mouse::getPosition(window)).y, Settings::floorLevel));
                    items["pool"+Utils::stringify(objectNamesCtr)] = pool;
                    objectNamesCtr++;
                    hasWaterGun=false;
                }
            }
        }
        else if (ev->mouseButton.button == sf::Mouse::Right){
            for(const auto& p: items){
                if(Utils::isMouseOnSprite(*p.second, &window)){
                    if(p.second->clickable)
                        p.second->onRightClick();
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
                if(draggedItem->isTrashable && draggedItem->type != Item::TRASH && p.second->type == Item::TRASH && Collision::PixelPerfectTest(*draggedItem, *p.second)){
                    dumped = true;
                    draggedItem->onTrash(p.second);
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
    int messiness = 0;
    for(const auto& it: items){
        if(it.second->state & Item::BROKEN){
            messiness+=2;
            if(it.second->state & Item::TRASHED){
                messiness--;
            }
        }
    }
    std::string str =   "Time left " + Utils::stringify((int)(totalTimeInSeconds - secondsPassed)) + "s\n\n"
                        "Messiness: " + Utils::stringify(messiness)+"\n";
    sf::Text textStats(str, font);
    textStats.setColor(sf::Color::Red);
    textStats.move(Settings::room*Settings::windowSize.x, 0);
    textStats.setCharacterSize(20);
    window.draw(textStats);
}

void Game::shotWater(){
    hasWaterGun=false;
    cat.getRekt();
}

void Game::createObjects(){
    assets.pot.loadFromFile("files/graphics/pot.png");
    assets.catIdle.loadFromFile("files/graphics/catIdle.png");
    assets.catMove.loadFromFile("files/graphics/catMove.png");
    assets.catHiss.loadFromFile("files/graphics/catHiss.png");
    assets.room1.loadFromFile("files/graphics/pokoj.png");
    assets.room2.loadFromFile("files/graphics/pokoj3.png");
    assets.doorRight.loadFromFile("files/graphics/drzwi_prawe.png");
    assets.clock.loadFromFile("files/graphics/clock.png");
    assets.clockHand.loadFromFile("files/graphics/clockhand.png");
    assets.sink.loadFromFile("files/graphics/sink.png");
    assets.pool.loadFromFile("files/graphics/pool0.png");
    assets.trash.loadFromFile("files/graphics/trash.png");
    assets.gamepad.loadFromFile("files/graphics/gamepad.png");
    assets.bed.loadFromFile("files/graphics/bed.png");
    assets.mom.loadFromFile("files/graphics/mom1.png");
    assets.cloud.loadFromFile("files/graphics/cloud.png");
    assets.radio.loadFromFile("files/graphics/radio.png");
    assets.onoff.loadFromFile("files/graphics/onoff.png");
    assets.table.loadFromFile("files/graphics/table.png");
    assets.glass.loadFromFile("files/graphics/glass.png");
    assets.cd1.loadFromFile("files/graphics/cd1.png");
    assets.cd2.loadFromFile("files/graphics/cd2.png");
    assets.tree.loadFromFile("files/graphics/tree.png");

    assets.catPrankBookThrow.loadFromFile("files/graphics/catPrankBookThrow.png");
    assets.catPrankBed.loadFromFile("files/graphics/catPrankBed.png");
    assets.catPrankGlass.loadFromFile("files/graphics/catPrankGlass.png");

    TextureContainer::spsSmoke.loadFromFile("files/graphics/spsSmoke.png");

    anims["catPrankBookThrow"] = new Anim(&assets.catPrankBookThrow);
    anims["catPrankBed"] = new Anim(&assets.catPrankBed);
    anims["catPrankGlass"] = new Anim(&assets.catPrankGlass);

    anims["pot"] = new Anim(&assets.pot, 58, sf::seconds(3600 * 24));
    anims["catIdle"] = new Anim(&assets.catIdle);
    anims["catMove"] = new Anim(&assets.catMove, 170, sf::milliseconds(300));
    anims["catHiss"] = new Anim(&assets.catHiss, 178, sf::milliseconds(100));
    anims["door"] = new Anim(&assets.doorRight);
    anims["clock"] = new Anim(&assets.clock);
    anims["clockHand"] = new Anim(&assets.clockHand);
    anims["sink"] = new Anim(&assets.sink);
    anims["pool"] = new Anim(&assets.pool);
    anims["trash"] = new Anim(&assets.trash);
    anims["gamepad"] = new Anim(&assets.gamepad);
    anims["radio"] = new Anim(&assets.radio);
    anims["onoff"] = new Anim(&assets.onoff);
    anims["bed"] = new Anim(&assets.bed, 254, sf::seconds(3600 * 24));
    anims["mom"] = new Anim(&assets.mom);
    anims["cloud"] = new Anim(&assets.cloud);
    anims["onoff_button"] = new Anim(&assets.onoff);
    anims["table"] = new Anim(&assets.table);
    anims["glass"] = new Anim(&assets.glass, 35, sf::seconds(3600 * 24));
    anims["cd1"] = new Anim(&assets.cd1);
    anims["cd2"] = new Anim(&assets.cd2);
    anims["tree"] = new Anim(&assets.tree);

    items["table"] = new ItemTable(anims["table"], 1.0f);
    items["table"]->setPosition(986, 478);
    items["glass"] = new ItemGlass(anims["glass"], 0.5f);
    items["glass"]->setPosition(893, 430);

    items["bed"] = new ItemBed(anims["bed"], 1.0f); // watch it!
    items["bed"]->setPosition(151, 583);
    items["pot"] = new ItemPot(anims["pot"], 1.0f);
    items["pot"]->move(600, 100);
    items["pot2"] = new ItemPot(anims["pot"], 1.0f);
    items["pot2"]->move(200, 400);
    items["pot3"] = new ItemPot(anims["pot"], 1.0f);
    items["pot3"]->move(400, 200);

    ItemClockHand* itemClockHand = new ItemClockHand(anims["clockHand"], 0.999999f);
    items["clockHand"] = itemClockHand;
    items["clock"] = new ItemClock(anims["clock"], itemClockHand, &secondsPassed, &totalTimeInSeconds, 1.0f);
    items["clock"]->setPosition(200, 100);
    items["clock"]->setScale(0.4, 0.4);

    ItemDoor* doorRightFirstRoom = new ItemDoor(anims["door"], false, 1.0f);
    doorRightFirstRoom->setGame(this);
    items["doorRightFirstRoom"] = doorRightFirstRoom;
    items["doorRightFirstRoom"]->move(1200, 400);

    ItemDoor *doorRightSecondRoom = new ItemDoor(anims["door"], false, 10.0f);
    doorRightSecondRoom->setGame(this);
    items["doorRightSecondRoom"] = doorRightSecondRoom;
    items["doorRightSecondRoom"]->move(1150 + 1280, 400);

    ItemDoor* doorLeftSecondRoom = new ItemDoor(anims["door"], true, 10.0f);
    doorLeftSecondRoom->setScale(-1, 1);
    doorLeftSecondRoom->setGame(this);
    items["doorLeftSecondRoom"] = doorLeftSecondRoom;
    items["doorLeftSecondRoom"]->move(130+1280, 400);

    ItemDoor *doorLeftThirdRoom = new ItemDoor(anims["door"], true, 10.0f);
    doorLeftThirdRoom->setScale(-1, 1);
    doorLeftThirdRoom->setGame(this);
    items["doorLeftThirdRoom"] = doorLeftThirdRoom;
    items["doorLeftThirdRoom"]->move(130 + 2560, 400);

    items["sink"] = new ItemSink(anims["sink"], this, 1.0f);
    items["sink"]->move(600+1280, Settings::floorLevel);

    items["trash1"] = new ItemTrash(anims["trash"], 5.f);
    items["trash1"]->move(300, 500);

    items["gamepad1"] = new ItemGamepad(anims["gamepad"], 1.0f);
    items["gamepad1"] -> move(350, 300);
    items["gamepad2"] = new ItemGamepad(anims["gamepad"], 1.0f);
    items["gamepad2"] -> move(420, 300);

    ItemOnOffButton* onOffButton = new ItemOnOffButton(anims["onoff_button"]);
    items["radioOnOff"] = onOffButton;
    ItemRadio* itemRadio = new ItemRadio(anims["radio"], onOffButton, this);
    items["radio"] = itemRadio;
    items["radio"]->move(800, 500);

    items["cd1"] = new ItemCD(anims["cd1"], true, itemRadio);
    items["cd1"]->setPosition(850, 620);
    items["cd2"] = new ItemCD(anims["cd2"], false, itemRadio);
    items["cd2"]->setPosition(800, 620);

    pranks.push_back(new PrankBookThrow(this));
    pranks.push_back(new PrankBed(this));
    pranks.push_back(new PrankGlass(this));
    pranks.push_back(new PrankThrowToTrash(this));

    roomSprite = sf::Sprite(assets.room2);
    roomSprite.setScale(window.getSize().x * 3.0f / roomSprite.getGlobalBounds().width,
                        window.getSize().y / roomSprite.getGlobalBounds().height);
    font.loadFromFile("files/fonts/Digital_7.ttf");

    ItemTree* iTree = new ItemTree(anims["tree"], 6.0f);
    items["tree"] = iTree;
    items["tree"]->setPosition(389, 358);

    Sounds::glass_crash_realistic.loadFromFile("files/tunes/glass_crash_realistic.ogg");
    Sounds::door_close.loadFromFile("files/tunes/door_close.ogg");
    Sounds::door_open.loadFromFile("files/tunes/door_open.ogg");
    Sounds::scratch_fast.loadFromFile("files/tunes/scratch_fast.ogg");
    Sounds::scratch_slow.loadFromFile("files/tunes/scratch_slow.ogg");
    Sounds::scratch_paw.loadFromFile("files/tunes/scratch_paw.ogg");
    Sounds::cat_meow1.loadFromFile("files/tunes/cat_meow1.ogg");
    Sounds::cat_meow2.loadFromFile("files/tunes/cat_meow2.ogg");
    Sounds::cat_meow3.loadFromFile("files/tunes/cat_meow3.ogg");
    Sounds::cat_meow4.loadFromFile("files/tunes/cat_meow4.ogg");
    Sounds::cat_purr1.loadFromFile("files/tunes/cat_purr1.ogg");
    Sounds::cat_purr2.loadFromFile("files/tunes/cat_purr2.ogg");
    Sounds::cat_screach1.loadFromFile("files/tunes/cat_screach1.ogg");
    //Sounds::disorganization.loadFromFile("files/tunes/disorganization.ogg");
    //Sounds::disorganization2.loadFromFile("files/tunes/disorganization2.ogg");
    Sounds::plum.loadFromFile("files/tunes/plum.ogg");
    Sounds::steppy.loadFromFile("files/tunes/steppy.ogg");
    Sounds::bec.loadFromFile("files/tunes/bec.ogg");
    Sounds::bupu_bupu.loadFromFile("files/tunes/bupu_bupu.ogg");
    Sounds::cat_screach1.loadFromFile("files/tunes/cat_screach1.ogg");
    Sounds::pef.loadFromFile("files/tunes/pef.ogg");
    Sounds::pif.loadFromFile("files/tunes/pif.ogg");
    Sounds::shash.loadFromFile("files/tunes/shash.ogg");
    Sounds::sink.loadFromFile("files/tunes/sink.ogg");
    Sounds::sss.loadFromFile("files/tunes/sss.ogg");
    Sounds::tik_tok.loadFromFile("files/tunes/tik_tok.ogg");
    Sounds::tsh.loadFromFile("files/tunes/tsh.ogg");
    Sounds::wosh.loadFromFile("files/tunes/wosh.ogg");

    std::vector<std::string> trashableItems = {
        "gamepad1", "gamepad2", "clock", "clockHand", "pot", "pot2", "pot3"
    };
    for(const auto& t: trashableItems)
        items[t]->isTrashable=true;


    cat.move(640, Settings::floorLevel);
    mom = AnimSprite(anims["mom"]);
    Utils::setOriginInCenter(mom);
    mom.setPosition(2*Settings::windowSize.x-700, Settings::floorLevel);
    mom.setScale(-1, 1);

    momCloud = AnimSprite(anims["cloud"]);
    Utils::setOriginInCenter(momCloud);

    momText = sf::Text("git good!\n", font);
    momText.setColor(sf::Color::Black);
    momText.setOrigin(momText.getGlobalBounds().width/2.0f, momText.getGlobalBounds().height/2.f+momText.getCharacterSize()/2.f);

    countText = sf::Text("", font);
    countText.setCharacterSize(50);
    countText.setColor(sf::Color::Red);

    momCloud.setPosition(mom.getPosition()+sf::Vector2f(175, -230));
    momText.setPosition(momCloud.getPosition());
}
