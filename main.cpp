#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include <string>
#include <unordered_map>

// Compile command 
// g++ main.cpp -o app -lsfml-graphics -lsfml-window -lsfml-system


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

	JoyStick x_sticks[2] = {{16,0},{17,0}};
	JoyStick y_sticks[2] = {{16,0},{17,0}};

	std::thread t(run,buttons,x_sticks,y_sticks);

	sf::RenderWindow window(sf::VideoMode(800, 600), "Window");

	// Button texture
	sf::Texture texture;

	// Joystick textures
	sf::Texture up_t;
	sf::Texture down_t;
	sf::Texture left_t;
	sf::Texture right_t;

	up_t.loadFromFile("up.png");
	down_t.loadFromFile("down.png");
	left_t.loadFromFile("left.png");
	right_t.loadFromFile("right.png");

	if(!texture.loadFromFile("button.png")){
		std::cerr << "Failed to load" << '\n';
		return -1;
	}



	std::unordered_map<int, sf::Sprite> js_sprites = {
		{16,sf::Sprite(left_t)},
		{17,sf::Sprite(right_t)},
		{18,sf::Sprite(up_t)},
		{19,sf::Sprite(down_t)},
	};

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

	for(auto& [key, sprite]: js_sprites){
		sprite.setPosition(100,0);
		sprite.setScale(1.0f,1.0f);
	}

	js_sprites[17].move(20,300);
	js_sprites[18].move(20,100);
	js_sprites[16].move(20,200);
	js_sprites[19].move(20,400);

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

    	
    		if(x_sticks[0].is_pushed == 1 ){
    				js_sprites[17].setColor(sf::Color(55,155,155));
    		}
    		else if(x_sticks[1].is_pushed == -1) {
    				js_sprites[16].setColor(sf::Color(55,155,155));
    		}
    		else{
    			js_sprites[16].setColor(sf::Color(255,255,255));
    			js_sprites[17].setColor(sf::Color(255,255,255));
    		}

    	

    
    		if(y_sticks[0].is_pushed == 1){
    				js_sprites[19].setColor(sf::Color(55,155,155));
    		}
    		else if(y_sticks[1].is_pushed == -1) {
    				js_sprites[18].setColor(sf::Color(55,155,155));
    		}
    		else{
    			js_sprites[18].setColor(sf::Color(255,255,255));
    			js_sprites[19].setColor(sf::Color(255,255,255));
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
        for(auto& [key,sprite]: js_sprites) {
        	window.draw(sprite);
        }
        window.display();
    } 

    t.join();

} 