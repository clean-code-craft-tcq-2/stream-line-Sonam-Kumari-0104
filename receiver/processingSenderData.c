#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receiver.h"

#define FIRST_DATA_SET 1

float parseParamValueFromString (char *input)
{
	int dest_index = 0;
	char parsed_value [10];
	
	while((input [dest_index] >= '0' && input [dest_index] <= '9') || input [dest_index] == '.')
	{
		parsed_value [dest_index] = input [dest_index];
		dest_index++;
	}
	parsed_value[dest_index] = '\0';
	
	return atof(parsed_value);
}

void parseSenderData (char *senderData, struct BMS *bms_param)
{
	const char* delim = ":";
	char *parameterName = NULL;
	int dest_index = 0;
	
	parameterName = strtok (senderData, delim);
	
	dest_index = strlen (parameterName) + strlen (delim);
	bms_param->temperature.value = parseParamValueFromString(&parameterName[dest_index]);
	parameterName = strtok (NULL, delim);
	dest_index = strlen (parameterName) + strlen (delim);
	bms_param->soc.value = parseParamValueFromString(&parameterName[dest_index]);
	parameterName = strtok (NULL, delim);
	dest_index = strlen (parameterName) + strlen (delim);
	bms_param->chargeRate.value = parseParamValueFromString(&parameterName[dest_index]);
		
	return;
}

void findMinimumOfBMSParams(struct BMS *bms_input)
{
	static int count = FIRST_DATA_SET;
	
	if (count == FIRST_DATA_SET)
	{
		count++;
		bms_input->temperature.min = bms_input->temperature.value;
		bms_input->soc.min 		   = bms_input->soc.value;
		bms_input->chargeRate.min  = bms_input->chargeRate.value;
		return;
	}
	
	if (bms_input->temperature.min > bms_input->temperature.value)
	{
		bms_input->temperature.min = bms_input->temperature.value;
	}
	if (bms_input->soc.min > bms_input->soc.value)
	{
		bms_input->soc.min = bms_input->soc.value;
	}
	if (bms_input->chargeRate.min > bms_input->chargeRate.value)
	{
		bms_input->chargeRate.min = bms_input->chargeRate.value;
	}
	return;
}