typedef struct{
float tempearture[50];
float SOC[50];
}batteryParameters;

void ReadBMSParametersFromFile(float* Temp, float* SOC);
void printBMSParamsOnConsole(float* Temp, float* SOC);
void sendBMSParameters();
