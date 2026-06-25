#include <vector>
#include <algorithm>

class Solution {
public:
    int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
        int n = position.size();
        if (n == 0) return 0;

        // Pair up position and speed so we can sort them together
        std::vector<std::pair<int, double>> cars(n);
        for (int i = 0; i < n; ++i) {
            // Calculate time to target as a double to avoid integer division issues
            double time = (double)(target - position[i]) / speed[i];
            cars[i] = {position[i], time};
        }

        // Sort cars by position in descending order (closest to target first)
        std::sort(cars.begin(), cars.end(), [](const auto& a, const auto& b) {
            return a.first > b.first;
        });

        int fleetCount = 0;
        double currentMaxTime = 0.0;

        // Traverse from closest to farthest from the target
        for (int i = 0; i < n; ++i) {
            // If this car takes more time than the current fleet leader,
            // it cannot catch up, so it starts a new fleet.
            if (cars[i].second > currentMaxTime) {
                fleetCount++;
                currentMaxTime = cars[i].second; // This car is now the new fleet leader
            }
        }

        return fleetCount;
    }
};