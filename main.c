#include <stdbool.h>    
#include <stdio.h>      
#include <stdlib.h>     
#include <fcntl.h>     
#include <unistd.h>     
#include <linux/input.h> 
#include <string.h>
#include <errno.h> 

// Bus 001 Device 004: ID 0f30:3018 Jess Technology Co., Ltd Qanba Arcade Joystick 3018

// js0: joystick api (buttons and axes/timestamps)

// /dev/input/event12&13 (interfaces for the stick)


// Dectect for stick after implementation

struct Button{
	bool is_pressed; 
	int code; 
};

struct JoyStick {
	int code; 
	int is_pushed; 
};

int FindDevice() {

	char path[32];

	for(int i = 0; i < 20; i++) {
		sprintf(path,"/dev/input/event%d",i);
		int fd = open(path,O_RDONLY | O_NONBLOCK);
		if(fd >= 0){
			char buffer[256];

			size_t len = sizeof(buffer); 

			ioctl(fd,EVIOCGNAME(len),buffer);


			if(strcmp(buffer,"Shenzhen Qanba Technology Development Co.,Ltd Qanba Arcade Joystick 3018") == 0) {
				close(fd);
				printf("Name: %s\n",buffer);
				return i;

			}

		}
		
	}

	return -1;

}

void run() {

}

int main(void) {

	int num = FindDevice();


	struct Button buttons[8] = {{false,304},{false,305},{false,306},{false,307},
						{false,308},{false,309},{false,310},{false,311},};

	struct input_event event; 
	char path[32];

	sprintf(path,"/dev/input/event%d",num);
	int fd = open(path,O_RDONLY | O_NONBLOCK);

	if(fd < 0) {
		exit(0);
	}

	while(true){
		int n = read(fd, &event, sizeof(event));

		if(n == sizeof(event)) {
		
			if(event.type == EV_KEY){
				for(int i = 0; i < 8; i++){
					if(event.code == buttons[i].code){
						buttons[i].is_pressed = (event.value == 1);
						printf("Button %u is: %d\n",buttons[i].code,buttons[i].is_pressed);
					}
				}
			
			}
			else if(event.type == EV_ABS){
				printf("%d %u\n",event.value,event.code);
			}

		}
	}

	close(fd);
}