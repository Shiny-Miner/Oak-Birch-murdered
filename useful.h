/* Useful Data For Pokemon Hacking
   By Tinix                       */

#define pLRESULT_FR 33779920 // 0x020270B6 + (0x800D * 2) in Hex, direct converion via assign screws it up, IDK why
#define pLRESULT_E  33781232 
#define pLRESULT_RS 33745116
#define pPlyer_FR  0x0300500C // start of struct
#define pPlyer_RS  0x02024EA4 
#define pPlyer_E   0x03005D90
#define pPKMN_FR   0x02024284 // start of struct
#define pPKMN_R    0x03004360 // start of struct
#define pPKMN_S    0x03004360 // start of struct
#define pPKMN_E    0x02024190 // start of struct
#define pPKMN_E_US 0x020244EC // start of struct
#define pPKMN_LG   0x020241E4 // start of struct
#define pPKMN_SIZE 100 // bytes 

typedef char BYTE; // To avoid confusion

struct PLYR_DATA_S
{
/* Thanks to HackMews ASM tutorial for structure & offset*/
	char Name[8];  
	BYTE Gender; 
	BYTE unk1; 
	short Trainer_ID; 
	short Secret_ID;
	short Hours_of_play; 
	BYTE Minutes; 
	BYTE Seconds; 
	BYTE Frames; 
	BYTE unk2;
	short Options;
};

struct PKMN_DATA_S
{
	int  Personality;
	int  OT_ID;
	char Nickname[10];
	short Language;
	char OT_NAME[7];
	BYTE Mark;
	short Checksum;
	short unk1;
	BYTE Data[48];
	int status_aliment;
	BYTE Level;
	BYTE pokerus_rem;
	short CurHP;
	short TotalHP;
	short Att;
	short Def;
	short Speed;
	short SpAtt;
	short SpDef;
};

typedef struct PLYR_DATA_S PLYR_DATA;
typedef struct PKMN_DATA_S PKMN_DATA;
