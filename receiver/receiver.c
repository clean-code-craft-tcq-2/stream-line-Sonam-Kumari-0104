#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processingSenderData.h"
#define NO_OF_DATASETS 50
#define MAX_SIZE 128

int main ()
{
	struct BMS bms_input = {.temperature = {0.0, .temp_stat = {0.0, 0.0, 0.0, 0.0, 0.0}}, 
							.soc = {0.0, .soc_stat = {0.0, 0.0, 0.0, 0.0, 0.0}}, 
							.chargeRate = {0.0, .CR_stat = {0.0, 0.0, 0.0, 0.0, 0.0}}};
	char senderData[MAX_SIZE] = {'\0'};
	for (int dataSetIndex = 0; dataSetIndex < NO_OF_DATASETS; dataSetIndex++ )
	{
		fgets(senderData, MAX_SIZE, stdin);
		parseSenderData (senderData, &bms_input);
		findMinMaxOfBMSParams(&bms_input);
		findMovAvgOfBMSParams(&bms_input);
		memset(senderData, '\0', MAX_SIZE);
	}
	printf ("Minimum values are\n----------------\n%f %f %f\n",bms_input.temperature.temp_stat.min, bms_input.soc.soc_stat.min, bms_input.chargeRate.CR_stat.min);
	printf ("Maximum values are\n----------------\n%f %f %f\n",bms_input.temperature.temp_stat.max, bms_input.soc.soc_stat.max, bms_input.chargeRate.CR_stat.max);
	printf ("Mov Average\n----------------\n%f %f %f\n", bms_input.temperature.temp_stat.movAvg, bms_input.soc.soc_stat.movAvg, bms_input.chargeRate.CR_stat.movAvg);

	return 0;	
}
