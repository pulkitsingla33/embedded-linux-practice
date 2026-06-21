#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string removeKdigits(string num, int k) {
        string result = ""; // This string will act as our stack
        
        for (char current_digit : num) {
            // While we still have digits to remove (k > 0)
            // AND the stack is not empty
            // AND the current digit is smaller than the top of the stack
            while (k > 0 && !result.empty() && result.back() > current_digit) {
                result.pop_back(); // Remove the larger digit
                k--;               // Decrement our removal quota
            }
            
            // Prevent pushing leading zeros into our stack
            if (!result.empty() || current_digit != '0') {
                result.push_back(current_digit);
            }
        }
        
        // Edge Case: If we have processed all digits but still need to remove some
        // (e.g., the digits were already in ascending order like "1234")
        // We just chop them off the end.
        while (!result.empty() && k > 0) {
            result.pop_back();
            k--;
        }
        
        // Edge Case: If the string is empty (e.g., we removed everything), return "0"
        return result.empty() ? "0" : result;
    }
};

int main() {
    Solution sol;
    string num = "1432219";
    int k = 3;
    
    cout << "Input: num = " << num << ", k = " << k << endl;
    cout << "Output: " << sol.removeKdigits(num, k) << endl;
    
    return 0;
}