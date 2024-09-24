#pragma once
#include <iostream>
#include <cstdlib>
#include <list>
#include <unordered_set>
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

    std::unordered_set<T> cache;
    std::vector<T> requests;

    unsigned int cache_max_size = 0;

    using CacheIt = typename std::unordered_set<T>::iterator;
    std::unordered_map<KeyT, CacheIt> cache_map;

    using DistMonT = typename std::set<std::pair<KeyT, std::list<u_int32_t>>,
        decltype ([](const std::pair<KeyT, std::list<u_int32_t>>& lhs, const std::pair<KeyT, std::list<u_int32_t>>& rhs)
            {return *(lhs.second.begin ()) > *(rhs.second.begin ());})>;

    DistMonT dist_set;

    using DistSetIt = DistMonT::iterator;
    std::unordered_map<KeyT, DistSetIt> dist_map;

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

    template<typename F>
    Perfect_cache_t (const int size, const std::vector<T>& reqs, F slow_get_page) : requests (reqs), cache_max_size (size) {

        for (int i = 0; i < requests.size (); i++) {

            if (dist_map.find (requests[i]) == dist_map.end ()) {

                auto dist_set_it = dist_set.emplace (requests[i]), std::list<u_int32_t> {i});
                dist_map[dist_set_it.first->first] = dist_set_it.first;
            }
            else {

                dist_map[requests[i]]->second.push_back (i);
            }
        }
    }

    bool cache_full () {

        if (cache.size () > cache_max_size) throw GenericError ("cache size exceeds cache_max_size");
        return cache.size () == cache_max_size;
    }

    template<typename F>
    bool lookup_update (const int req_num, F slow_get_page) {

        T req = requests[req_num];

        auto hit = cache_map.find ()
    }

    void dump () {

        std::cout << "-------------------------\n";

        std::cout << "requests : [";
        for (auto i : requests) std::cout << i << ", ";
        std::cout << "end]\n";

        std::cout << "cache : [";
        for (auto i : cache) std::cout << i << ", ";
        std::cout << "end]\n";

        std::cout << "cache_map : [";
        for (auto i : cache_map) std::cout << "<" << i.first << ", " << std::distance (cache.begin (), i.second) << ">, ";
        std::cout << "end]\n";

        std::cout << "dist_map : [";
        for (auto i : dist_map) std::cout << "<" << i.first << ", " << i.second->second << ">, ";
        std::cout << "end]\n";

        std::cout << "dist_set : [";
        for (auto i : dist_set) std::cout << "<" << i.first << ", " << i.second << ">, ";
        std::cout << "end];\n-------------------------\n";
    }
};
