#include <stdio.h>
#include <stdlib.h>
#include "processingSenderData.h"
#define NO_OF_DATASETS 5

int main ()
{
    char Data1[] = "Temperature:2.00 deg C, State of Charge:5.00, Charge Rate:0.40\n"; 
    char Data2[] = "Temperature:5.00 deg C, State of Charge:4.00, Charge Rate:0.10\n";
    char Data3[] = "Temperature:8.00 deg C, State of Charge:10.00, Charge Rate:0.20\n";
	char Data4[] = "Temperature:7.00 deg C, State of Charge:6.00, Charge Rate:0.30\n";
	char Data5[] = "Temperature:4.00 deg C, State of Charge:7.00, Charge Rate:0.50\n";
    char *senderData[NO_OF_DATASETS] = {Data1, Data2, Data3, Data4, Data5};
	struct BMS bms_input = {0.0};
	
	for (int dataSetIndex = 0; dataSetIndex < NO_OF_DATASETS; dataSetIndex++ )
	{
		parseSenderData (senderData[dataSetIndex], &bms_input);
		findMinMaxOfBMSParams(&bms_input);
		findMovAvgOfBMSParams(&bms_input);
	}
	printf ("Minimum values are\n%f %f %f\n",bms_input.temperature.temp_stat.min, bms_input.soc.soc_stat.min, bms_input.chargeRate.CR_stat.min);
	printf ("Maximum values are\n%f %f %f\n",bms_input.temperature.temp_stat.max, bms_input.soc.soc_stat.max, bms_input.chargeRate.CR_stat.max);
	printf ("Mov Average %f %f %f\n", bms_input.temperature.temp_stat.movAvg, bms_input.soc.soc_stat.movAvg, bms_input.chargeRate.CR_stat.movAvg);

	return 0;
	
}