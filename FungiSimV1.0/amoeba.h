class Amoeba
{
public:
   int AcidTime;
   int NonAcidTime;
   int AmoebaStatus;
   Amoeba(void);			//Konstruktor
   void SetInitialAcidTime(int SetAcidTime, int SetNonAcidTime, int SetAmoebaStatus);
   void SetUpdateAcidTime(int TimeStep);
};


