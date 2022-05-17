//
// Created by Viktoria on 14.05.2022.
//

#ifndef TVPIS_UTILS_HPP
#define TVPIS_UTILS_HPP
#include <iostream>

namespace ft {

    template<typename Iter>
    size_t distance(Iter first, Iter last) {
        size_t distance = 0;
        while (first != last) {
            ++distance;
            ++first;
        }
        return distance;
    }

    template<typename Iter>
    void advance(Iter &it, size_t count) {
        while (count) {
            ++it;
            --count;
        }
    }

    template<typename T>
    void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    template <typename InputIt1, typename InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (*first1 < *first2) {
                return true;
            }
            if (*first2 < *first1) {
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }

    template<typename Pair>
    struct Select1st {
        typename Pair::first_type &operator()(Pair &x) const {
            return x.first;
        }
        const typename Pair::first_type &operator()(const Pair &x) const {
            return x.first;
        }
    };

    template<typename T>
    struct Identity {
        T &operator()(T &x) const {
            return x;
        }
        const T &operator()(const T &x) const {
            return x;
        }
    };
}
#endif //TVPIS_UTILS_HPP
