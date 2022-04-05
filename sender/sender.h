#define NOOFSAMPLES 50;

typedef struct{
float tempearture[NOOFSAMPLES];
float SOC[NOOFSAMPLES];
}batteryParameters;

void ReadBMSParametersFromFile(float* Temp, float* SOC);
void printBMSParamsOnConsole(float* Temp, float* SOC);
void sendBMSParameters();
