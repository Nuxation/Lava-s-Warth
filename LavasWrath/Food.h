#ifndef FOOD_H
#define FOOD_H

#include <Gamebuino-Meta.h>


class Food
{
	private:
	
		// X and Y in the titles value
		short xPos;
		short yPos;
				
		Image* currentImg;
	
	public:
		
		void SetPosition( short newX ,short newY );
		void SelectSkin();
		bool Safe( short dangerX , short dangerY );
		//Update sera utilisé pour les annimation de la nouriture
		void Update ();
		void Draw ();
		
		Food ();
		Food (short xStart, short Start);
		
};


#endif //FOOD_H
