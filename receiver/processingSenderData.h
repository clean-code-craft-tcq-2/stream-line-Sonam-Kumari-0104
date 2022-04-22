#pragma once

#define MOV_AVG_TOTAL 5
struct stats
{
	float min;
	float max;
	float movAvg;
	float sum;
	float movAvgArray[MOV_AVG_TOTAL];
};

struct bms_temp
{
	float value;
	struct stats temp_stat;
};

struct bms_soc
{
	float value;
	struct stats soc_stat;
};

struct bms_chargeRate
{
	float value;
	struct stats CR_stat;
};

struct BMS
{
	struct bms_temp temperature ;
	struct bms_soc soc;
	struct bms_chargeRate chargeRate;
};

float parseParamValueFromString (char *input);
void parseSenderData (char *senderData, struct BMS *bms_param);
void findMinMaxOfBMSParams(struct BMS *bms_input);
void findMovAvgOfBMSParams (struct BMS *bms_input);
float computeMovAvg (float *sum, float *movAvgArray, float value);
