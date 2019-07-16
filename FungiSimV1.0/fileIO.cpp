void ReadParameters()
{
      //This is only a gimmick to display the calculation date and time
      time_t rawtime;
      struct tm * timeinfo;
      char buffer[80];
      time (&rawtime);
      timeinfo = localtime(&rawtime);
      strftime(buffer,sizeof(buffer),"%d-%m-%Y %H:%M:%S",timeinfo);
      std::string str(buffer);
      //End of gimmick

      std::cout << "FungiSim V1.0  This calculation run was performed on  " << str <<  '\n';
      std::cout <<  '\n';

      char   dummy[255];
      ifstream fin("Parameters.txt", ios::in);
      if(!fin.good())
      cerr << "Error opening Parameters.txt" << endl;

      fin.precision(20);

     //Total amount of amoeba
      fin.getline(dummy,200);    // skip line of explanation
      fin >> AmoebaAmount;
      std::cout << "Total amount of amoeba:  " << AmoebaAmount << '\n';

     //Maximum fungi per amoeba in parallel
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> AmoebaChannels;
      std::cout << "Maximum fungi per amoeba in parallel:  " << AmoebaChannels << '\n';

      //Median expulsion time (in minutes)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> MedianExpulsionTime;
      std::cout << "Median expulsion time (in minutes):  " << MedianExpulsionTime << '\n';

      //Median acidic positive time (in minutes)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> MedianAcidicPositiveTime;
      std::cout << "Median acidic positive time (in minutes):  " << MedianAcidicPositiveTime << '\n';

      //Total process time to consider (in minutes)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> TotalProcessTime;
      std::cout << "Total process time to consider (in minutes):  " << TotalProcessTime << '\n';

      //Phagocytosis rate (in percentage per hour)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> PhagocytosisRate;
      std::cout << "Phagocytosis rate (in percentage per hour):  " << PhagocytosisRate << '\n';

       //Show detailed time development of acidic amoebas (1=yes, 0=no)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> ShowTimeDevelopment;
      std::cout << "Show detailed time development of acidic amoebas (1=yes, 2=no):  " << ShowTimeDevelopment << '\n';

     //Write results to screen or file (1=screen, 0=file)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> ResultsToScreenOrFile;

      //Filename for output of results (Filename.txt)
      fin.getline(dummy,200);    // skip end of line
      fin.getline(dummy,200);    // skip line of explanation
      fin >> AnalysisFilename;

      MedianNeutralCompartmentTime = MedianExpulsionTime - MedianAcidicPositiveTime;
      if (MedianNeutralCompartmentTime < 1)
      std::cout << "Invalid MedianAcidicPositiveTime and.or invalid MedianExpulsionTime" << '\n';

      std::cout << "\n";

      ofstream myAnalysis;
      myAnalysis.open (AnalysisFilename, ios::out | ios::trunc);

      if(ResultsToScreenOrFile==0)
      {
       myAnalysis << "FungiSim V1.0  This calculation run was performed on  " << str <<  '\n';
       myAnalysis <<  '\n';
       myAnalysis << "Total amount of amoeba:  " << AmoebaAmount << '\n';
       myAnalysis << "Maximum fungi per amoeba in parallel:  " << AmoebaChannels << '\n';
       myAnalysis << "Median expulsion time (in minutes):  " << MedianExpulsionTime << '\n';
       myAnalysis << "Median acidic positive time (in minutes):  " << MedianAcidicPositiveTime << '\n';
       myAnalysis << "Total process time to consider (in minutes):  " << TotalProcessTime << '\n';
       myAnalysis << "Phagocytosis rate (in percentage per hour):  " << PhagocytosisRate << '\n';
       myAnalysis << '\n';
      }

      myAnalysis.close();
}


void CalculateDetailedTimeDevelopment(int AmoebaAnzahl, Amoeba *Gruppe, int TimeStep)
{
    int AmoebaEmpty=0;
    int AmoebaAcid=0;
    int AmoebaNonAcid=0;

    //Auswertung der Amoeben
    //Status 0: Anzahl der Amoeben ohne Pilz
    //Status 1: Anzahl der Acidic Amoeben
    //Status 2: Anzahl der NonAcidic Amoeben

    ofstream myAnalysis;
    myAnalysis.open (AnalysisFilename, ios::out | ios::app);


    for (int Index1 = 0 ; Index1 < AmoebaAnzahl ; Index1++)
    {
        if(Gruppe[Index1].AmoebaStatus==0)
            AmoebaEmpty=AmoebaEmpty++;

        if(Gruppe[Index1].AmoebaStatus==1)
            AmoebaAcid=AmoebaAcid++;

        if(Gruppe[Index1].AmoebaStatus==2)
            AmoebaNonAcid=AmoebaNonAcid++;
    }
        if(AmoebaAcid+AmoebaNonAcid>=1 && ShowTimeDevelopment==1)
        {
            float AcidRelation =(float) AmoebaAcid/((float)AmoebaNonAcid+(float)AmoebaAcid);
            if(ResultsToScreenOrFile==1)
            {
              std::cout << "TimeStep:  " << setw(8) << TimeStep << "Acidic amoebas:  " << setw(5) << AmoebaAcid << "  Nonacidic amoebas:  " << setw(5) << AmoebaNonAcid << "  Relation:  " <<   AcidRelation << "\n";
            }
            if(ResultsToScreenOrFile==0)
            {
              myAnalysis << "TimeStep:  " << setw(5) << TimeStep << "  Acidic amoebas:  " << setw(5) << AmoebaAcid << "  Nonacidic amoebas:  " << setw(5) << AmoebaNonAcid << "  Relation:  " <<   AcidRelation << "\n";
            }
        }
        else if(ShowTimeDevelopment==1)
        {
            if(ResultsToScreenOrFile==1)
            {
            std::cout << "Acidic amoebas:  " << AmoebaAcid << "  Nonacidic amoebas:  " << AmoebaNonAcid << "  Relation:  " <<  0 << "\n";
            }
            if(ResultsToScreenOrFile==0)
            {
            myAnalysis << "Acidic amoebas:  " << AmoebaAcid << "  Nonacidic amoebas:  " << AmoebaNonAcid << "  Relation:  " <<  0 << "\n";
            }
        }

    myAnalysis.close();

}


void CalculateResult(int AmoebaAnzahl, Amoeba *Gruppe)
{
    int AmoebaEmpty=0;
    int AmoebaAcid=0;
    int AmoebaNonAcid=0;

    //Auswertung der Amoeben
    //Status 0: Anzahl der Amoeben ohne Pilz
    //Status 1: Anzahl der Acidic Amoeben
    //Status 2: Anzahl der NonAcidic Amoeben

    ofstream myAnalysis;
    myAnalysis.open (AnalysisFilename, ios::out | ios::app);


    for (int Index1 = 0 ; Index1 < AmoebaAnzahl ; Index1++)
    {
        if(Gruppe[Index1].AmoebaStatus==0)
            AmoebaEmpty=AmoebaEmpty++;

        if(Gruppe[Index1].AmoebaStatus==1)
            AmoebaAcid=AmoebaAcid++;

        if(Gruppe[Index1].AmoebaStatus==2)
            AmoebaNonAcid=AmoebaNonAcid++;
    }

    std::cout << "\n";
    std::cout << "Result:  " <<  "\n";
    std::cout << "\n";
    std::cout << "Amoebas without digesting fungi:  " << AmoebaEmpty << "\n";
    std::cout << "Acidic positive amoebas:  " << AmoebaAcid << "\n";
    std::cout << "Acidic negative amoebas:  " << AmoebaNonAcid << "\n";
    std::cout << "\n";
    float AcidRelation =(float) AmoebaAcid/((float)AmoebaNonAcid+(float)AmoebaAcid);
    std::cout << "Relation of acidic amoebas to acidic plus nonacidic amoebas:  " << AmoebaAcid << "/(" << AmoebaNonAcid << " + " << AmoebaAcid << ")" << " = " <<  AcidRelation << "\n";

    if(ResultsToScreenOrFile==0)
    {
    myAnalysis << "\n";
    myAnalysis << "Result:  " <<  "\n";
    myAnalysis << "\n";
    myAnalysis << "Amoebas without digesting fungi:  " << AmoebaEmpty << "\n";
    myAnalysis << "Acidic positive amoebas:  " << AmoebaAcid << "\n";
    myAnalysis << "Acidic negative amoebas:  " << AmoebaNonAcid << "\n";
    myAnalysis << "\n";
    float AcidRelation =(float) AmoebaAcid/((float)AmoebaNonAcid+(float)AmoebaAcid);
    myAnalysis << "Relation of acidic amoebas to acidic plus nonacidic amoebas:  " << AmoebaAcid << "/(" << AmoebaNonAcid << " + " << AmoebaAcid << ")" << " = " <<  AcidRelation << "\n";
    }

    myAnalysis.close();

}


