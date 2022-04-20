#define CATCH_CONFIG_MAIN 

#include "test/catch.hpp"
#include "receiver/receiver.h"

TEST_CASE("Receive the data stream from sender and validate value of each parameters") 
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
    REQUIRE(bms_input.temperature.value[sender_index] == expectedTemp[sender_index]);
    REQUIRE(bms_input.soc.value[sender_index] == expectedSOC[sender_index]);
    REQUIRE(bms_input.chargeRate.value[sender_index] == expectedCR[sender_index]);
  }
}
