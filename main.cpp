#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <thread>

extern "C" {
	#include "driver.h"
}


int main() {

	Button buttons[8] = {{false,304},{false,305},{false,306},{false,307},
						{false,308},{false,309},{false,310},{false,311},};

	std::thread t(run,buttons);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

	sf::Texture texture;
	//texture.loadFromFile("1.png");
	if(!texture.loadFromFile("one.png")){
		std::cerr << "Failed to load" << '\n';
		return -1;
	}

	sf::Sprite sprite(texture);
	sprite.setPosition(0, 0); 
	sprite.setScale(0.5f,0.5f);

    sf::Event event;
    while (window.isOpen()) {

    	if(buttons[0].is_pressed) {
    		sprite.setColor(sf::Color(255,255,255,128));
    	}
    	else {
    		sprite.setColor(sf::Color(255,255,255,255));
    	}
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    t.join();

}