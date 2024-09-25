#include <cstdlib>
#include <iostream>
#include <vector>
#include "2q.hpp"
#include "perfect_cache.hpp"

int slow_get_page_emulator (int req) {

    int j = 2;
    for (int i = 0; i < 100000; i++) j *= (j-1);
    return req;
}



int main (int argc, char* argv[]) {

    std::setvbuf(stdout, nullptr, _IONBF, 0);

    std::cout << "Insert summary cache size in pages (note that approximately 50%% of it will go to A1 and the rest to Am) : ";
    int cache_size = 0;
    std::cin >> cache_size;

    Cache_2q_t<int> cache(cache_size);

    std::cout << "Insert number of requests : ";
    int request_count = 0;
    std::cin >> request_count;

    if (request_count < 1) throw Cache_2q_t<int>::GenericError ("Request count less than one");

    std::cout << "Now insert " << request_count  << " numbers that will represent page numbers to look up:\n";

    std::vector<int> reqs (request_count);

    for (auto& i : reqs) std::cin >> i;

    std::cout << "Now chill out and enjoy the testing)\n";

    cache.dump ();

    std::cout << "Test start\n";

    std::vector<bool> lookupResults (request_count);

    for (int i = 0; i < request_count; i++) {

        lookupResults[i] = cache.lookup_update (reqs[i], slow_get_page_emulator);
        std::cout << lookupResults[i] << "\n";
        cache.dump ();
    }
    std::cout << std::endl;

    std::cout << "Now lets compare it to an ideal cache\n";

    Perfect_cache_t<int> perf_cache (cache_size, reqs, slow_get_page_emulator);

    perf_cache.dump ();

    std::cout << "Test start\n";

    for (int i = 0; i < request_count; i++) {

        lookupResults[i] = perf_cache.lookup_update (i, slow_get_page_emulator);
        std::cout << lookupResults[i] << "\n";
        perf_cache.dump ();
    }
}
