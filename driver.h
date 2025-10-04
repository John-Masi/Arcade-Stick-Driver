#include <stdbool.h>    
#include <stdio.h>      
#include <stdlib.h>     
#include <fcntl.h>     
#include <unistd.h>     
#include <linux/input.h> 
#include <string.h>
#include <errno.h> 

#ifndef DRIVER_H	
#define DRIVER_H

// Bus 001 Device 004: ID 0f30:3018 Jess Technology Co., Ltd Qanba Arcade Joystick 3018

// js0: joystick api (buttons and axes/timestamps)

// /dev/input/event12&13 (interfaces for the stick)

// Dectect for stick after implementation

typedef struct {
	bool is_pressed; 
	int code; 
} Button;

typedef struct {
	int code; 
	int is_pushed; 
} JoyStick;

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
				//printf("Name: %s\n",buffer);
				return i;

			}

		}
		
	}

	return -1;

}

void run(Button* buttons,JoyStick* joystick,JoyStick* joystick_2) {
	int num = FindDevice();

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
					}
				}
			
			}
			else if(event.type == EV_ABS){
					printf("%d\n",event.code);

					if(event.code == 16 && event.value == 1) {
						joystick[0].is_pushed = event.value;
					}
					else if(event.code == 16 && event.value == -1){
						joystick[1].is_pushed = event.value;
					}
					else{
						joystick[0].is_pushed = 0;
						joystick[1].is_pushed = 0;
					}

					if(event.code == 17 && event.value == 1) {
						joystick_2[0].is_pushed = event.value;
					}
					else if(event.code == 17 && event.value == -1) {
						joystick_2[1].is_pushed = event.value;
					}
					else{
						joystick_2[0].is_pushed = 0;
						joystick_2[1].is_pushed = 0;
					}

				}
			}

		}
		close(fd);
	}

#endif