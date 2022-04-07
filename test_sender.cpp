#define CATCH_CONFIG_MAIN 

#include "test/catch.hpp"
#include "sender/sender.h"

TEST_CASE("Check whether reading and passing the data is successful") 
{
  float Temperature[NOOFSAMPLES] = {0};
  float StateOfCharge[NOOFSAMPLES] = {0};
  float ChargeRate[NOOFSAMPLES] = {0};
  float expectedoutput[3][3] = {{2,5,0.0}, {45,55,0.65},{-3,45,0.36}};
  
  ReadBMSParametersFromFile(Temperature,StateOfCharge,ChargeRate);
  int j= 0, i= 0;
  for(i=0;i<3;i++)
  {
    REQUIRE(Temperature[j] == expectedoutput[i][0]);
    REQUIRE(StateOfCharge[j] == expectedoutput[i][1]);
    REQUIRE(ChargeRate[j] == expectedoutput[i][2]);
    j=j+20;
  }
 sendBMSParameters();
}
