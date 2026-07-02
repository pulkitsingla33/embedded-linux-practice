#include <vector>
#include <unordered_map>
#include <cstdlib>

class RandomizedSet {
private:
    std::vector<int> nums;
    std::unordered_map<int, int> valToIndex;

public:
    RandomizedSet() {
        // Constructor
    }
    
    // Inserts a value to the set. Returns true if the set did not already contain the specified element.
    bool insert(int val) {
        if (valToIndex.find(val) != valToIndex.end()) {
            return false; // Element already exists
        }
        
        nums.push_back(val);
        valToIndex[val] = nums.size() - 1;
        return true;
    }
    
    // Removes a value from the set. Returns true if the set contained the specified element.
    bool remove(int val) {
        if (valToIndex.find(val) == valToIndex.end()) {
            return false; // Element does not exist
        }
        
        // 1. Find the index of the element to delete and the value of the last element
        int idxToDelete = valToIndex[val];
        int lastElement = nums.back();
        
        // 2. Move the last element into the position of the element to delete
        nums[idxToDelete] = lastElement;
        valToIndex[lastElement] = idxToDelete;
        
        // 3. Remove the last element from both the vector and the map
        nums.pop_back();
        valToIndex.erase(val);
        
        return true;
    }
    
    // Get a random element from the set.
    int getRandom() {
        // Generate a random index between 0 and nums.size() - 1
        int randomIndex = rand() % nums.size();
        return nums[randomIndex];
    }
};