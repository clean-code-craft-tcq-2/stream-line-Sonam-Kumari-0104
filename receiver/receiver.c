#include <stdio.h>
#include <stdlib.h>
#include "receiver.h"


int main ()
{
    char Data1[] = "Temperature:2.00 deg C, State of Charge:5.00, Charge Rate:0.40\n"; 
    char Data2[] = "Temperature:5.00 deg C, State of Charge:4.00, Charge Rate:0.10\n";
    char Data3[] = "Temperature:15.00 deg C, State of Charge:10.00, Charge Rate:0.20\n";
    char *senderData[3] = {Data1, Data2, Data3};
	struct BMS bms_input;
	
	parseSenderData (senderData[0], &bms_input);
	parseSenderData (senderData[1], &bms_input);
	parseSenderData (senderData[2], &bms_input);
	printf ("converted........\n%f %f %f\n",bms_input.temperature.value, bms_input.soc.value, bms_input.chargeRate.value); 

	return 0;
	
}