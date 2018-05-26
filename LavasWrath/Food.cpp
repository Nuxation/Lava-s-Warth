#include "Food.h"

#include <Gamebuino-Meta.h>
#include "GlobaleData.h"

const uint16_t lavaGemsData[] = {16,16,1, 0, 0xF81F, 0, 0xF81F,0xF81F,0xbf90,0xbf90,0x8ea9,0x8ea9,0xF81F,0xF81F,0xF81F,0xF81F,0xa6bf,0xa6bf,0x7d9e,0x7d9e,0xF81F,0xF81F,0xF81F,0xbf90,0xbf90,0xbf90,0x8ea9,0x8ea9,0x8ea9,0xF81F,0xF81F,0xa6bf,0xa6bf,0xa6bf,0x7d9e,0x7d9e,0x7d9e,0xF81F,0xbf90,0xbf90,0xbf90,0xbf90,0x8ea9,0x8ea9,0x8ea9,0x8ea9,0xa6bf,0xa6bf,0xa6bf,0x1295,0x1295,0x7d9e,0x7d9e,0x7d9e,0x8ea9,0x8ea9,0x8ea9,0x8ea9,0x5da3,0x5da3,0x5da3,0x5da3,0xa6bf,0xa6bf,0x1295,0x1295,0x1295,0x1295,0x7d9e,0x7d9e,0xF81F,0x8ea9,0x8ea9,0x8ea9,0x5da3,0x5da3,0x5da3,0xF81F,0x7d9e,0x7d9e,0x1295,0x1295,0x1295,0x1295,0x549c,0x549c,0xF81F,0xF81F,0x8ea9,0x8ea9,0x5da3,0x5da3,0xF81F,0xF81F,0x7d9e,0x7d9e,0x7d9e,0x1295,0x1295,0x549c,0x549c,0x549c,0xF81F,0xF81F,0x8ea9,0x8ea9,0x5da3,0x5da3,0xF81F,0xF81F,0xF81F,0x7d9e,0x7d9e,0x7d9e,0x549c,0x549c,0x549c,0xF81F,0xF81F,0xF81F,0xF81F,0x8ea9,0x5da3,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0x7d9e,0x7d9e,0x549c,0x549c,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xfff5,0xffcb,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xfbcf,0xe208,0xe208,0xfbcf,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xfff5,0xffcb,0xF81F,0xF81F,0xF81F,0xF81F,0xfbcf,0xfbcf,0xfbcf,0xfbcf,0xfbcf,0xfbcf,0xF81F,0xF81F,0xF81F,0xF81F,0xfff5,0xffcb,0xF81F,0xF81F,0xF81F,0xF81F,0xe208,0xfbcf,0xc061,0xc061,0xfbcf,0xe208,0xF81F,0xF81F,0xffcb,0xF81F,0xfff5,0xffcb,0xF81F,0xf720,0xF81F,0xF81F,0xe208,0xfbcf,0xc061,0xc061,0xfbcf,0xe208,0xF81F,0xffcb,0xffcb,0xffcb,0xffcb,0xf720,0xf720,0xf720,0xf720,0xF81F,0xfbcf,0xfbcf,0xfbcf,0xfbcf,0xfbcf,0xfbcf,0xF81F,0xF81F,0xF81F,0xffcb,0xffcb,0xf720,0xf720,0xF81F,0xF81F,0xF81F,0xF81F,0xfbcf,0xe208,0xe208,0xfbcf,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xffcb,0xf720,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F,0xF81F};

Image lavaGems = Image(lavaGemsData);

void Food::SetPosition(short newX, short newY)
{
	this-> xPos = newX * tile;
	this-> yPos = newY * tile;
}

void Food::SelectSkin()
{
	this->currentImg = &lavaGems;
}

bool Food::Safe( short dangerX , short dangerY )
{
	if ( (this->xPos == dangerX * tile) && (this->yPos == dangerY * tile))
		return false;
	else	
		return true;
}

void Food::Update ()
{
	
}

void Food::Draw ()
{
    const int XDrawFood = 1 * tile;
    const int YDrawFood = 0 * tile; 
	gb.display.drawImage(xPos, yPos, *this->currentImg, XDrawFood, YDrawFood, tile, tile);
}

Food::Food () : currentImg(0), xPos(0), yPos (0)
{
	SelectSkin();
}

Food::Food (short xStart, short yStart) :  xPos(xStart), yPos (yStart),currentImg(0)
{
	SelectSkin();
}