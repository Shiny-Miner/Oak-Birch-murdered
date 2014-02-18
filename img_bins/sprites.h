const Oam ballOam = {01,3,50,0x80,0x1,0};
unsigned char ballAnimation[8] = {  1, 0, 0xA, 0,
					0xFE, 0xFF, 0, 0 };
unsigned char ballWiggleAnimation[48] = {  
					1, 0, 0x5, 0,
					1+32, 0, 0x5, 0,
					1, 0, 0x5, 0,
					1+16, 0, 0x5, 0,
					1, 0, 35, 0,

					1, 0, 0xA, 0,
					1+16, 0, 0xA, 0,
					1, 0, 0xA, 0,
					1+32, 0, 0xA, 0,
					1, 0, 0xA, 0,
					1+16, 0, 0xA, 0,

					0xFE, 0xFF, 0, 0 };
const unsigned int ballAnimTable[2] = { &ballAnimation, &ballWiggleAnimation};
const ObjTemplate ballTemplate = {2,1,&ballOam,&ballAnimTable,0,0x08231CFC,0x080EE4DD,0xFF};

//

const Oam pointerOam = {50,3,50,0x80,0x1,0};
unsigned char pointerAnimation[8] = {  1+48, 0, 0xA, 0,
					0xFE, 0xFF, 0, 0 };
const unsigned int pointerAnimTable = &pointerAnimation;
const ObjTemplate pointerTemplate = {2,1,&pointerOam,&pointerAnimTable,0,0x08231CFC,0x080EE4DD,0xFF};

//

const Oam circleOam = {50,3,50,0xC0,0x1,0};
unsigned char circleAnimation[8] = {  1+64, 0, 0xA, 0,
					0xFE, 0xFF, 0, 0 };
unsigned char nopAnimation[8] = {  1+128+64, 0, 0xA, 0,
					0xFE, 0xFF, 0, 0 };
const unsigned int circleAnimTable[2] = {&circleAnimation, &nopAnimation};
const ObjTemplate circleTemplate = {2,1,&circleOam,&circleAnimTable,0,0x08231CFC,0x080EE4DD,0xFF};

//

const Oam monOam = {50,3,50,0xC0,0x1,0};
unsigned char monAnimation[8] = {  1+128, 0, 0xA, 0,
					0xFE, 0xFF, 0, 0 };
const unsigned int monAnimTable[2] = {&monAnimation, &nopAnimation};
const ObjTemplate monTemplate = {2,1,&monOam,&monAnimTable,0,0x08231CFC,0x080EE4DD,0xFF};
