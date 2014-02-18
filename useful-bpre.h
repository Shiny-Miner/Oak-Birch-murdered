#define objBaseAddr		 (u8  *) 0x0202063C
#define OAMBuffer		 ((OAMThingy*)objBaseAddr)
#define dummyAnimData	 (u32 *) 0x08231CFC
#define dummyAnimRoutine (u32 *) 0x0800760D
#define spriteTable ((u32*)0x082350AC)
#define paletteTable ((u32*)0x0823730C)

//Memory Locations
#define OAM_Mem 	       ((u16*)0x03003128)
#define OBJ_PaletteMem        ((u16*)0x020373F8) // Sprite Palette(256/16 colors) (adjusted for FR callback)
#define BG_PaletteMem          ((u16*)0x020371F8) // Background Palette(256/16 colors) (adjusted for FR callback)
#define BG_PaletteMem2          ((u16*)0x020375F8) // Background Palette(256/16
#define OBJ_PaletteMem2        ((u16*)0x020377F8) // Sprite Palette(256/16 colors)

//Key Stuffs
#define KEYS         *(volatile u8*)0x0300311E
#define KEYSHOLD     *(volatile u8*)0x0300311C
#define KEYSLR       *(volatile u8*)0x0300311F
#define KEYSHOLDLR   *(volatile u8*)0x0300311D
#define keyPressed(k)    (KEYS & k)
#define keyHeldDown(k)   (KEYSHOLD & k)
#define keyPressedLR(k)  (KEYSLR & k)
#define keyHeldDownLR(k) (KEYSHOLDLR & k)

//Variables and Such
#define LASTRESULT		(*(u16 *) 0x020370D0)
#define var8004			(*(u16 *) 0x020370C0)
#define fadeScreenDone	(*(u8  *) (0x02037AB8 + 7))
#define globalVars		(*(u32 *) 0x0203BCD0)
#define boxInitStuff	0x083E22C0
#define nullCallback	0x08015B59

//RoA Sounds 
#define EMPTYMOVESOUND  0x05 
#define TILEMOVESOUND   0x1D 
#define ERRORSOUND      0x1A 
#define TAKETILESOUND   0x1E 
#define DROPTILESOUND   0x26 
#define WINSONG         0x10D 

void updateEverything()
{
	int (*callback3)(void) = (int (*)(void))0x08077579;
	callback3();

	int (*callbackOAM)(void) = (int (*)(void))0x08006B5D; //call_back_oam
	callbackOAM();
	
	int (*writeOAM)(void) = (int (*)(void))0x08006BA9; //write oam
	writeOAM();
	
	int (*func4)(void) = (int (*)(void))0x080704D1; //idk
	func4();
}

void updateEverything2()
{
	int (*func)(void) = (int (*)(void))0x08007321;
	func();
	
	int (*func2)(void) = (int (*)(void))0x08007611;
	func2();
	
	int (*func3)(void) = (int (*)(void))0x08070475;
	func3();
}

u32 malloc(int *size)
{
	int (*func)(u32) = (int (*)(u32))0x08002B9D;
	return func(size);
}

void free(int *addr)
{
	int (*func)(u32) = (int (*)(void))0x08002BC5;
	func(addr);
}

void unfadeScreen()
{
	fadeScreen2(0xFFFFFFFF,0x0,0x10,0,0x0000);
}

void fadeScreen()
{
	fadeScreen2(0xFFFFFFFF,0x0,0,0x10,0x0000);
}

void fadeScreen2(int *bitmask, int *r1, int *r2, int *r3, int *color)
{

	int (*func)(u32,u16,u16,u16,u16) = (int (*)(void))0x08070589;
	func(bitmask,r1,r2,r3,color);
		
}

void oam_rotate(u8 oam, u16 x, u16 y, u16 rot)
{
	int (*func)(u8,u16,u16,u16) = (int (*)(void))0x08075859;
	func(oam,x,y,rot);
}

void copyPal(void *source, u8 num)
{
	copyMem(source,BG_PaletteMem+(num*0x10),0x8);
	copyMem(source,BG_PaletteMem2+(num*0x10),0x8);
}

void copyCompPal(void *source, u8 num)
{
	LZ77UnCompWram(source,BG_PaletteMem+(num*0x10));
	LZ77UnCompWram(source,BG_PaletteMem2+(num*0x10));
}

void copyMem(void *source, void *dest, void *size)
{
	SystemCall(0xC);
}

void playFanfare(int *fanfareNum)
{
	int (*func)(void) = (int (*)(void))0x08071C61;
	func();
}

u8 waitForFanfare() {

	int (*func)(void) = (int (*)(u8))0x08071C9D;
	return func();
	
}

void playSound(int *fxNum)
{
	int (*func)(void) = (int (*)(void))0x080722CD;
	func();
}

//TODO Actally call function
u8 waitForSound() {

	return 0;
	//int (*func)(void) = (int (*)(u8))0x080A38A1;
	//return func();
	
}

void changeIO(int *offset, int *value)
{
	int (*func)(void) = (int (*)(void))0x08000A39;
	func();
}

void enableBG(int *BG)
{
	int (*func)(void) = (int (*)(void))0x080019BD;
	func();
}

void clearOAM()
{
	int (*func)(void) = (int (*)(void))0x08006B11;
	func();
}

//TODO figure out what the heck this is
void initStuff()
{
	clearOAM();
	
	int (*func2)(void) = (int (*)(void))0x080088F1; //Still no idea
	func2();
	
	int (*func3)(u8) = (int (*)(void))0x08001619; //Still no idea about this one either
	func3(0x0);
	
}

//Unsure about this guy...
void storeCallback(int *addr)
{	
	int (*func)(void) = (int (*)(void))0x08000545;
	func();
}

void storeCallback2(int *addr)
{
	int (*func)(void) = (int (*)(void))0x080006F5;
	func();
}	

u32 createSprite(int *addr2, int *XPos, int *YPos, int *i)
{
	int (*func2)(u32,u16,u16,u8) = (int (*)(u8))0x08006F8D;
	u32 result = func2(addr2,XPos,YPos,0);
	return result;
	
}

void loadGFX(int *addr)
{
	int (*func)(u32) = (int (*)(void))0x080086DD; //load_gfx
	func(addr); 
}

void loadCompressedGFX(void *addr)
{
	int (*func)(u32) = (int (*)(void))0x0800F035; //load_gfx
	func(addr); 
}

void loadPalette(int *addr, int *offset, int *length)
{
	int (*func)(u32,u8,u8) = (int (*)(void))0x080703ED;
	func(addr,offset,length);
	
}

const u8 instsData[3] = {
	0x0, 0x3, 0x2
};

void boxPrint(u8 foo, u8 font, u8 x, u8 y, u32 bar, u32 baz, u32 txtpointer)
{
	int (*func3)(u8,u8,u8,u8,u32,u32,u32) = (int (*)(void))0x0812E51D;
	func3(foo,font,x,y,bar,baz,txtpointer);
}

void writeBoxToTilemap(u8 a, u8 b)
{
	int (*func5)(u8,u8) = (int (*)(void))0x08003F21;
	func5(a,b);
}

void initText(u8 background, u8 type)
{
	int (*func2)(u8,u8) = (int (*)(void))0x0800445D;
	func2(background,type);
}

void loadTutorialText(u32 *textAddr) 
{
	int (*func)(u8) = (int (*)(u32))0x08150409;		//load tutorial bar palette
	loadPalette(func(2),0xB0,0x20);
	initText(0x3,0x11);
	boxPrint(0x0,0x1,134,0x1,instsData,0x00000000,textAddr);
	
	int (*func4)(u8) = (int (*)(void))0x08003FA1;
	func4(0x0); //Something with BGs
	
	writeBoxToTilemap(0x0,3);	
}

void enableBox(u8 bg)
{
	int (*func4)(u8) = (int (*)(void))0x08003FA1;
	func4(bg); //Something with BGs
}

void drawText(u32 *textAddr, u8 x, u8 y)
{
	int (*func)(u8) = (int (*)(u32))0x08150409;		//load tutorial bar palette
	loadPalette(func(2),0xB0,0x20);
	initText(0x0,0xFF);
	boxPrint(0x0,0x0,x,y,instsData,0x00000000,textAddr);
	
	int (*func4)(u8) = (int (*)(void))0x08003FA1;
	func4(0x0); //Something with BGs
	
	writeBoxToTilemap(0x0,3);	
}

void reloadTutorialText(u32 *textAddr, int shortText) 
{
	initText(0x0,0xFF);
	boxPrint(0x0,0x0,134 + (shortText == 1 ? 68 : 0),0x1,instsData,0x00000000,textAddr);
}

void initMapData(u8 *r0, u32 *r1, u8 *r2)
{
	int (*func)(u8,u32,u8) = (int (*)(void))0x08001659;
	func(r0,r1,r2);
}

void someExitFunc()
{
	int (*func)(void) = (int (*)(void))0x08003ECD;
	func();
}

int textboxBGInit(u32 *addr)
{
	int (*func)(u32) = (int (*)(void))0x08003B24+1;
	return func(addr);
}

void prepTextSpace(u8 r0, u8 r1)
{
        int (*func)(u8,u8) = (int (*)(void))0x080F6EE4+1;
        func(r0,r1);
}

int loadNormalTextbox(u8 r0, u8 r1, u32 textPointer, u8 r3, u8 sp0, u8 sp4, u8 sp8)
{
        int (*func)(u8,u8,u32,u8,u8,u8,u8) = (int (*)(void))0x08002C48+1;
        return func(r0,r1,textPointer,r3,sp0,sp4,sp8);
}

void somethingPicbox(u8 r0, u8 r1, u8 r2, u8 r3)
{
	int (*func)(u8,u8,u8,u8) = (int (*)(void))0x0809CDEC+1;
	//func(r0,r1,r2,r3);
}

void yesNoBox()
{
	int (*func)() = (int (*)(void))0x0809CDEC+1;
	func();
}

void iDunno(u32 something)
{
	int (*func)(u32) = (int (*)(void))0x081119D4+1;
	func(something);
}

void loadSpritePal(u32 *addr)
{
	int (*func)(u32) = (int (*)(void))0x08008929;
	func(addr);
}

void loadMessageBoxBorders(int tile, int pal)
{
        int (*func)(u8,u16,u8) = (int (*)(void))0x0814FEAC+1;
        func(pal,tile,0xF0);
        
        //int (*func2)(u8,u16,u8) = (int (*)(void))0x0809882D;
        //func2(0x0,(0x85 << 0x2),0xE0);
}

void loadStandardBoxBorders(int tile, int pal)
{
        int (*func)(u8,u16,u8) = (int (*)(void))0x0814FF2C+1;
        func(pal,tile,0xF0);
        
        //int (*func2)(u8,u16,u8) = (int (*)(void))0x0809882D;
        //func2(0x0,(0x85 << 0x2),0xE0);
}
//0814FF2C
