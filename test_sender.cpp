#define CATCH_CONFIG_MAIN 

#include "test/catch.hpp"
#include "sender/sender.h"

TEST_CASE("Check whether reading and passing the data is successful") 
{
  float Temperature[NOOFSAMPLES] = {0};
  float StateOfCharge[NOOFSAMPLES] = {0};
  float ChargeRate[NOOFSAMPLES] = {0};
  float expectedoutput[4][4] = {{2,5,0.0}, {5,5,0.0}, {5,5,0.0}, {15,10,0.2};
  
  ReadBMSParametersFromFile(Temperature,StateOfCharge,ChargeRate);
  int j= 0, i= 0;
  for(i=0;i<4;i++)
  {
    REQUIRE(Temperature[j] == expectedoutput[i][0]);
    REQUIRE(StateOfCharge[j] == expectedoutput[i][1]);
    REQUIRE(ChargeRate[j] == expectedoutput[i][2]);
    j++;
  }
 sendBMSParameters();
}
