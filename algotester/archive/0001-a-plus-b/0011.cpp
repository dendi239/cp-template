#include <bits/stdc++.h>


auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t count;
    std::cin >> count;

    std::vector<int64_t> packs(count);
    for (auto &pack : packs) {
        std::cin >> pack;
    }

    std::cout << (std::accumulate(packs.begin(), packs.end(), int64_t(0)) - packs.size()) << '\n';
    
    return 0;
}


