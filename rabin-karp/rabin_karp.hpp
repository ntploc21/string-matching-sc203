#ifndef __RABIN_KARP_HPP__
#define __RABIN_KARP_HPP__

#include<bits/stdc++.h>

namespace rabin_karp {
    std::vector<int> rabin_karp(std::string const& s, std::string const& t);
}; // namespace rabin_karp

#endif // __RABIN_KARP_HPP__

/*
 * References for Rabin-Karp algorithm:
 * https://www.giaithuatlaptrinh.com/?p=290
 * https://cp-algorithms.com/string/rabin-karp.html#implementation
 * Reference for Miller-Rabin algorithm:
 * https://vnoi.info/wiki/algo/algebra/primality_check.md#3-thu%E1%BA%ADt-to%C3%A1n-rabin-miller
*/
