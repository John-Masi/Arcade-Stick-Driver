
extern "C" {
	#include "driver.h"
}


#include <iostream>


int main() {
	Button buttons[8] = {{false,304},{false,305},{false,306},{false,307},
						{false,308},{false,309},{false,310},{false,311},};
	run(buttons);
}