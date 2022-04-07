#define CATCH_CONFIG_MAIN 

#include "test/catch.hpp"
#include <sender.h>

TEST_CASE("Check whether reading and passing the data is successful") 
{
  float Temperature[NO_OF_SAMPLES] = {0};
  float StateOfCharge[NO_OF_SAMPLES] = {0};
  float expectedoutput[3][3] = {{22,75}, {55,59},{89, -5}};
  
  ReadBMS_DataFromFile( Temperature,StateOfCharge,ChargeRate);
  int j= 0, i= 0;
  for(i=0;i<3;i++)
  {
    REQUIRE(Temperature[j] == expectedoutput[i][0]);
    REQUIRE(StateOfCharge[j] == expectedoutput[i][1]);
    j=j+24;
  }
 sendBMSParameters();
}