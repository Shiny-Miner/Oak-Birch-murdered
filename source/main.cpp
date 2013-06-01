#include <string.h>
#include "gba.h"
#include "ball.h"
#define BG2Buffer     ((u8*)0x6003800)
#define Tiles     ((u16*)0x6000000)

int decompress(u32, u32);

int main()
{
	u16 x;
	SetMode(MODE_0 | BG2_ENABLE);
	BG2CNT=0x0703;
	memcpy(&BG_PaletteMem[0],ballpal,sizeof(ballpal));
	memcpy(&Tiles[0],balldata,sizeof(balldata));
	memcpy(&BG2Buffer[0],balltile,sizeof(balltile));
        return 0;
}

int decompress(u32 location, u32 destination)
{   asm("swi 0x12");   }

