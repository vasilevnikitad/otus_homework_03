#include "ip_filter.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <ostream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int, char const *[]) try
{
  ip_filter::filter_pipe(std::cin, std::cout,
      [](ip_filter::ip const &) constexpr {return true;},
      [](ip_filter::ip const &ip){return ip[0] == 1;},
      [](ip_filter::ip const &ip){return ip[0] == 46 && ip[1] == 70;},
      [](ip_filter::ip const &ip){return std::any_of(std::begin(ip),
                                                     std::end(ip),
                                                     [](ip_filter::octet_t v){return v == 46;});}
  );

  return EXIT_SUCCESS;
} catch(std::exception const &e) {
    std::cerr << "Exception: "<< e.what() << std::endl;
    return EXIT_FAILURE;
} catch(...) {
    std::cerr << "Unknown Failure" << std::endl;
    return EXIT_FAILURE;
}
