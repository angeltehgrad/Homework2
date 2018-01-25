#pragma once
//------------------------------------------------------
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
//------------------------------------------------------
typedef std::vector<std::string> VecString;
typedef std::tuple<int, int, int, int> IPAddress;
typedef std::vector<IPAddress> VecIPAdresses;
//------------------------------------------------------
void readIPs(VecIPAdresses & ips);

void printIPs(const VecIPAdresses & ips);

void sort(VecIPAdresses & ips);

VecIPAdresses filter(const VecIPAdresses & in,
            const int firstByte);

VecIPAdresses filter(const VecIPAdresses &in,
            const int firstByte, const int secondByte);

VecIPAdresses filter_any(const VecIPAdresses & in,
            const int searchedByte);

VecString split(const std::string & str, char d);
//------------------------------------------------------
