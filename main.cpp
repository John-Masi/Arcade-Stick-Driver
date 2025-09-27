#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <optional>
#include <thread>

extern "C" {
	#include "driver.h"
}


int main() {

	Button buttons[8] = {{false,304},{false,307},{false,309},{false,308},
						{false,305},{false,306},{false,311},{false,310},};

	std::thread t(run,buttons);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

	sf::Texture texture;
	//texture.loadFromFile("1.png");
	if(!texture.loadFromFile("button.png")){
		std::cerr << "Failed to load" << '\n';
		return -1;
	}


	sf::Sprite sfArray[8] = {sf::Sprite(texture),sf::Sprite(texture),sf::Sprite(texture),sf::Sprite(texture),
								sf::Sprite(texture),sf::Sprite(texture),sf::Sprite(texture),sf::Sprite(texture)};
	
	for(int i = 0; i < 8; i++){
		if(i >= 4) {
			sfArray[i].setPosition(i*100,100);
		}
		else {
			sfArray[i].setPosition(i*100,0);
		}

		sfArray[i].setScale(0.5f,0.5f);
	}

    sf::Event event;
    while (window.isOpen()) {

    	for(int i = 0; i < 8; i++) {
    		if(buttons[i].is_pressed) {
    			sfArray[i].setColor(sf::Color(255,255,255,128));
    		}
    		else {
    			sfArray[i].setColor(sf::Color(255,255,255,255));
    		}
    	}
    
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        for(int i = 0; i < 8; i++) {
        	window.draw(sfArray[i]);
        }
        window.display();
    }

    t.join();

}