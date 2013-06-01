#include "useful.h"
void GetMaxLvl()
{
   PKMN_DATA* pPKMN_DATA = (PKMN_DATA*) pPKMN_FR;
   int* LRESULT = (int*) pLRESULT_FR;
   *LRESULT = pPKMN_DATA->Level;
}
