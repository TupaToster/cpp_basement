#pragma once
#include <cstdlib>
#include <iostream>
#include <list>
#include <unordered_map>

template <typename T, typename KeyT = int>
struct Cache_2q_t {

    std::list<T> a1;
    std::list<T> am;

    int a1_max_size = 0;
    int am_max_size = 0;

    using ListIt = typename std::list<T>::iterator;
    std::unordered_map<KeyT, ListIt> a1_hash_map;
    std::unordered_map<KeyT, ListIt> am_hash_map;

    class GenericError : std::exception {

        private:

        const char* message;

        public:

        GenericError (const char* msg) : message (msg) {}

        const char* what () {

            return message;
        }
    };

    class BadSize : std::exception {

        public:

        const char* what () {

            return "Bad size argument passed to constructor";
        }
    };

    // ------ end of variables -------

    Cache_2q_t (const int a1_size, const int am_size);

    Cache_2q_t (const int sum_size);

    template <typename F>
    bool lookup_update (const KeyT req, F slow_get_page);

    bool a1_is_full ();

    bool am_is_full ();

};


template <typename T, typename KeyT>
Cache_2q_t<T, KeyT>::Cache_2q_t (const int a1_size, const int am_size) : a1_max_size (a1_size), am_max_size (am_size) {

    if (a1_max_size < 1) throw BadSize ();
    if (am_max_size < 1) throw BadSize ();
}

template <typename T, typename KeyT>
Cache_2q_t<T, KeyT>::Cache_2q_t (const int sum_size) {

    a1_max_size = sum_size / 2;
    am_max_size = sum_size - a1_max_size;

    if (a1_max_size < 1) throw BadSize ();
    if (am_max_size < 1) throw BadSize ();
}

template<typename T, typename KeyT>
template<typename F>
bool Cache_2q_t<T, KeyT>::lookup_update (const KeyT req, F slow_get_page) {

    auto hit_a1 = a1_hash_map.find (req);

    if (hit_a1 == a1_hash_map.end ()) {

        auto hit_am = am_hash_map.find (req);

        if (hit_am == am_hash_map.end ()) {

            if (a1_is_full ()) {

                a1_hash_map.erase (a1.back ().id);
                a1.pop_back ();
            }

            a1.push_front (slow_get_page (req));
            a1_hash_map[req] = a1.front ();
            return false;
        }

        auto hit_It = hit_am->second;

        if (hit_It != am.begin ()) {

            am.splice (am.begin (), am, hit_It, std::next (hit_It));
            am_hash_map[req] = am.front ();
        }

        return true;
    }

    auto hit_It = hit_a1->second;

    if (am_is_full ()) {

        am_hash_map.erase (am.back ().id);
        am.pop_back ();
    }

    am.splice (am.begin (), a1, hit_It, std::next (hit_It));
    am_hash_map[req] = am.front ();

    return true;
}

template<typename T, typename KeyT>
bool Cache_2q_t<T, KeyT>::am_is_full () {

    if (am.size () > am_max_size) throw GenericError ("am cache size larger than am_max_size");
    return am.size () == am_max_size;
}