#include<random>
#include<iostream>
#include <iomanip>
#include<fstream>
#include <string>
#include <cstring>
#include <ctime>
#include<stdio.h>
using namespace std;

int AmoebaAmount = 0;
int AmoebaChannels = 0;
int MedianExpulsionTime = 0;       // in minutes
int MedianAcidicPositiveTime = 0; // in minutes
int TotalProcessTime = 0;        // in minutes
int PhagocytosisRate = 0;         // in percentage per hour
int MedianNeutralCompartmentTime = 0;
int ShowTimeDevelopment = 0;
int ResultsToScreenOrFile =0;
string AnalysisFilename;

//Definition der Amoeba-Klasse
#include"amoeba.h"
#include"amoeba.cpp"

//Filehandling
#include"fileIO.h"
#include"fileIO.cpp"



int main(int argc, char** args)
{


    //Einlesen der Werteparameter (Funktion wurde nach fileIO ausgelagert)
    ReadParameters();

    //AmoebaAnzahl entspricht der Amoebenanzahl multipliziert mit der gleichzeitig zu verarbeitenden Pilzmenge
    int AmoebaAnzahl = AmoebaAmount * AmoebaChannels;

    //Mersenne Twister is a pseudorandom number generator
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0, 100);

    //Erzeugung eines Arrays von Amoeba-Objekten
    Amoeba *Gruppe=0;
    Gruppe = new Amoeba[AmoebaAnzahl];

    float RandNo = 0;

    for (int i=0; i< TotalProcessTime; i++)
    {
            for (int Index = 0 ; Index < AmoebaAnzahl ; Index++)
            {
                //Falls die aktuelle Amoebe i gerade einen Pilz verarbeitet (Status 1 für Acid, Status 2 für NonAcid)
                //so zähle die Restzeit (MedianExpulsionTime) um eine Minute herunter
                if (Gruppe[Index].AmoebaStatus == 1 || Gruppe[Index].AmoebaStatus == 2)
                Gruppe[Index].SetUpdateAcidTime(1);

                RandNo = dis(gen);

                //Falls die aktuelle Amoebe i gerade keinen Pilz verarbeitet (Status 0)
                //so ist sie mit 1/60 der PhagocytosisRate jetzt einen Pilz
                if (Gruppe[Index].AmoebaStatus == 0 &&  RandNo < (PhagocytosisRate/60.0))
                Gruppe[Index].SetInitialAcidTime(MedianAcidicPositiveTime, MedianNeutralCompartmentTime, 1);
            }

      CalculateDetailedTimeDevelopment(AmoebaAnzahl, Gruppe, i);

    }

    //Auswertung der Amoeben

    CalculateResult(AmoebaAnzahl, Gruppe);



    return 0;
}

