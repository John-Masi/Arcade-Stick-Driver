#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <unordered_map>

extern "C" {
	#include "driver.h"
}

struct Sprite {
	Button button;
	sf::Sprite sprite;
};

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

	std::unordered_map<int , sf::Sprite> sprites = {
		{304,sf::Sprite(texture)},
		{307,sf::Sprite(texture)},
		{309,sf::Sprite(texture)},
		{308,sf::Sprite(texture)},
		{305,sf::Sprite(texture)},
		{306,sf::Sprite(texture)},
		{311,sf::Sprite(texture)},
		{310,sf::Sprite(texture)}

	};
	
	for(auto& [key, sprite]: sprites){
		sprite.setPosition(100,0);
		sprite.setScale(0.5f,0.5f);
	}

	sprites[304].move(200,200);
	sprites[307].move(300,200);
	sprites[309].move(400,200);
	sprites[308].move(500,200);
	sprites[305].move(200,300);
	sprites[306].move(300,300);
	sprites[311].move(400,300);
	sprites[310].move(500,300);

    sf::Event event;
    while (window.isOpen()) {

    	for(int i = 0; i < 8; i++) {
  
    			if(buttons[i].is_pressed){
    			sprites[buttons[i].code].setColor(sf::Color(55,155,155));
    			}
   
    			else{
    				sprites[buttons[i].code].setColor(sf::Color(255,255,255));
    			}
    		}
    		
    
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::Black);
        for(auto& [key,sprite]: sprites) {
        	window.draw(sprite);
        }
        window.display();
    } 

    t.join();

} 