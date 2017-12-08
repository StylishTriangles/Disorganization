#include <SFML/Graphics.hpp>
#include <cmath>

int main(){
    sf::RenderWindow app(sf::VideoMode(320, 240), "Example");
    sf::Clock stoper;
    while(app.isOpen()){
        sf::Event event;
        while(app.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                 app.close();
        }
        app.clear();

        sf::CircleShape shape(std::sin( stoper.getElapsedTime().asSeconds()) * app.getSize().y / 8 + app.getSize().y / 4);
        shape.setOrigin(sf::Vector2f( shape.getRadius(), shape.getRadius()));
        shape.setPosition(app.getSize().x / 2.0f, app.getSize().y / 2.0f);
        shape.setFillColor(sf::Color::Yellow);
        app.draw(shape);

        app.display();
    }
    return 0;
}
