#include "LavasBound.h"


#include <Gamebuino-Meta.h>
#include "GlobaleData.h"
#include "LavasBoundData.h"



// Methode of LavasBound

// This methode is made to initiate the river can be increase to telporte the river later if need
void LavasBound::SetPosition (short xP, short yP)
{
    this->xPos = xP * tile;
    this->yPos = yP * tile;
}

short LavasBound::GetPositionX()
{
	return this->xPos / tile;
}

short LavasBound::GetPositionY()
{
	return this->yPos / tile;
}

byte LavasBound::GetProximalPos()
{
	return proximalPos;
}

byte LavasBound::GetDistalPos()
{
	if (state ==0 && this->distal == 0)
		//A random value to allow the head to move freely at start if no tail
		return 10;
	else 
		return distalPos;

}

void LavasBound::Move (byte mvt)
{

	byte oldProximal = proximalPos;
	byte oldDistal = distalPos;
	
	if (mvt != 5 && distal != 0 )
		this->distal->Follow();

    switch (mvt)
    {
        case 6:
        {
            this->xPos += tile;
            break;
        }
        case 4:
        {
            this->xPos -= tile;
            break;
        }
        case 2:
        {
            this->yPos += tile;
            break;
        }
        case 8:
        {
            this->yPos -= tile;
            break;
        }
		case 5:
        {
            break;
        }
        default:
        {
            gb.display.print("This dev sucks! Value: ");
			gb.display.println(mvt);
        }
    }    
	
	//alow the head to remember his last move
	if (proximal == 0)
	{
		proximalPos = mvt;
	}
	else 
	{
		CalcProximalPos();
	}
	//allow the part to remember its relative last position.
	distalPos = ReverseMove(mvt);
	
	if ((oldProximal != proximalPos) ||(oldDistal != distalPos))
		imgState = false;
	
}

void LavasBound::Follow()
{
	CalcProximalPos();
  if (proximalPos != 5 || proximalPos != 7 || proximalPos != 9 || proximalPos != 1 || proximalPos != 3 )
	Move(proximalPos);

	
}

byte LavasBound::ReverseMove(const byte &move)
{
	
	// I am absolutly aware than those break are useless
	switch (move)
    {
        case 6:
        {
            return 4;
            break;
        }
        case 4:
        {
            return 6;
            break;
        }
        case 2:
        {
            return 8;
            break;
        }
        case 8:
        {
            return 2;
            break;
        }
		case 5:
        {
			return 5;
            break;
        }
        default:
        {
			
            gb.display.print("Oh! not that dev again >.> Value: ");
			gb.display.println(move);
			return move;
        }
    }
}

void LavasBound::CalcProximalPos()
{
	if(proximal != 0)
	{
		short difX(1+((proximal->xPos)-(this->xPos))/tile);
		short difY(1+((proximal->yPos)-(this->yPos))/tile);

		byte pavNum[3][3] = 
		{ 
			{7, 8, 9}, 
			{4, 5, 6},
			{1, 2, 3}
		};
		
		if (difX > -1 && difX < 3 && difY > -1 && difY < 3)
		proximalPos = pavNum[difY][difX];
	}
}

void LavasBound::CalcDistalPos()
{
	if(distal != 0)
	{
		short difX(1+((distal->xPos)-(this->xPos))/tile);
		short difY(1+((distal->yPos)-(this->yPos))/tile);

		byte pavNum[3][3] = 
		{ 
			{7, 8, 9}, 
			{4, 5, 6},
			{1, 2, 3}
		};
		
		if (difX > -1 && difX < 3 && difY > -1 && difY <3)
		distalPos = pavNum [difY][difX];
	}
}

void LavasBound::GivePositionNewLB(LavasBound &newFriend)
{
	
	switch (this->distalPos)
	{
		case 6:
		{
			newFriend.SetPosition(this->xPos/tile + 1,this->yPos/tile);
			break;
		}
		case 4:
		{
			newFriend.SetPosition(this->xPos/tile - 1,this->yPos/tile);
			break;
		}
		case 2:
		{
			newFriend.SetPosition(this->xPos/tile , this->yPos/tile + 1);
			break;
		}
		case 8:
		{
			newFriend.SetPosition(this->xPos/tile,this->yPos/tile - 1);
			break;
		}
		default:
		{
			newFriend.SetPosition(this->xPos/tile,this->yPos/tile);
			gb.display.print("Error: This dev is a Noob!");
			gb.display.println(this->distalPos);

		}
	}
	newFriend.proximalPos = this->distalPos;
	newFriend.distalPos = this->distalPos;
	
	//Synchronisation of animations + Remove residual value
	newFriend.imgPhase = this->imgPhase;
	newFriend.animationState = this->animationState;
	newFriend.animationTimeur = this->animationTimeur;
	
}


void LavasBound::CheckState ()
{
	//if first state head
	if (this->proximal == 0)
		state = 0;
	// else if last state is tail
	else if (this->distal == 0)
		state = 2;
	//then if nor head and nor tail the state is body
	else 
		state = 1; 
	
	//
	imgState = false;
	
}
void LavasBound::AddBoundP (LavasBound &proximalLB)
{
	this->proximal = &proximalLB;	
}

void LavasBound::AddBoundD (LavasBound &distalLB)
{
	this->distal = &distalLB;
}

void LavasBound::RemoveBoundP()
{
	this->proximal = 0;
}

void LavasBound::RemoveBoundD()
{
	this->distal = 0;
}


void LavasBound::Draw ()
{
    if (!imgState)
        ImageSelect();

	
	if (animationState != 0)
	{
		ImageAnimationWave();
	}
	
	//Body tileset is 2 tile high over tileset are 1 tile high
	if( state == 1 )
		gb.display.drawImage(xPos, yPos, *this->currentImg, imageX, (imageY + (imgPhase * tile * 2)) , tile, tile);
	else
		gb.display.drawImage(xPos, yPos, *this->currentImg, imageX, (imageY + (imgPhase * tile)) , tile, tile);
	
}
void LavasBound::ImageSelect()
{
    CalcProximalPos();
	imageX = 0 ;
    switch (state)
    {
		
        case 0:
        {
            this->currentImg = &lavaHead;
			
			imageX = tileSetconversion(this->proximalPos);
			imageY = 0;
			
            this->imgState=true;
            break;
        }
        
        case 1:
        {
            this->currentImg = &lavaBody; 
			switch (this->proximalPos + this->distalPos)
			{
				case 6:
				{
					imageX = tile * 2 ;
					imageY = tile * 0 ;
					break;
				}
				case 8:
				{
					imageX = tile * 1 ;
					imageY = tile * 0 ;
					break;
				}
				case 12:
				{
					imageX = tile * 2 ;
					imageY = tile * 1 ;
					break;
				}
				case 14:
				{
					imageX = tile * 1 ;
					imageY = tile * 1 ;
					break;
				}
				
				case 10:
				{
					if (this->proximalPos == 4 || this->proximalPos == 6 )
					{
						imageX = tile * 0 ;
						imageY = tile * 0 ;
					}
					else if (this->proximalPos == 2 || this->proximalPos == 8 )
					{
						imageX = tile * 0 ;
						imageY = tile * 1 ;
					}
					else
					{
						gb.lights.fill(RED);
					}
					break;
				}
				default:
				{
					gb.lights.fill(RED);
				}
				
			}
            this->imgState=true;
            break;
        }  
        
        case 2:
        {
            this->currentImg = &lavaTail;
			
			imageX = tileSetconversion(this->proximalPos);
			imageY = 0 ;
			
            this->imgState=true;
            break;
        }       
        default:
        {
            this->currentImg = &buggy; 
            this->imgState=true;
        }
    }
}

void LavasBound::ImageAnimationWave()
{
	const int framesPerTransition = 2;
	const int nbrOfTransitionFrame = 4;
	

	switch (animationState)
	{
		case 0 :
		{
			break;
		}
		
		case 1 :
		{

			// i want the next bound to start at 1/3 of the first animation
			if (animationTimeur == (framesPerTransition * nbrOfTransitionFrame)/3)
			{
				if(this->distal != 0)
				{
					this->distal->animationState = 1;
				}
			}
			if (animationTimeur < (framesPerTransition * nbrOfTransitionFrame))
			{

				if (((animationTimeur % framesPerTransition) == 0) && (imgPhase < 4))
				{
					++imgPhase;
				}
				++animationTimeur;
			}
			if (imgPhase >= 4 )
			{
				animationState = 2;
				animationTimeur = 0;
			}
			break;
		}
		
		case 2 :
		{	
			// This phase of the animation is 10 time longer than a transition
			if (animationTimeur < framesPerTransition * 10)
			{
				++animationTimeur;
			}
			else
			{
				animationState = 3;
				animationTimeur = 0;
			}

			break;
		}
		
		case 3 :
		{
			if (animationTimeur < framesPerTransition * nbrOfTransitionFrame)
			{
				if ( animationTimeur % framesPerTransition == 0 && imgPhase > 0)
				{
					--imgPhase;
				}
				++animationTimeur;
			}
			else if (imgPhase <= 0)
			{
				animationState = 0;
				animationTimeur = 0;
			}

			break;
		}
		
		default:
		{
			break;
		}
	}
}
bool LavasBound::askWave()
{

	
	if(!(animationState == 0))
	{
		return false;
	}
	else
	{
		animationState = 1 ;
	}
}
short LavasBound::tileSetconversion(byte relativePosition)
{
	switch (relativePosition)
	{
		case 2:
		{
			return 0;
			break;
		}
		case 4:
		{
			return 1*tile;
			break;
		}
		case 6:
		{
			return 2*tile;
			break;
		}
		case 8:
		{
			return 3*tile;
			break;
		}
	}
	return 0;
}

        
//Construc and destruct for LavasBound
//default avoide to use it
LavasBound::LavasBound() : proximal(0), distal(0), xPos(0), yPos(0), state(0), imgState(false), currentImg(0),proximalPos(5), distalPos(5), imageX(0), imageY(0), imgPhase(0), animationState (0), animationTimeur (0)
{	 
	
}

//How the snake should be init
LavasBound::LavasBound(short Xask ,short Yask ) : proximal(0), distal(0), xPos(Xask), yPos(Yask), state(0), imgState(false), currentImg(0),proximalPos(5), distalPos(5), imageX(0), imageY(0), imgPhase(0), animationState (0), animationTimeur (0)
{

}
LavasBound::~LavasBound()
{

}


