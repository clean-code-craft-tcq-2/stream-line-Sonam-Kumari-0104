#pragma once

struct bms_temp
{
	float value;
	float min;
	float max;
};

struct bms_soc
{
	float value;
	float min;
	float max;
};

struct bms_chargeRate
{
	float value;
	float min;
	float max;
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
