// <Bits.hpp> -*- C++ -*-
#pragma once

#include <cinttypes>
#include <cassert>
#include <typeinfo>

#include "sparta/utils/SpartaException.hpp"

/**
 * \file Bits.hpp
 * \brief Helper functions to count bits.  A little old -- consider using compiler intrinsics
 */

namespace sparta {
    namespace utils {

        template <class T>
        inline uint32_t count_1_bits(const T&)
        {
            throw SpartaException("Unsupported type for count_1_bits: ") << typeid(T).name();
        }

        // Courtesy: Warren, Henry S. (2012-09-25). Hacker's Delight
        // (2nd Edition)
        template<>
        inline uint32_t count_1_bits<uint32_t>(const uint32_t& n)
        {
            uint32_t x = n - (( n >> 1) & 0x55555555);
            x = (x & 0x33333333) + (( x >> 2) & 0x33333333);
            x = (x + (x >> 4)) & 0x0F0F0F0F;
            x = x + (x >> 8);
            x = x + (x >> 16);
            return x & 0x3F;
        }

        template<>
        inline uint32_t count_1_bits<uint64_t>(const uint64_t& n)
        {
            uint64_t x = n - (( n >> 1) & 0x5555555555555555ull);
            x = (x & 0x3333333333333333ull) + (( x >> 2) & 0x3333333333333333ull);
            x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0Full;
            x = x + (x >> 8);
            x = x + (x >> 16);
            x = x + (x >> 32);
            return x & 0x7F;
        }

    } // namespace sparta::utils
} // namespace sparta
