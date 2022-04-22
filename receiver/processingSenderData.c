#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processingSenderData.h"

#define FIRST_DATA_SET 1
bool isNumerical (char input)
{
	return (input >= '0' && input <= '9') ? 1 : 0;
}

bool isDotOrMinus (char input)
{
	return (input == '.' || input == '-') ? 1 : 0;
}
float parseParamValueFromString (char *input)
{
	int data_index = 0;
	char parsed_value [10];
	
	while(isNumerical(input [data_index]) || isDotOrMinus(input [data_index]))
	{
		parsed_value [data_index] = input [data_index];
		data_index++;
	}
	parsed_value[data_index] = '\0';
	
	return atof(parsed_value);
}

void parseSenderData (char *senderData, struct BMS *bms_param)
{
	const char* delim = ":";
	char *parameterName = NULL;
	int data_index = 0;
	
	parameterName = strtok (senderData, delim);
	
	data_index = strlen (parameterName) + strlen (delim);
	bms_param->temperature.value = parseParamValueFromString(&parameterName[data_index]);
	parameterName = strtok (NULL, delim);
	data_index = strlen (parameterName) + strlen (delim);
	bms_param->soc.value = parseParamValueFromString(&parameterName[data_index]);
	parameterName = strtok (NULL, delim);
	data_index = strlen (parameterName) + strlen (delim);
	bms_param->chargeRate.value = parseParamValueFromString(&parameterName[data_index]);
		
	return;
}

void computeMinMax (float *min, float *max, float *value)
{
	if (*min > *value)
		*min = *value;
	if (*max < *value)
		*max = *value;
}
void setThresholdIfFirstData (int *dataSetCount, struct BMS *bms_input)
{
	if (*dataSetCount == FIRST_DATA_SET)
	{
		*dataSetCount = *dataSetCount + 1;
		bms_input->temperature.temp_stat.min = bms_input->temperature.value;
		bms_input->soc.soc_stat.min 		 = bms_input->soc.value;
		bms_input->chargeRate.CR_stat.min  	 = bms_input->chargeRate.value;
		bms_input->temperature.temp_stat.max = bms_input->temperature.value;
		bms_input->soc.soc_stat.max 		 = bms_input->soc.value;
		bms_input->chargeRate.CR_stat.max  	 = bms_input->chargeRate.value;
		return;
	}
}

void findMinMaxOfBMSParams(struct BMS *bms_input)
{
	static int count = FIRST_DATA_SET;
		
	setThresholdIfFirstData(&count, bms_input);
	
	computeMinMax(&bms_input->temperature.temp_stat.min, &bms_input->temperature.temp_stat.max, &bms_input->temperature.value);
	computeMinMax(&bms_input->soc.soc_stat.min, &bms_input->soc.soc_stat.max, &bms_input->soc.value);
	computeMinMax(&bms_input->chargeRate.CR_stat.min, &bms_input->chargeRate.CR_stat.max, &bms_input->chargeRate.value);
	
	return;
}

float computeMovAvg (float *sum, float *movAvgArray, float value)
{
	float result = 0.0;
	*sum = (*sum) - (*movAvgArray) + value;
	*movAvgArray = value;
	result = (*sum / MOV_AVG_TOTAL);
	return result;
	
}

void findMovAvgOfBMSParams (struct BMS *bms_input)
{
	static int pos = 0;
	
	bms_input->temperature.temp_stat.movAvg = computeMovAvg(&bms_input->temperature.temp_stat.sum, &bms_input->temperature.temp_stat.movAvgArray[pos], 
															bms_input->temperature.value);
	bms_input->soc.soc_stat.movAvg = computeMovAvg(&bms_input->soc.soc_stat.sum, &bms_input->soc.soc_stat.movAvgArray[pos], bms_input->soc.value);
	bms_input->chargeRate.CR_stat.movAvg = computeMovAvg(&bms_input->chargeRate.CR_stat.sum, &bms_input->chargeRate.CR_stat.movAvgArray[pos], 
														   bms_input->chargeRate.value);
	pos++;
	if (pos == MOV_AVG_TOTAL)
		pos = 0;
}