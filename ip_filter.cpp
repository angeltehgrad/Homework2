#include <cassert>
#include <cstdlib>
#include "lib.h"
//------------------------------------------------------
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
//------------------------------------------------------
void sortAndPrint(VecIPAdresses & ips)
{
  sort(ips);
  printIPs(ips);
}
//------------------------------------------------------
int main(int argc, char const *argv[])
{
    try
    {
        VecIPAdresses ip_pool;

        readIPs(ip_pool);
        sortAndPrint(ip_pool);

        VecIPAdresses filtered = filter(ip_pool,1);
        sortAndPrint(filtered);

        filtered = filter(ip_pool, 46, 70);
        sortAndPrint(filtered);

        filtered = filter_any(ip_pool, 46);
        sortAndPrint(filtered);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
//------------------------------------------------------
