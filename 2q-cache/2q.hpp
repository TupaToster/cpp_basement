#pragma once
#include <cstdlib>
#include <iostream>
#include <list>
#include <unordered_map>
#include <fstream>
#include "lib.hpp"

template <typename T, typename KeyT = int>
struct Cache_2q_t {

    using ListIt = typename std::list<T>::iterator;         ///< list iterator type
    std::list<T>                        a1;                 ///< list for a1 cache (first met)
    std::list<T>                        am;                 ///< list for am cache (met multiple times)
    int                                 a1_max_size = 0;    ///< max allowed size for a1 (approx 50% of sum size)
    int                                 am_max_size = 0;    ///< max allowed size for am (what is left from a1)
    std::unordered_map<KeyT, ListIt>    a1_hash_map;        ///< hash map key -> list iterator for a1
    std::unordered_map<KeyT, ListIt>    am_hash_map;        ///< hash map key -> list iterator for am

    /**
     * @brief generic error that gets it's error during construction
     */
    class GenericError : std::exception {

        private:

        const char* message;

        public:

        GenericError (const char* msg) : message (msg) {}

        const char* what () {

            return message;
        }
    };

    /**
     * @brief exception for bad size passed to cache constructor (1 or more of caches is zero)
     */
    class BadSize : std::exception {

        public:

        const char* what () {

            return "Bad size argument passed to constructor";
        }
    };

    // ------ end of variables -------

    /**
     * @brief Construct a new Cache_2q_t object
     *
     * @param a1_size size of a1 cache
     * @param am_size size of am cache
     */
    Cache_2q_t (const int a1_size, const int am_size) : a1_max_size (a1_size), am_max_size (am_size) {

        if (a1_max_size < 1) throw BadSize ();
        if (am_max_size < 1) throw BadSize ();
    }

    /**
     * @brief Construct a new Cache_2q_t object
     *
     * @param sum_size total size allowed for 2 caches
     */
    Cache_2q_t (const int sum_size) {

        a1_max_size = sum_size / 2;
        am_max_size = sum_size - a1_max_size;

        if (a1_max_size < 1) throw BadSize ();
        if (am_max_size < 1) throw BadSize ();
    }

    /**
     * @brief looks up request in cache and manages it's caching; returns if it was a hit or a miss
     *
     * @tparam F function type that emulates loading page from ram
     * @param req key of request (would be hash of page irl i guess)
     * @param slow_get_page function for slowly getting page from ram
     * @return true if cache hit (a1 or am)
     * @return false if cache miss
     */
    template <typename F>
    bool lookup_update (const KeyT req, F slow_get_page) {

        auto a1_hit = a1_hash_map.find (req);

        if (a1_hit != a1_hash_map.end ()) {

            ListIt iter = a1_hit->second;

            if (am_is_full ()) {

                am_hash_map.erase (am.back ());
                am.pop_back ();
            }

            am.splice (am.begin (), a1, iter, std::next (iter));
            am_hash_map[*iter] = am.begin ();

            a1_hash_map.erase (a1_hit);

            return 1;
        }
        else {

            auto am_hit = am_hash_map.find (req);

            if (am_hit != am_hash_map.end ()) {

                ListIt iter = am_hit->second;

                if (iter == am.begin ()) return 1;

                am.splice (am.begin (), am, iter, std::next (iter));
                am_hit->second = am.begin ();

                return 1;
            }
            else {

                if (a1_is_full ()) {

                    a1_hash_map.erase (a1.back ());
                    a1.pop_back ();
                }

                a1.push_front (slow_get_page (req));
                a1_hash_map[req] = a1.begin ();

                return 0;
            }
        }
    }

    /**
     * @brief check a1 for fullness
     *
     * @return true if full
     * @return false if unfull
     */
    bool a1_is_full () {

        if (a1.size () > a1_max_size) throw GenericError ("a1 cache size larger than a1_max_size");
        return a1.size () == a1_max_size;
    }

    /**
     * @brief check am for fullness
     *
     * @return true if full
     * @return false if unfull
     */
    bool am_is_full () {

        if (am.size () > am_max_size) throw GenericError ("am cache size larger than am_max_size");
        return am.size () == am_max_size;
    }

    /**
     * @brief dump function to log basic parameters of a class such as a1, am, a1_hash_map, am_hash_map
     *
     * @param log_file ref to output stream in case it is desired to dump not to cout but to some other file stream or idk /dev/null
     */
    void dump (std::ostream& log_file = std::cout) {

        log_file << "a1 : [";
        for (auto i : a1) log_file << i << ", ";
        log_file << "end]\n";

        log_file << "a1_map : [";
        for (auto i : a1_hash_map) log_file << '<' << i.first << ", " << std::distance (a1.begin (), i.second) << ">, ";
        log_file << "end]\n";

        log_file << "am : [";
        for (auto i : am) log_file << i << ", ";
        log_file << "end]\n";

        log_file << "am_map : [";
        for (auto i : am_hash_map) log_file << '<' << i.first << ", " << std::distance (am.begin (), i.second) << ">, ";
        log_file << "end]\n\n";
    }

};
