#ifndef SCOREMODE_H
#define SCOREMODE_H


#include "LavaRiver.h"
#include "Food.h"

class ScoreMode
{

	private:
		//Methode
		
		/* Every GameOver condition for this gamemode
		 * 1/ The head go out of the screen
		 * 2/ The river head touch the body or tail
		 */
        bool GameOverLose ();
        bool GameOverWin (); 
		
		//0 = win / 1 = lose.
		void GameOverScreen (short endType);
		void PrintScore (int xCur, int yCur);
		bool HeadInBody();
		
		//Propriety
		const short mapXMin;
		const short mapXMax;
		const short mapYMin;
		const short mapYMax;
		
		Food gem;
		
		// count gem eat during the party
        int score;
		// Time per tick
		const int timePT;
		
		//the element 0 is the current size of the river. 1 is the head.
		short riverPositionX[81];
		short riverPositionY[81];
		//The name of the lava river choose by my mom, thanks to keep it.
		LavaRiver serpentissimo;
		
		void MoveFood (Food &food);
		bool EatGem();
		
	public: 
		
		//Take care to init and to the flow of the game
		void Play();
		void Restart();
		
		//The bool return true if the game is over
		bool Update(const short &time, byte &mvtWanted);
		void Draw();
		
		//Construc and destruct
		//default
		ScoreMode(); 

		//default destructor
		~ScoreMode();

};


#endif //SCOREMODE_H
