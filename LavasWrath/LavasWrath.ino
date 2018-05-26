//#include <Gamebuino-Meta.h>
#include "GameScreen.h"


void setup() {
    gb.begin();
  
}

void loop() { 
    while(!gb.update());
    gb.display.clear();
    
    MainScreenSelector(1);
}
