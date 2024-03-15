#pragma once

#include <type_traits>

template<typename T>
struct make_unsigned_better {
    using type = std::make_unsigned_t<T>;
};

#ifdef __SIZEOF_INT128__
template<>
struct make_unsigned_better<__int128_t> {
    using type = __uint128_t;
};

template<>
struct make_unsigned_better<__uint128_t> {
    using type = __uint128_t;
};
#endif

template<typename T> using make_unsigned_better_t = typename make_unsigned_better<T>::type;