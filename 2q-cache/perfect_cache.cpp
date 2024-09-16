#include "perfect_cache.hpp"

template<typename T, typename KeyT>
Perfect_cache_t<T, KeyT>::Perfect_cache_t (const int size, const std::vector<T>& reqs) : requests (reqs), cache_max_size (size) {

    for (int i = 0; i < requests.size (); i++) {

        if (dist_map.find (requests[i]) == dist_map.end ()) {

            dist_map[requests[i]] = i;
        }
    }
}

template<typename T, typename KeyT>
bool Perfect_cache_t<T, KeyT>::cache_full () {

    if (cache.size () > cache_max_size) throw GenericError ("cache size exceeds cache_max_size");
    return cache.size () == cache_max_size;
}

template<typename T, typename KeyT>
template<typename F>
bool Perfect_cache_t<T, KeyT>::lookup_update (const int req_num, F slow_get_page) {

    auto hit = cache_map.find (requests[req_num]);

    if (hit == cache_map.end ()) {

        if (cache_full ()) {

            for (auto i : dist_map) {

                if (i.first == requests[req_num]) return false; // no cache hit if current request is the furthest

                if (cache_map.find (i.first) != cache_map.end ()) {

                    cache.erase (cache_map[i.first]);
                    cache_map.erase (i.first.id);
                }
            }

        }
    }
}