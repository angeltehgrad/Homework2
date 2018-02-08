#include "lib.h"
#include <algorithm>
//------------------------------------------------------
void readIPs(VecIPAdresses & ips)
{
  for(std::string line; std::getline(std::cin, line);)
  {
    VecString v = split(line, '\t');
    VecString octets(split(v.at(0), '.'));
    ips.push_back(std::make_tuple(stoi(octets[0]), stoi(octets[1]), stoi(octets[2]), stoi(octets[3])));
  }
}
//------------------------------------------------------
void printIPs(const VecIPAdresses & ips)
{
  for(auto ip = ips.cbegin(); ip != ips.cend(); ++ip)
  {
      int b1,b2,b3,b4;
      std::tie(b1,b2,b3,b4) = *ip;
      std::cout << b1 << "." << b2 << "." << b3 << "." << b4;
      std::cout << std::endl;
  }
}
//------------------------------------------------------
void sort(VecIPAdresses & ips)
{
  auto f = [] (IPAddress & l, IPAddress & r)
  {
    return l > r;
  };
  std::sort(ips.begin(), ips.end(), f);
}
//------------------------------------------------------
VecIPAdresses filter(const VecIPAdresses & in,
            const int firstByte)
{
  VecIPAdresses out;
  auto f = [firstByte](auto & ip)
  {
    return firstByte == std::get<0>(ip);
  };
  std::copy_if(in.begin(), in.end(), std::back_inserter(out), f);
  return out;
}
//------------------------------------------------------
VecIPAdresses filter(const VecIPAdresses & in,
            const int firstByte, const int secondByte)
{
  VecIPAdresses out;
  auto f = [firstByte,secondByte](auto & ip)
  {
    return firstByte == std::get<0>(ip) && secondByte == std::get<1>(ip);
  };
  std::copy_if(in.begin(), in.end(), std::back_inserter(out), f);
  return out;
}
//------------------------------------------------------
VecIPAdresses filter_any(const VecIPAdresses &in,
            const int searchedByte)
{
  VecIPAdresses out;
  auto f = [searchedByte](auto & ip)
  {
    return (std::get<0>(ip) == searchedByte ||
            std::get<1>(ip) == searchedByte ||
            std::get<2>(ip) == searchedByte ||
            std::get<3>(ip) == searchedByte);
  };
  std::copy_if(in.begin(), in.end(), std::back_inserter(out), f);
  return out;
}
//------------------------------------------------------
VecString split(const std::string & str, char d)
{
    VecString r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));
    return r;
}
//------------------------------------------------------
