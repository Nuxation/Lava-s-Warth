#ifndef LAVASBOUND_H
#define LAVASBOUND_H

#include <Gamebuino-Meta.h>


//Should be internal to LavaRiver (but i am not sure about know how to do yet)
class LavasBound
{
    private:
			
		LavasBound *proximal;
		LavasBound *distal;

		// X and Y in the titles value
		short xPos;
		short yPos;

		// Relative position or proximal and distal number are use like a num pad.
		// proximalPos is use by the head to remember last move than replay it. 
		// using it this away also allow to set the tail well when the river size is 1.
		byte proximalPos;
		byte distalPos;

		//0 = Head / 1 = Body / 2 = Tail / 255 = no states yet
		byte state;
		
		//Those propriety are value use to draw the LavasBound image
		// if the current image is good one
		bool imgState;
		//Represent the image's phase within the 5 image animation  (from 0 to 4)
		int imgPhase;
		// 0 == Low Glow && base state , 1 == forward , 2 == High glow, 3 == backward
		byte animationState;
		int animationTimeur;
		
		// current image;
		Image* currentImg;
		short imageX;
		short imageY;

    public:
    
		// Methode

		void SetPosition (short xP, short yP);
		
		// give position in the tiles map
		short GetPositionX();
		short GetPositionY();
		byte GetProximalPos();
		byte GetDistalPos();
		
		// to move the river (number are use like on a num pad)
		//and if state is not tail ask to distal to follow 
		void Move (byte mvt);
		//is call by the proxial part when it is moving
		//send the relative move instruction
		void Follow();
		//Give the opposite movement of the given move
		byte ReverseMove(const byte &move);
		//Take care to calculate the relative position of proximal and distal LavasBound
		void CalcProximalPos();
		void CalcDistalPos();
		
		//tell where a newly linked LavasBound should set him
		void GivePositionNewLB(LavasBound &newFriend);

		//Ask to this LavasBound to check which part of the river he is and to update him
		void CheckState ();

		// 4 methode who take care to set proximal and distal pointer
		void AddBoundP (LavasBound &proximalLB);
		void AddBoundD (LavasBound &distalLB);
		void RemoveBoundP();
		void RemoveBoundD();

		//Methode which take care to the river display
		void Draw();
		void ImageSelect();
		void ImageAnimationWave();
		bool askWave();
		short tileSetconversion (byte relativePosition);



		//Construc and destruct
		//default
		LavasBound(); 

		//How the snake should be init
		LavasBound(short Xask, short Yask);

		//default destructor
		~LavasBound();
};

#endif //LAVASBOUND_H
