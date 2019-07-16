#include<iostream>
//#include "amoeba.h"


using namespace std;

Amoeba::Amoeba(void)		//Implementation des Konstruktors
{
   AcidTime = 0;
   NonAcidTime = 0;

// Amoeba-Status Ohne Pilz: 0; Mit Pilz und Versäuert: 1; Mit Pilz und nicht versäuert: 2
   AmoebaStatus = 0;

}

// Diese Methode setzt den Status eines Amoeba-Objektes, sobald ein Pilz gefressen wird
void Amoeba::SetInitialAcidTime(int SetAcidTime, int SetNonAcidTime, int SetAmoebaStatus)
{
   AcidTime = SetAcidTime;
   NonAcidTime = SetNonAcidTime;
   AmoebaStatus = SetAmoebaStatus;

   if(AcidTime > 0 && NonAcidTime > 0)
        AmoebaStatus = 1;

   if(AcidTime == 0 && NonAcidTime > 0)
        AmoebaStatus = 2;

   if(AcidTime == 0 && NonAcidTime == 0)
        AmoebaStatus = 0;

}

void Amoeba::SetUpdateAcidTime(int TimeStep)
{
    if(AcidTime > 0 && NonAcidTime > 0)
        AcidTime = AcidTime - TimeStep;
    else if(AcidTime == 0 && NonAcidTime > 0)
        NonAcidTime = NonAcidTime - TimeStep;

    if(AcidTime > 0 && NonAcidTime > 0)
        AmoebaStatus = 1;

    if(AcidTime == 0 && NonAcidTime > 0)
        AmoebaStatus = 2;

    if(AcidTime == 0 && NonAcidTime == 0)
        AmoebaStatus = 0;
}



