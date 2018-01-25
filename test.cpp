#define BOOST_TEST_MODULE test_ip_filter
//------------------------------------------------------
#include "lib.h"
#include <fstream>
#include "TestsConfig.h"
//------------------------------------------------------
#include <boost/test/unit_test.hpp>
//------------------------------------------------------
void readInputIps(VecIPAdresses & ips)
{
  std::string fullname = std::string(TESTS_SOURCE_DIR) + "ips.txt";
  std::ifstream is(fullname);
  while(!is.eof())
  {
    std::string line;
    std::getline(is, line);
    if (line.empty()) continue;

    VecString octets(split(line, '.'));
    ips.push_back(std::make_tuple(stoi(octets[0]), stoi(octets[1]), stoi(octets[2]), stoi(octets[3])));
  }
}
//------------------------------------------------------
void readProcessedDataFromFile(const std::string & fileName, std::string & data)
{
  std::ifstream is(fileName.c_str());
  while(!is.eof())
  {
    std::string line;
    std::getline(is, line);
    if (line.empty()) continue;

    data += line;
  }
}
//------------------------------------------------------
void convertIPAddressesToString(VecIPAdresses & in, std::string & out)
{
  for(auto ip = in.cbegin(); ip != in.end(); ++ip)
  {
    out += std::to_string(std::get<0>(*ip));
    out += '.';
    out += std::to_string(std::get<1>(*ip));
    out += '.';
    out += std::to_string(std::get<2>(*ip));
    out += '.';
    out += std::to_string(std::get<3>(*ip));
  }
}
//------------------------------------------------------
bool compareResults(VecIPAdresses & in, const std::string & fileName)
{
 std::string expected;
 readProcessedDataFromFile(fileName, expected);

 std::string str;
 convertIPAddressesToString(in, str);
 return str == expected;
}
//------------------------------------------------------
BOOST_AUTO_TEST_SUITE(test_ip_filter)
//------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_reverse_sorting_ips)
{
  std::string fullname = std::string(TESTS_SOURCE_DIR) + "sorted_ips.txt";
  VecIPAdresses ips;
  readInputIps(ips);
  sort(ips);
  BOOST_CHECK(compareResults(ips, fullname));
}
//------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_filter_first_byte)
{
  std::string fullname = std::string(TESTS_SOURCE_DIR) + "filterFirstByte.txt";
  VecIPAdresses ips;
  readInputIps(ips);
  VecIPAdresses filtered = filter(ips, 1);
  sort(filtered);
  BOOST_CHECK(compareResults(filtered, fullname));
}
//------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_filter_first_second_byte)
{
  std::string fullname = std::string(TESTS_SOURCE_DIR) + "filterFirstSecondBytes.txt";
  VecIPAdresses ips;
  readInputIps(ips);
  VecIPAdresses filtered = filter(ips, 46, 70);
  sort(filtered);
  BOOST_CHECK(compareResults(filtered, fullname));
}
//------------------------------------------------------
BOOST_AUTO_TEST_CASE(test_filter_any_byte)
{
  std::string fullname = std::string(TESTS_SOURCE_DIR) + "filterAnyByte.txt";
  VecIPAdresses ips;
  readInputIps(ips);
  VecIPAdresses filtered = filter_any(ips, 46);
  sort(filtered);
  BOOST_CHECK(compareResults(filtered, fullname));
}
//------------------------------------------------------
BOOST_AUTO_TEST_SUITE_END()
//------------------------------------------------------
