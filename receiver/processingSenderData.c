#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "receiver.h"

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

