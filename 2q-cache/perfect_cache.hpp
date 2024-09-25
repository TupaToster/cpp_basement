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
    std::vector<T> reqs;

    unsigned int cache_max_size = 0;

    using CacheIt = typename std::unordered_set<T>::iterator;
    std::unordered_map<KeyT, CacheIt> cache_map;

    using DistSetT = typename std::set<std::pair<
                                                KeyT,
                                                std::list<u_int32_t>>,
                                                decltype ([](const std::pair<KeyT, std::list<u_int32_t>>& lhs, const std::pair<KeyT, std::list<u_int32_t>>& rhs) -> bool
                                                {return ((*lhs.second.begin ()) < (*rhs.second.begin ()));})>;

    DistSetT dist_set;

    using DistSetIt = DistSetT::iterator;
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

    /**
     * @brief Construct a new Perfect_cache_t object
     *
     * @tparam F function type for getting a page from ram (slow)
     * @param size size of cache
     * @param reqs_ vector of requests
     * @param slow_get_page function for getting page from KeyT
     */
    template<typename F>
    Perfect_cache_t (const int size, const std::vector<T>& reqs_, F slow_get_page) : reqs (reqs_), cache_max_size (size) {

        for (int i = 0; i < reqs.size (); i++) {

            auto hit = dist_map.find (reqs[i]); ///< Check if key was already encountered

            // Well where to start... First of all - set iterator is const for a reason; if u change it without set's knowledge, set loses it's sortedness.
            // In this place it works correctly because order is defined on creation of set element, so in this SPECIFIC scenario and this SPECIFIC place -fpermissive is justified
            if (dist_map.count (reqs[i]))   dist_map[reqs[i]]->second.push_back (i); ///< add pos to end of list of known positions}
            else dist_map[reqs[i]] = dist_set.emplace (reqs[i], std::list<u_int32_t> (1, i)).first; ///< just create new entry with list of one element
        }

        for (auto& i : dist_set) {
            i.second.push_back (-1); ///< add u_int32_t (-1) (inf in this context) as the last element (to signify that we will not find this element in requests anymore)
        }
    }

    bool cache_full () {

        if (cache.size () > cache_max_size) throw GenericError ("cache size exceeds cache_max_size");
        return cache.size () == cache_max_size;
    }

    template<typename F>
    bool lookup_update (const int req_num, F slow_get_page) {


        KeyT req = reqs[req_num];

        // Here i will extract an element, change it and put it back
        auto node = dist_set.extract (dist_map[req]);
        node.value ().second.pop_front ();
        dist_set.insert (std::move (node));
        // Well if it works it works lol
        /// @remark Let me explain myself here. This is a crutch that exists only because i didn't waste time to research the fact, that set elements can not be changed in place, but need to be extracted and modified outside of it not to break sets orderd... so yeah i hereby consent to any shaming that may (and will follow) :)

        if (cache_map.find (req) != cache_map.end ()) return 1; ///< if already in cache
        else {

            if (!cache_full ()) {

                cache_map[req] = cache.emplace (slow_get_page (req)).first;
                return 0;
            }

            if (dist_set.begin ()->first == req) return 0; ///< if request is furthest

            for (auto i : dist_set) {

                if (cache_map.find (i.first) != cache_map.end ()) {

                    if (i.second.front () < dist_map[req]->second.front ()) return 0; ///< if distance to the furthest elem in cache is less than dist to req than return 0

                    // replace found in cache with req
                    cache.erase (cache_map[i.first]);
                    cache_map.erase (i.first);

                    // add requested element to cache
                    cache_map[req] = cache.emplace (slow_get_page (req)).first;
                    return 0;
                }
            }

            // if no element that we will meet is in cache

            if (dist_map[req]->second.front () != (u_int32_t) -1) {

                cache.erase (cache_map.begin ()->second);
                cache_map.erase (cache_map.begin ());

                cache_map[req] = (cache.emplace (slow_get_page (req))).first;

                return 0;
            }
        }
    }

    void dump () {

        std::cout << "-------------------------\n";

        std::cout << "requests : [";
        for (auto i : reqs) std::cout << i << ", ";
        std::cout << "end]\n";

        std::cout << "cache : [";
        for (auto i : cache) std::cout << i << ", ";
        std::cout << "end]\n";

        std::cout << "cache_map : [";
        for (auto i : cache_map) std::cout << "<" << i.first << ", " << std::distance (cache.begin (), i.second) << ">, ";
        std::cout << "end]\n";

        std::cout << "dist_map : [";
        for (auto i : dist_map) {

            int counter = 0;

            std::cout << "(" << i.second->second.size () << ")" << "<" << i.first << ", {";
            for (auto j : i.second->second) {

                std::cout << j << ", ";
                counter++;
                if (counter >= (i.second->second.size ())) break;
            }
            std::cout << "end}>, ";
        }
        std::cout << "end]\n";

        std::cout << "dist_set : [";
        for (auto i : dist_set) {

            std::cout << "<" << i.first << ", {";
            for (auto j : i.second) std::cout << j << ", ";
            std::cout << "end}>, ";
        }
        std::cout << "end];\n-------------------------\n";
    }
};
