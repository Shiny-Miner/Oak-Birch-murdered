#include <string.h>
#include "gba.h"
#include "ball.h"
#include "grass.h"
#include "bag.h"
#include "pointer.h"
#include "circle.h"

#define BG2Buffer     ((u16*)0x6003800)
#define BG3Buffer	((u16*)0x6003000)
#define Tiles     ((u16*)0x6000000)
#define Music     ((u16*)0x3003114)

int jump(u32);
void CopyOAM();
void InitializeSprites();
void GetInput();
void UpdateBallsandPointer();


int pFunc = 0x08069F9F; // 0x08youroffset

OAMEntry sprites[128];
int activeBall = 1;
int timer = 0;
int lastKeyPress = 0;
int pointertimer = 0;
int pointerIsUp = 0;
int pointerY = 0;
int circleinfront = 1;
int pokemonChosen = 0;

int notMain()
{
	//asm("push {r0-r7}");
	u16 x;
	SetMode(MODE_0 | BG2_ENABLE | BG3_ENABLE | BG0_ENABLE | OBJ_ENABLE | OBJ_MAP_1D);
	BG2CNT=0x0703;
	BG3CNT=0x0601;
	BG2HOFF=0x0000;
	BG2VOFF=0x0000;
	BG3HOFF=0x0000;
	BG3VOFF=0x0000;


	InitializeSprites();	
	
	//Copy Palettes...
	memcpy(&OBJ_PaletteMem[0],ballpal,sizeof(ballpal));
	memcpy(&BG_PaletteMem[0],grasspal,sizeof(grasspal));
	memcpy(&BG_PaletteMem[16],bagpal,sizeof(bagpal));

	memcpy(&Tiles[0], grassdata,sizeof(grassdata));
	memcpy(&Tiles[0x600], bagdata, sizeof(bagdata));
	memcpy(&OAM_Data[0], balldata,sizeof(balldata));
	memcpy(&OAM_Data[0x100], ball2data,sizeof(ball2data));
	memcpy(&OAM_Data[0x200], ball3data,sizeof(ball3data));
	memcpy(&OAM_Data[0x300], pointerdata,sizeof(pointerdata));
	memcpy(&OAM_Data[0x400], circledata,sizeof(circledata));

	//Copy Tilemap
	memcpy(&BG2Buffer[0], grasstiles, sizeof(grasstiles));
	memcpy(&BG3Buffer[0], bagtiles, sizeof(bagtiles));

	//Copy mapping
	//memcpy(&OAM_Data[0],balltiler1,sizeof(balltiler1)); //Each line is 0x20 words, or 0x40 bytes
	//memcpy(&OAM_Data[0x20],balltiler2,sizeof(balltiler1));
	//memcpy(&OAM_Data[0x40],balltiler3,sizeof(balltiler1));
	//memcpy(&OAM_Data[0x60],balltiler4,sizeof(balltiler1));
	//while(!pokemonChosen)  //main loop
	//{
	/*	u16 i = Music[0];
		Music[0] = i + 1;
		if(pointerIsUp)
		{
			pointerY--;
			if(pointerY == 0)
			{
				pointerY++;
				pointertimer++;
			}
			if(pointertimer >= 3)
			{
				pointerIsUp = false;
				pointertimer = 0;
			}
		}
		else
		{
			pointerY++;
			if(pointerY == 20)
			{
				pointerY--;
				pointertimer++;
			}
			if(pointertimer >= 3)
			{
				pointerIsUp = 1;
				pointertimer = 0;
			}
		}

		if(activeBall == 1)
		{
			sprites[5].attribute0 = COLOR_16 | SQUARE | 30 + pointerY;
		}
		else
		{
			sprites[5].attribute0 = COLOR_16 | SQUARE | 10 + pointerY;
		}
		timer++;
		if(timer > 110)
			timer = 0;
        	vsync();  //wait for screen to finish drawing.
        	CopyOAM();  //copy sprite info (OAM) into OAM memory
		GetInput();
		UpdateBallsandPointer();
        //}*/
	//asm("pop {r0-r7}");
	//jump(pFunc);
        return 0;
}

void UpdateBallsandPointer()
{
	sprites[5].attribute1 = sprites[activeBall + 2].attribute1;
	if(timer == 0)
	{
		sprites[activeBall + 2].attribute2 = 0x0;
	}
	if(timer == 10)
	{
		sprites[activeBall + 2].attribute2 = 0x10;
	}
	if(timer == 20)
	{
		sprites[activeBall + 2].attribute2 = 0x0;
	}
	if(timer == 30)
	{
		sprites[activeBall + 2].attribute2 = 0x20;
	}
	if(timer == 40)
	{
		sprites[activeBall + 2].attribute2 = 0x0;
	}
	if(timer == 50)
	{
		sprites[activeBall + 2].attribute2 = 0x10;
	}
	if(timer == 55)
	{	
		sprites[activeBall + 2].attribute2 = 0x0;
	}
	if(timer == 60)
	{
		sprites[activeBall + 2].attribute2 = 0x20;
	}
	if(timer == 65)
	{
		sprites[activeBall + 2].attribute2 = 0x0;
	}
	if(timer == 70)
	{
		sprites[activeBall + 2].attribute2 = 0x10;
	}
	if(timer > 75)
	{
		sprites[activeBall + 2].attribute2 = 0x0;
	}
}

int dirtomove = 3;
int circleVisible = 0;
void GetInput()
{
	if(keyDown(KEY_LEFT) && activeBall != 0 && dirtomove != 3  && !circleVisible)
	{
		lastKeyPress++;
		dirtomove = 1;
		if(lastKeyPress > 2)
		{
			sprites[activeBall + 2].attribute2 = 0x0;
			activeBall--;
			timer = 10;
			dirtomove = 0;
			lastKeyPress = 0;
			dirtomove = 3;
		}
	}
	else if(keyDown(KEY_RIGHT) && activeBall != 2 && dirtomove != 3 && !circleVisible)
	{
		lastKeyPress++;
		dirtomove = 2;
		if(lastKeyPress > 2)
		{
			sprites[activeBall + 2].attribute2 = 0x0;
			activeBall++;
			timer = 10;
			lastKeyPress = 0;
			dirtomove = 3;
		}
	}
	else if(keyDown(KEY_A) && dirtomove != 3)
	{
		if(!circleVisible)
		{
			circleVisible = 1;
			sprites[1].attribute0 = COLOR_16 | SQUARE | 33;  //set 256 colors, shape and y-coordinate 48
			sprites[1].attribute1 = SIZE_64 | 90;  //set shape and x-coordinate 88
			dirtomove = 3;
		}
		else
		{
			//Leave Routine
			pokemonChosen = 1;
			//jump(pFunc); // Store return value in LRESULT
		}
	}
	else if(keyDown(KEY_B) && circleVisible && dirtomove != 3)
	{
		circleVisible = 0;
		sprites[1].attribute0 = COLOR_16 | SQUARE | 160;  //set 256 colors, shape and y-coordinate 48
		sprites[1].attribute1 = SIZE_64 | 240;  //set shape and x-coordinate 88
	}

	if(!keyDown(KEY_LEFT) && !keyDown(KEY_RIGHT) && !keyDown(KEY_A) && !keyDown(KEY_B))
	{
		lastKeyPress = 0;
		dirtomove = 0;
	}
}

//function to copy all our sprite data from the table to OAM memory
void CopyOAM()
{
            u16 loop;
            u16* temp;
            temp = (u16*)sprites;
            for(loop = 0; loop < 128*4; loop++) //2 bytes at the time (2byte * 4 * 128 = 1024 bytes)
            {
                        OAM_Mem[loop] = temp[loop];
            }
}

//function that sets OAM data for all sprites, so that they are not shown on the screen.
//by setting coordinates to all sprites outside the visible area of the screen, they are not shown.
void InitializeSprites()
{
        for(u16 loop = 0; loop < 128; loop++)
        {
       		sprites[loop].attribute0 = 160;  //y to > 159
        	sprites[loop].attribute1 = 240;  //x to > 239
        	sprites[loop].attribute2 = 0;
        }
	sprites[2].attribute0 = COLOR_16 | SQUARE | 55;  //set 256 colors, shape and y-coordinate
	sprites[2].attribute1 = SIZE_32 | 45;  //set shape and x-coordinate
	sprites[2].attribute2 = 0x0;  //set shape and x-coordinate

	sprites[3].attribute0 = COLOR_16 | SQUARE | 75;  //set 256 colors, shape and y-coordinate
	sprites[3].attribute1 = SIZE_32 | 103;  //set shape and x-coordinate
	sprites[3].attribute2 = 0x0;  //set shape and x-coordinate

	sprites[4].attribute0 = COLOR_16 | SQUARE | 55;  //set 256 colors, shape and y-coordinate
	sprites[4].attribute1 = SIZE_32 | 160;  //set shape and x-coordinate
	sprites[4].attribute2 = 0x0;  //set shape and x-coordinate

	sprites[5].attribute0 = COLOR_16 | SQUARE | 13;  //set 256 colors, shape and y-coordinate
	sprites[5].attribute1 = SIZE_32 | 103;  //set shape and x-coordinate
	sprites[5].attribute2 = 0x30;  //set shape and x-coordinate

	sprites[1].attribute0 = COLOR_16 | SQUARE | 160;  //set 256 colors, shape and y-coordinate 48
	sprites[1].attribute1 = SIZE_64 | 240;  //set shape and x-coordinate 88
	sprites[1].attribute2 = PALETTE(0) | 0x40;  //Image location
}

int jump(u32 location)
{   asm("BX r0");   }

