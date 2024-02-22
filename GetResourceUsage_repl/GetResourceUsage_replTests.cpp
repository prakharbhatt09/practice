#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "GetResourceUsage_repl.hpp"
#include "SoC.hpp"
#include "TunerPath.hpp"
#include "NBT.hpp"
#include "DFE.hpp"
#include "Receiver.hpp"

using namespace std;

TEST_CASE("encoding a message with zero SoCs")
{
  GetResourceUsage_repl message1(1,1,0,0,0);
  vector<uint8_t> encoded_msg = message1.encode();
  CHECK(encoded_msg.at(0) == 1);
  CHECK(encoded_msg.at(1) == 0x02);
  CHECK(encoded_msg.at(2) == 0x03);
  CHECK(encoded_msg.at(3) == 1);
  CHECK(encoded_msg.at(4) == 0);
}
TEST_CASE("encoding a message with 1 SoCs")
{
  GetResourceUsage_repl message1(1,1,0,1,0);
  SoC soc1(0,1,1,0,0);
  vector<uint8_t> encoded_msg = message1.encode();

  CHECK(encoded_msg.at(0) == 1);

}