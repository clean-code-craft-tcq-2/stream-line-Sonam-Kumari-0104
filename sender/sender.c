#include <stdio.h>
#include "sender.h"

void ReadBMSParametersFromFile(float* Temp, float* SOC, float* CR)
{
    float Temperature, StateOfCharge, ChargeRate;
    FILE * file= fopen("./sender/BMSData.txt","r");  
    if (file!=NULL) 
    {
        for(int i=0;fscanf(file, "%f\t%f\t%f\n", &Temperature,&StateOfCharge,&ChargeRate)!=EOF ;i++)
        {
            *(Temp+i) = Temperature;
            *(SOC+i)  = StateOfCharge;
            *(CR+i)   = ChargeRate;
        }
    }
    fclose(file);  
}

void printBMSParamsOnConsole(float* Temp, float* SOC, float* CR)
{
   
  for (int i=0; i<NOOFSAMPLES; i++)
  {
    printf(" Temperature:%.2f deg C, State of Charge:%.2f, Charge Rate:%.2f\n",  *(Temp+i),*(SOC+i),*(CR+i));
  }
}

void sendBMSParameters(){
  float Temperature[NOOFSAMPLES] = {0};
  float StateOfCharge[NOOFSAMPLES]= {0};
  float ChargeRate[NOOFSAMPLES] = {0};
  ReadBMSParametersFromFile(Temperature, StateOfCharge, ChargeRate);
  printBMSParamsOnConsole(Temperature, StateOfCharge, ChargeRate);
}
