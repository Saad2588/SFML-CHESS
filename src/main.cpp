#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;

float const tilesize = 96.f;
float const startingtilePos = 299.f;


int main() {

    //Get fullscreen size and render accordingly
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML Chess", sf::Style::Fullscreen);

    //Setting view to match board
    sf::View view(sf::FloatRect(0.f, 0.f, desktop.width, desktop.height));
    window.setView(view);


    sf::RectangleShape tile(sf::Vector2f(100.f,100.f));
    


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();


           

        window.clear(sf::Color(65,65,65));
        
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8 ; j++){

                if( (i+j) % 2 == 0)
                tile.setFillColor(sf::Color::White);
                else
                tile.setFillColor(sf::Color::Black);

                tile.setPosition(sf::Vector2(tilesize * i + startingtilePos, tilesize * j));

                window.draw(tile);
                
            }
        }
        window.display();
    }




    }

    
    return 0;
}