#define CATCH_CONFIG_MAIN 

#include "test/catch.hpp"
#include "receiver/processingSenderData.h"

TEST_CASE("Receive the data stream from sender and validate parsed value of each parameters") 
{
  char Data1[] = "Temperature:2.00 deg C, State of Charge:5.00, Charge Rate:0.40\n"; 
  char Data2[] = "Temperature:5.00 deg C, State of Charge:4.00, Charge Rate:0.10\n";
  char Data3[] = "Temperature:15.00 deg C, State of Charge:10.00, Charge Rate:0.20\n";
  char *senderData[3] = {Data1, Data2, Data3};
  struct BMS bms_input;
  int sender_index;
  float expectedTemp[3] = {2.0, 5.0, 15.0};
  float expectedSOC[3] = {5.0, 4.0, 10.0};
  float expectedCR[3] = {0.40, 0.10, 0.20};
   
  for(sender_index=0; sender_index < 3; sender_index++)
  {
	parseSenderData (senderData[sender_index], &bms_input);
    REQUIRE(bms_input.temperature.value == expectedTemp[sender_index]);
    REQUIRE(bms_input.soc.value == expectedSOC[sender_index]);
    REQUIRE(bms_input.chargeRate.value == expectedCR[sender_index]);
  }
}

TEST_CASE("Find Minimum and Maximum value from parsed value of each parameters") 
{
  struct BMS bms_input;
  int sender_index;
  float actualTemp[3] = {12.0, 5.0, 15.0};
  float actualSOC[3] = {5.0, 6.0, 2.0};
  float actualCR[3] = {0.10, 0.40, 0.20};
  float expectedTempMin = 5.0;
  float expectedSOCMin = 2.0;
  float expectedCRMin = 0.10;
  float expectedTempMax = 15.0;
  float expectedSOCMax = 6.0;
  float expectedCRMax = 0.40;
  for(sender_index=0; sender_index < 3; sender_index++)
  {
	bms_input.temperature.value = actualTemp[sender_index];
	bms_input.soc.value = actualSOC[sender_index];
	bms_input.chargeRate.value = actualCR[sender_index];
	findMinMaxOfBMSParams(&bms_input);
  }
  REQUIRE(bms_input.temperature.temp_stat.min == expectedTempMin);
  REQUIRE(bms_input.soc.soc_stat.min == expectedSOCMin);
  REQUIRE(bms_input.chargeRate.CR_stat.min == expectedCRMin);
  REQUIRE(bms_input.temperature.temp_stat.max == expectedTempMax);
  REQUIRE(bms_input.soc.soc_stat.max == expectedSOCMax);
  REQUIRE(bms_input.chargeRate.CR_stat.max == expectedCRMax);
}

TEST_CASE("Find Simple Moving Average from parsed value of each parameters") 
{
  float actualTemp[] = {12.0, 5.0, 15.0, 3.0, 4.0, 7.0, 1.0, 8.0, 11.0, 10.0};
  float actualSOC[] = {5.0, 6.0, 2.0, 3.0, 1.0, 4.0, 2.0, 4.0, 8.0, 6.0};
  float actualCR[] = {0.10, 0.40, 0.20, 0.30, 0.20, 0.1, 0.4, 0.5, 0.6, 0.9};
  static struct BMS bms_input = {0.0};
  float expectedTempMav = 7.4;
  float expectedSOCMav = 4.8;
  float expectedCRMav = 0.5;

  int total_index = sizeof(actualTemp)/sizeof(actualTemp[0]);
  for(int sender_index=0; sender_index < total_index; sender_index++)
  {
	bms_input.temperature.value = actualTemp[sender_index];
	bms_input.soc.value = actualSOC[sender_index];
	bms_input.chargeRate.value = actualCR[sender_index];
	findMovAvgOfBMSParams(&bms_input);
  }
  REQUIRE(bms_input.temperature.temp_stat.min == expectedTempMav);
  REQUIRE(bms_input.soc.soc_stat.min == expectedSOCMav);
  REQUIRE(bms_input.chargeRate.CR_stat.min == expectedCRMav);
}