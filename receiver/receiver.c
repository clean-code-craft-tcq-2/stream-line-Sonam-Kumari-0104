#include <stdio.h>
#include <stdlib.h>
#include "receiver.h"
#define NO_OF_DATASETS 3

int main ()
{
    char Data1[] = "Temperature:2.00 deg C, State of Charge:5.00, Charge Rate:0.40\n"; 
    char Data2[] = "Temperature:5.00 deg C, State of Charge:4.00, Charge Rate:0.10\n";
    char Data3[] = "Temperature:15.00 deg C, State of Charge:10.00, Charge Rate:0.20\n";
    char *senderData[NO_OF_DATASETS] = {Data1, Data2, Data3};
	struct BMS bms_input;
	
	for (int dataSetIndex = 0; dataSetIndex < NO_OF_DATASETS; dataSetIndex++ )
	{
		parseSenderData (senderData[dataSetIndex], &bms_input);
		findMinMaxOfBMSParams(&bms_input);
	}
	printf ("Minimum values are\n%f %f %f\n",bms_input.temperature.min, bms_input.soc.min, bms_input.chargeRate.min);
	printf ("Maximum values are\n%f %f %f\n",bms_input.temperature.max, bms_input.soc.max, bms_input.chargeRate.max);

	return 0;
	
}