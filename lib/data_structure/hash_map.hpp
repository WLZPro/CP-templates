#pragma once

#include <cstdint>
#include <chrono>
#include <unordered_map>
#include <ext/pb_ds/assoc_container.hpp>

// https://codeforces.com/blog/entry/62393
struct my_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    std::size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename Key, typename Val>
using safe_unordered_map = std::unordered_map<Key, Val, my_hash>;
template<typename Key, typename Val>
using safe_gp_hash_table = __gnu_pbds::gp_hash_table<Key, Val, my_hash>;