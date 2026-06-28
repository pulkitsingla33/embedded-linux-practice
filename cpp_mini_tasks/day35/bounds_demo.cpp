#include <iostream>
#include <vector>
#include <algorithm> // Required for std::lower_bound and std::upper_bound

int main() {
    // Must be sorted!
    std::vector<int> data = {10, 20, 30, 30, 30, 40, 50};
    int target = 30;

    // 1. lower_bound: Points to the FIRST element that is >= target
    auto lb = std::lower_bound(data.begin(), data.end(), target);

    // 2. upper_bound: Points to the FIRST element that is > target
    auto ub = std::upper_bound(data.begin(), data.end(), target);

    // Print the results (converting iterators to indices)
    std::cout << "Vector: {10, 20, 30, 30, 30, 40, 50}\n";
    std::cout << "Target: " << target << "\n\n";

    std::cout << "lower_bound found value " << *lb 
              << " at index " << std::distance(data.begin(), lb) << "\n";

    std::cout << "upper_bound found value " << *ub 
              << " at index " << std::distance(data.begin(), ub) << "\n";

    // Practical use-case: Counting occurrences of the target
    int count = ub - lb;
    std::cout << "\nNumber of times " << target << " appears: " << count << "\n";

    return 0;
}