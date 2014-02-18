#include "include/gba.h"
#include "useful.h"
#include "img_bins/ball1.c"
#include "img_bins/ball2.c"
#include "img_bins/ball3.c"
#include "img_bins/sprites.h"
#include "img_bins/grass.c"
#include "img_bins/bag.c"
#include "img_bins/pointer.c"
#include "img_bins/circle.c"
#include "img_bins/workaround.c"

#define DMA3Source		(*(u32 *) 0x040000D4)
#define DMA3Dest		(*(u32 *) 0x040000D8)
#define DMA3Options		(*(u32 *) 0x040000DC)

#define Tiles   ((u16 *) 0x6008000)
#define MapData ((u16 *) 0x600E800)
#define BG0Data ((u16 *) 0x600E800)
#define BG2Data ((u16 *) 0x600E000)
#define OBJData ((u16 *) 0x6010000)
#define MenuBG  ((u16 *) 0x600F800)

#define starterUno 	10
#define starterDos 	128
#define starterTres	206

void InitializeSprites();
void GetInput();

#define currentLoop 		(*(u8 *) (globalVars + 0x0))
#define activeBall  		(*(u8 *) (globalVars + 0x1))
#define timer 			(*(u16 *) (globalVars + 0x2))
#define lastKeyPress  		(*(u8 *) (globalVars + 0x4))
#define pointertimer  		(*(u8 *) (globalVars + 0x5))
#define pointerIsUp  		(*(u8 *) (globalVars + 0x6))
#define pointerY  		(*(u8 *) (globalVars + 0x7))
#define circleinfront  		(*(u8 *) (globalVars + 0x8))
#define pokemonChosen  		(*(u8 *) (globalVars + 0x9))
#define dirtomove  		(*(u8 *) (globalVars + 0xA))
#define circleVisible  		(*(u8 *) (globalVars + 0xB))
#define ballStart  		(*(u16 *) (globalVars + 0xC))
#define meep	  		(*(u16 *) (globalVars + 0xE))
#define meep2	  		(*(u16 *) (globalVars + 0x10))
#define circleStart  		(*(u16 *) (globalVars + 0x12))

void init2();
void init3();
void main();

void init() {

	storeCallback((void *) init2 + 1);
}

#include "include/gba_compress.h"

//Select the proper useful.h for the version we're compiling
#ifdef engine
#if engine == 1
	#include "useful-bpee.h"
#else
	#include "useful-bpre.h"
#endif
#endif

unsigned char starters[3] = {19, 129, 11};

void init2() {

	storeCallback2(0);
	globalVars = malloc(0x80);						
	
	int blank = 0;
	DMA3Source = &blank;
	DMA3Dest = globalVars;
	DMA3Options = 0x81000040;						
	
	currentLoop = 0;
	
	storeCallback((void *) init3 + 1);
	
}

void init3() {
	for(int i=0x10;i<0x20;i+=2) changeIO(i,0);
	
	initStuff();
	
	const u32 mapDataUnk[2] = {
		0x000001E0, 0x000011D9
	};
	
	initMapData(0x1,mapDataUnk,0x2);
	
	storeCallback((void *) main + 1);
	LASTRESULT = 0xFF;
}

void main()
{
	if (currentLoop == 0) 
	{
		activeBall = 1;
		circleinfront = 1;
		dirtomove = 3;
		
		initVideo();
		initBG();
		InitializeSprites();
		
		unfadeScreen();
		currentLoop++;
		storeCallback2((void *) updateEverything2 + 1);
	
	}
	
	else if (currentLoop == 1) 
	{
		if (fadeScreenDone == 0)
			currentLoop++;
	}
	
	else if (currentLoop == 2) 
	{
		if (!pokemonChosen) 
		{
			GetInput();
			if(circleVisible)
			{
				if(meep > 0xCA)
				{
						meep -= (meep / 8);
				}
				if(meep < 0xCA)
				{
					meep = 0xCA;
				}
				oam_rotate(circleStart, meep, meep, 0);
				oam_rotate(circleStart+1, meep + (0x100 - 0xCA), meep + (0x100 - 0xCA), 0);
				if(LASTRESULT == 0x1)
					pokemonChosen = 1;
				else if(LASTRESULT == 0x0)
					returnToSelect();
			}
		}
		
		else 
		{
			if (waitForSound() == 0) 
			{
				playFanfare(WINSONG);
				currentLoop++;
			}
		}
	}
	
	else if (currentLoop == 3) 
	{
		
		if (waitForFanfare() == 1) 
		{                        
			// Ignore A or B until the fanfare is done
			if (keyPressed(KEY_A) || keyPressed(KEY_B)) 
			{   
				// Wait until the player presses A or B
				LASTRESULT = 1;
				fadeScreen();
				currentLoop++;
			}
		}
	}
	
	else if (currentLoop == 4) 
	{
		if (fadeScreenDone == 0) 
		{
			storeCallback(nullCallback);
			if (globalVars != 0) 
			{
				free(globalVars);
				globalVars = 0;
			}
			someExitFunc();
		}
	}

	animatePointer();
	updateEverything();	
}

void animatePointer()
{
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
				pointerIsUp = 0;
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
			OAMBuffer[ballStart+3].pos1.y = 45 + pointerY;
		}
		else
		{
			OAMBuffer[ballStart+3].pos1.y = 20 + pointerY;
		}
		timer++;
		if(timer > 110)
			timer = 0;
}

void initVideo() {

	changeIO(0,OBJ_ENABLE | OBJ_MAP_1D);
	
	u32 x = 0x80 << 5;
	u32 endAddr = 0xC0 << 0x13;
	int blank = 0;
	
	for(u32 i = 0xC0 << 9; i > x ; i -= x, endAddr += x) {
		DMA3Source = &blank;
		DMA3Dest = endAddr;
		DMA3Options = 0x81000800;
	}
	
	textboxBGInit(boxInitStuff);
	
	enableBG(0);
	enableBG(1);
	
	changeIO(0x4, 0x1E08);
	changeIO(0x6, 0x1C46);
	changeIO(0x8,(0x1E << SCREEN_SHIFT));
	changeIO(0xA,(0x1D << SCREEN_SHIFT) | (2 << CHAR_SHIFT) | 3);
	changeIO(0,0x3740);
	
}

const u8 textboxData[12] = { //BG number, X pos, Y pos, width, height, palette slot, tile number (2 bytes), list terminator
        0x00, 0x03, 0x0F, 0x18, 0x04, 0x0E, 0x94, 0x02, 0xFF, 0x0, 0x0, 0x0
};

const u8 textboxTransData[12] = { //BG number, X pos, Y pos, width, height, palette slot, tile number (2 bytes), list terminator
        0x00, 0x10, 0x0A, 0xD, 0x05, 0x0F, 0x94, 0x02, 0xFF, 0x0, 0x0, 0x0
};

const u8 murderText[61] = { //PROF. BIRCH is in trouble!\nRelease a POKEMON and rescue him!
        0xCA, 0xCC, 0xC9, 0xC0, 0xAD, 0x00, 0xBC, 0xC3, 0xCC, 0xBD, 0xC2, 0x00, 0xDD, 0xE7, 0x00, 0xDD, 0xE2, 0x00, 0xE8, 0xE6, 0xE3, 0xE9, 0xD6, 0xE0, 0xD9, 0xAB, 0xFE, 0xCC, 0xD9, 0xE0, 0xD9, 0xD5, 0xE7, 0xD9, 0x00, 0xD5, 0x00, 0xCA, 0xC9, 0xC5, 0x1B, 0xC7, 0xC9, 0xC8, 0x00, 0xD5, 0xE2, 0xD8, 0x00, 0xE6, 0xD9, 0xE7, 0xD7, 0xE9, 0xD9, 0x00, 0xDC, 0xDD, 0xE1, 0xAB, 0xFF,
};

const u8 choiceText[28] = { //Do you choose this POKEMON?
0xBE, 0xE3, 0x00, 0xED, 0xE3, 0xE9, 0x00, 0xD7, 0xDC, 0xE3, 0xE3, 0xE7, 0xD9, 0x00, 0xE8, 0xDC, 0xDD, 0xE7, 0x00, 0xCA, 0xC9, 0xC5, 0x1B, 0xC7, 0xC9, 0xC8, 0xAC, 0xFF, 0xCA, 0xC9, 0xC5, 0x1B, 0xC7, 0xC9, 0xC8, 0xFF
};

const u8 monText[36] = { //Do you choose this POKEMON?
0xFC, 0x0F, 0xFC, 0x06, 0x0, 0xBE, 0xE3, 0x00, 0xED, 0xE3, 0xE9, 0x00, 0xD7, 0xDC, 0xE3, 0xE3, 0xE7, 0xD9, 0xFE, 0xFC, 0x06, 0x00, 0xE8, 0xDC, 0xDD, 0xE7, 0x00, 0xCA, 0xC9, 0xC5, 0x1B, 0xC7, 0xC9, 0xC8, 0xAC, 0xFF, 0xCA, 0xC9, 0xC5, 0x1B, 0xC7, 0xC9, 0xC8, 0xFF
};

void initBG0WithText()
{
	loadMurderText();
	//loadSemiTransText();
	//somethingPicbox(1,2,3,4);
	iDunno(0x0809D6D4+1);

	loadStandardBoxBorders(532,0);
	loadMessageBoxBorders(512,0);
	copyPal(&palWorkaround,14);
}

void loadChoiceText()
{
	int box = textboxBGInit(textboxData);
	enableBox(box);
	prepTextSpace(0,0);
        loadNormalTextbox(0,1,choiceText,0,1,0,0);
	writeBoxToTilemap(0,3);
}

void loadMurderText()
{
 	int box = textboxBGInit(textboxData);
	enableBox(box);
	prepTextSpace(0,0);
	//writeBoxToTilemap(box,3);

        loadNormalTextbox(0,1,murderText,0,1,0,0);
	writeBoxToTilemap(0,3);
}

void loadSemiTransText()
{
	int box = textboxBGInit(textboxTransData);
	//initText(box,1);
	//prepTextSpace(0,0);
	BG_PaletteMem[(15*16)+1] = 0x0;
	BG_PaletteMem2[(15*16)+1] = 0x0;

	BG_PaletteMem[(15*16)+3] = 0x7FFF;
	BG_PaletteMem2[(15*16)+3] = 0x7FFF;

	//prepTextSpace(1,2);
	//box = 1;
	//loadNormalTextbox(box,1,murderText,0,1,0,0);
	enableBox(box);
	boxPrint(0,1,50,50,instsData,0x00000000,monText);
        writeBoxToTilemap(box,3);

	BLDMOD = 0xFE;
	COLEY = 0x7;
	WININ = 0x3F;
	WINOUT = 0x1F;
}

void initBG() {
	
	//drawText(tutorialText,34,7);
	
	//Copy Palettes...
	copyPal(ball1Pal,16);
	copyPal(grassPal,0);
	copyPal(bagPal,1);

	u32 ball1[2] = {
		&ball1Tiles, 0x00000200
	};

	u32 ball2[2] = {
		&ball2Tiles, 0x00000200
	};

	u32 ball3[2] = {
		&ball3Tiles, 0x00000200
	};

	u32 pointer[2] = {
		&pointerTiles, 0x00000200
	};

	u32 circle[2] = {
		&circleTiles, 0x00000800
	};

	LZ77UnCompVram(grassTiles, Tiles);
	LZ77UnCompVram(bagTiles,Tiles-0x4000);
	loadCompressedGFX(ball1);
	loadCompressedGFX(ball2);
	loadCompressedGFX(ball3);
	loadCompressedGFX(pointer);
	loadCompressedGFX(circle);

	//Copy Tilemap
	LZ77UnCompVram(grassMap, BG0Data);
	LZ77UnCompVram(bagMap, BG2Data);
	initBG0WithText();
}

void GetInput()
{
	if(keyPressed(KEY_LEFT) && activeBall != 0  && !circleVisible)
	{
		lastKeyPress++;
		dirtomove = 1;
	 	OAMBuffer[ballStart+activeBall].animFrame = 12;
	 	OAMBuffer[ballStart+activeBall].animNum = 0;
		activeBall--;
		OAMBuffer[ballStart+activeBall].animNum = 1;
		OAMBuffer[ballStart+3].pos1.x = OAMBuffer[ballStart+activeBall].pos1.x;
		timer = 10;
		dirtomove = 0;
		lastKeyPress = 0;
		dirtomove = 3;
	}
	else if(keyPressed(KEY_RIGHT) && activeBall != 2 && !circleVisible)
	{
		lastKeyPress++;
		dirtomove = 2;
	 	OAMBuffer[ballStart+activeBall].animFrame = 12;
		OAMBuffer[ballStart+activeBall].animNum = 0;
		activeBall++;
		OAMBuffer[ballStart+activeBall].animNum = 1;
		OAMBuffer[ballStart+3].pos1.x = OAMBuffer[ballStart+activeBall].pos1.x;
		timer = 10;
		lastKeyPress = 0;
		dirtomove = 3;
	}
	else if(keyPressed(KEY_A))
	{
		if(!circleVisible)
		{
			circleVisible = 1;
			LZ77UnCompVram(spriteTable[(starters[activeBall])*2], monSpriteLoc);
			copyCompPal(paletteTable[(starters[activeBall])*2],17);
			OAMBuffer[circleStart].animNum = 0;
			OAMBuffer[circleStart+1].animNum = 0;
			loadChoiceText();
			yesNoBox();
		}
	}
}

void returnToSelect()
{
	circleVisible = 0;
	OAMBuffer[circleStart].animNum = 1;
	OAMBuffer[circleStart+1].animNum = 1;
	meep = 0x6CA;
	LASTRESULT = 0xFF;
	loadMurderText();
}

void InitializeSprites()
{
	clearOAM();
	ballStart = createSprite(&ballTemplate,0x3C,0x40,5);
	createSprite(&ballTemplate,0x78,0x58,0);
	createSprite(&ballTemplate,0xB4,0x40,0);
	createSprite(&pointerTemplate,0x78,38,0);
	circleStart = createSprite(&circleTemplate,0x78,60,0);
	createSprite(&monTemplate,0x78,60,0);
	for(int i = ballStart; i < ballStart+5; i++)
	{
		OAMBuffer[i].oam.tileProPal = 2 << 10; //Lower the priority so that the circle + starter comes out on top
		if(i == ballStart+1)
			OAMBuffer[i].animNum = 1;
	}
	OAMBuffer[circleStart].animNum = 1;
	OAMBuffer[circleStart+1].animNum = 0;
	OAMBuffer[circleStart].oam.tileProPal = 1 << 10;
	OAMBuffer[circleStart+1].oam.tileProPal = 0x1000;
	meep = 0x6CA;
	oam_rotate(circleStart, meep, meep, 0);
	oam_rotate(circleStart+1, meep, meep, 0);
}

