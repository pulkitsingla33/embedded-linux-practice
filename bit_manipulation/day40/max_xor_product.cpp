class Solution {
public:
    int maximumXorProduct(long long a, long long b, int n) {
        const int MOD = 1000000007;
      
        // Initialize XOR results by preserving bits above position n-1
        // These bits cannot be modified by x (since x < 2^n)
        long long xorResultA = (a >> n) << n;  // Clear lower n bits of a
        long long xorResultB = (b >> n) << n;  // Clear lower n bits of b
      
        // Process each bit position from (n-1) down to 0
        // We can choose x to have any bit pattern in these positions
        for (int bitPos = n - 1; bitPos >= 0; --bitPos) {
            // Extract the current bit from original values a and b
            int bitFromA = (a >> bitPos) & 1;
            int bitFromB = (b >> bitPos) & 1;
          
            if (bitFromA == bitFromB) {
                // When bits are same, setting x's bit to opposite value
                // makes both XOR results have 1 at this position
                // This maximizes the product
                xorResultA |= (1LL << bitPos);
                xorResultB |= (1LL << bitPos);
            } else {
                // When bits are different, one XOR result gets 1, other gets 0
                // Give the bit to the smaller number to balance the product
                if (xorResultA < xorResultB) {
                    xorResultA |= (1LL << bitPos);
                } else {
                    xorResultB |= (1LL << bitPos);
                }
            }
        }
      
        // Apply modulo to prevent overflow
        xorResultA %= MOD;
        xorResultB %= MOD;
      
        // Return the product modulo MOD
        return (xorResultA * xorResultB) % MOD;
    }
};