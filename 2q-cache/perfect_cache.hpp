#pragma once
#include <iostream>
#include <cstdlib>
#include <list>
#include <unordered_map>
#include <vector>
#include <map>
#include <set>

/**
 * @brief This is a perfect cache implementation
 *
 * @tparam T type of value
 * @tparam KeyT type of key
 *
 * @remark Well the mechanism is as follows: It gets a page as an input; it checks distances to the closest entry of every key in upcoming requests; it replaces one that will be needed the latest; rinse and repeat
 */
template <typename T, typename KeyT = int>
struct Perfect_cache_t {

    std::set<T> cache;
    std::vector<T> requests;

    unsigned int cache_max_size = 0;

    using CacheIt = typename std::set<T>::iterator;
    std::unordered_map<KeyT, CacheIt> cache_map;

    /**
     * @brief Немного костыльная мапа которая сортирует не ключи а значения которые им соответствуют; в теории так будет более менее быстро
     * @brief А суть её в том чтобы по кд хранить ключ до которого наименьшее расстояние по реквестам
     * @brief Не знаю зачем я это делаю, но это прикольно хотя бы
     */
    std::map<KeyT, int, decltype ([&](const KeyT& key1, const KeyT& key2){ return ((*this)[key1] - (*this)[key2]);})> dist_map;
    using DistIt = typename std::map<KeyT, int, decltype ([&](const KeyT key1, const KeyT key2){ return ((*this)[key2] - (*this)[key1]);})>::iterator;

    class GenericError : std::exception {

        private:

        char* message;

        public:

        GenericError (const char* msg) : message (msg) {}

        char* what () {

            return message;
        }
    };

    // ----------- end of variables ---------------

    Perfect_cache_t (const int size, const std::vector<T>& reqs);

    bool cache_full ();

    template<typename F>
    bool lookup_update (const int req_num, F slow_get_page);
};
