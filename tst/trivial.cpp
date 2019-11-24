#define BOOST_TEST_MODULE trivial_module

#include "ip_filter.hpp"

#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <range/v3/algorithm/equal.hpp>

BOOST_AUTO_TEST_SUITE(trivial)

BOOST_AUTO_TEST_CASE(trivial_data) try {
  std::ifstream data_stream{"trivial_data_input.txt"};

  if (!data_stream)
    throw std::ios_base::failure{"Cannot open file for reading"};

  std::stringstream filter_data_stream;

  ip_filter::filter_pipe(
      data_stream,
      filter_data_stream,
      [](ip_filter::ip const &)  {return true;},
      [](ip_filter::ip const &ip){return ip[0] == 1;},
      [](ip_filter::ip const &ip){return ip[0] == 46 && ip[1] == 70;},
      [](ip_filter::ip const &ip){return std::any_of(std::begin(ip),
                                                     std::end(ip),
                                                     [](ip_filter::octet_t v){return v == 46;});}
  );

  std::ifstream expect_stream{"trivial_data_expectation.txt"};
  if (!expect_stream)
    throw std::ios_base::failure{"Cannot open file for reading"};

  BOOST_CHECK(
      ranges::equal(
        std::istream_iterator<std::string>(expect_stream),
        std::istream_iterator<std::string>(),
        std::istream_iterator<std::string>(filter_data_stream),
        std::istream_iterator<std::string>()
      )
  );
} catch(std::exception const &e) {
  BOOST_FAIL(e.what());
} catch(...) {
  BOOST_FAIL("Unknown exception");
}

BOOST_AUTO_TEST_SUITE_END()
