#ifndef __IP_FILTER_HPP__
#define __IP_FILTER_HPP__
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

namespace ip_filter {
  using octet_t = std::uint8_t;
  enum : octet_t { IPV4_OCTET_CNT = 4 };
  using ip_base = std::array<octet_t, IPV4_OCTET_CNT>;

  class ip : public ip_base {
    private:

      static inline ip_base str2ip_base(const std::string &ip_str)
      {
        int pos{0};
        std::array<unsigned, IPV4_OCTET_CNT> val_be{{0, 0, 0, 0}};
        if (std::sscanf(ip_str.c_str(), "%u.%u.%u.%u%n",
              &val_be[0], &val_be[1], &val_be[2], &val_be[3], &pos) != 4 ||
            (unsigned)pos != ip_str.length() ||
            std::any_of(std::begin(val_be),
              std::end(val_be),
              [](unsigned const val){return val > std::numeric_limits<octet_t>::max();})) {
          throw std::invalid_argument{"string \"" + ip_str + "\" doesn't contain valid ipv4 address"};
        }
        return {
          static_cast<octet_t>(val_be[0]),
          static_cast<octet_t>(val_be[1]),
          static_cast<octet_t>(val_be[2]),
          static_cast<octet_t>(val_be[3])
        };
      }

    public:
      template<typename... Args,
        typename = std::enable_if_t<std::conjunction_v<std::is_integral<Args>...> &&
          sizeof...(Args) <= IPV4_OCTET_CNT> >
      constexpr ip(Args&&... args) : ip_base{std::forward<octet_t>(args)...} { }

      ip(const std::string &ip_str) : ip_base{str2ip_base(ip_str)} { }
  };

  template<std::size_t N = 0>
  inline std::ostream &operator <<(std::ostream &o, ip const &ip) {
    o << +ip[N];
    if constexpr (N != IPV4_OCTET_CNT - 1)
      return operator<< <N + 1>(o << '.', ip);
    return o;
  }

  template <typename InputIt, typename OutputIt, typename ...Args,
    typename = std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool, Args, ip const &>...>>>
  inline void apply_filters(InputIt begin, InputIt end, OutputIt out, Args&&... args)
  {
    (std::copy_if(begin, end, out, std::forward<Args>(args)), ...);
  }

  template <typename IS, typename OS, typename ...Filters,
    typename = std::enable_if_t<std::conjunction_v<std::is_invocable_r<bool, Filters, ip const &>...>>>
  inline void filter_pipe(IS &&is, OS &&os, Filters&&... filters)
  {
    std::vector<ip> ip_pool;

    try {
      for(std::string line; std::getline(std::forward<IS>(is), line); )
        ip_pool.emplace_back(line.substr(0, line.find('\t')));
    } catch(std::ios_base::failure const &) {
        /* getline doesn't tell what has triggered an exception:
         * no chars or the stream has been corrupted you will not guess
         */
    }

    std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<ip>());

    apply_filters(std::begin(ip_pool), std::end(ip_pool),
                  std::ostream_iterator<ip>(std::forward<OS>(os), "\n"),
                  std::forward<Filters>(filters)...);
  }
}

#endif
