#include <stdio.h>
#include "sender.h"

void ReadBMSParametersFromFile(float* Temp, float* SOC)
{
    float Temperature, StateOfCharge;
    FILE * file= fopen("./sender/BMSData.txt","r");  
    if (file!=NULL) 
    {
        for(int i=0;fscanf(file, "%f\t%f\t%f\n", &Temperature,&StateOfCharge)!=EOF ;i++)
        {
            *(Temp+i) = Temperature;
            *(SOC+i)  = StateOfCharge;
        }
    }
    fclose(file);  
}

void printBMSParamsOnConsole(float* Temp, float* SOC)
{
  char bmsParam[50];
  for (int i=0; i<NOOFSAMPLES; i++)
  {
    sprintf(bmsParam[50], "Temperature: %f, SOC: %f", *(Temp+i),*(SOC+i));
  }
}

void sendBMSParameters(){
  float Temperature[NOOFSAMPLES] = {0};
  float StateOfCharge[NOOFSAMPLES]= {0};
  ReadBMSParametersFromFile(Temperature, StateOfCharge);
  printBMSParamsOnConsole(Temperature, StateOfCharge);
}
