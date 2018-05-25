#ifndef LAVARIVER_H
#define LAVARIVER_H

#include <Gamebuino-Meta.h>
#include "LavasBound.h"



class LavaRiver
{
	private:
	
		//Take care to link/unlink 2 LavasBound
		void Linker (LavasBound &proximalLB ,LavasBound &distalLB);
		void UnLinker (LavasBound &proximalLB ,LavasBound &distalLB);
        
		//The size of the rivers need in the array
		short riverSize;
		//80 is the amounth of tile need to fill the 80x64 screen with 8x8 tiles
        LavasBound river[80];
		
		
		
	public: 

        //methode
        void Update(byte mvtWanted);
        void Draw();
        void SetPos(short xP, short yP);
		void Restart();
		
		void Grow();
		void Diminish();
		
		//used for colision calculation. the array parrametre have to be riverSize size + 1 because the first slot is use to store the array current size.
		void GetRiverPosition(short arrayX[81],short arrayY[81]);

		
		//constructor & destructor & copie
        LavaRiver();
        LavaRiver(short xStart, short yStart, short riverSizeStart);
		~LavaRiver();

};

#endif //LAVARIVER_H
