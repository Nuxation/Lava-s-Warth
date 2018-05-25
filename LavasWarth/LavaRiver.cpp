#include "LavaRiver.h"

#include <Gamebuino-Meta.h>
#include "GlobaleData.h"
#include "LavasBound.h"



// Private methode
void LavaRiver::Linker (LavasBound &proximalLB ,LavasBound &distalLB)
{
	proximalLB.AddBoundD(distalLB);
	distalLB.AddBoundP(proximalLB);
	proximalLB.CheckState ();
	distalLB.CheckState ();
}

void LavaRiver::UnLinker (LavasBound &proximalLB ,LavasBound &distalLB)
{
	proximalLB.RemoveBoundD();
	distalLB.RemoveBoundP();
	proximalLB.CheckState ();
	distalLB.CheckState ();
}


//Public methode
void LavaRiver::Update(byte mvtWanted)
{   
	river[0].CalcDistalPos();
	
	if (mvtWanted != river[0].GetDistalPos())
		river[0].Move(mvtWanted);
	else
		river[0].Move(river[0].GetProximalPos());
	
}

void LavaRiver::Draw()
{
	for (int i = 0 ; i < (riverSize); i++)
	{
		this->river[i].Draw();
	}
}

void LavaRiver::SetPos(short xP, short yP)
{
    this->river[0].SetPosition(xP ,yP);

}

void LavaRiver::Restart()
{
	for ( int i = riverSize-1 ; i > -1 ; i --)
	{
		UnLinker(river[i-1],river[i]);
	}		
	riverSize = 1;
}

void LavaRiver::Grow()
{
	if (riverSize < (sizeof(river)/sizeof(river[0])))
	{
        Linker(river[(riverSize-1)],river[riverSize]);    
        river[riverSize - 1].GivePositionNewLB(river[riverSize]);
        ++ riverSize;
		
		river[0].askWave();
	}
	else
	{
		gb.display.println("the river is already at max size");
	}
}

void LavaRiver::Diminish()
{
	if (riverSize > 1)
	{
		UnLinker (river[riverSize - 2],river[riverSize-1]);
		-- riverSize;
	}
	else
	{
		gb.display.println("the river is already at min size");
	}
}

void LavaRiver::GetRiverPosition(short arrayX[81],short arrayY[81])
{
	arrayX[0] = riverSize;
	arrayY[0] = riverSize;
	
	for (int i = 0 ; i < riverSize ; i++ )	
	{
		arrayX[i + 1] = river[i].GetPositionX();
		arrayY[i + 1] = river[i].GetPositionY();
	}
}

//Construc and destruct for LavaRiver
LavaRiver::LavaRiver() : riverSize(1)
{
	
}

LavaRiver::LavaRiver(short xStart, short yStart , short riverSizeStart = 1) : riverSize(riverSizeStart)
{

	river[0].SetPosition(xStart,yStart);
	for ( short i(1); i < riverSizeStart ; i++)
	{
		Linker(river[i-1], river[i]);
		xStart += tile;
		river[i].SetPosition(xStart,yStart);
	}


}
LavaRiver::~LavaRiver()
{
	
}
