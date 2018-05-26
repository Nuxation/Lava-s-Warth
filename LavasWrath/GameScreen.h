#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <Gamebuino-Meta.h>

// This file take care of the title screen, the tile menu, option.


	
	/* Take care to Load the right mode dependign of the selector value
	 * 0 = leave MainScreenSelector
	 * 1 = Title Scren
	 * 2 = Menu
	 * 3 = Option
	 * 4 = Classic
	 */
	void MainScreenSelector(short selector);
	//Show the tile screen and switch to tile menu once A is press
	short Title ();
	short Menu ();
	short Classic ();
	
#endif //GameSCREEN_H


		//Score mode and difficulty
		//Story Mode
		//Option
		// if stuff to unlock encyclopedie