#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        int rowCount = matrix.size();
        int colCount = matrix[0].size();
      
        // Convert each row to a bitmask where bit j is set if matrix[i][j] == 1
        vector<int> rowBitmasks(rowCount, 0);
        for (int i = 0; i < rowCount; ++i) {
            for (int j = 0; j < colCount; ++j) {
                if (matrix[i][j] == 1) {
                    rowBitmasks[i] |= (1 << j);
                }
            }
        }
      
        int maxCoveredRows = 0;
      
        // Try all possible combinations of selecting numSelect columns
        for (int columnMask = 1; columnMask < (1 << colCount); ++columnMask) {
            // Skip if the number of selected columns is not equal to numSelect
            if (__builtin_popcount(columnMask) != numSelect) {
                continue;
            }
          
            // Count how many rows are fully covered by the selected columns
            int coveredRowCount = 0;
            for (int rowMask : rowBitmasks) {
                // A row is covered if all its 1s are in the selected columns
                // This means (rowMask & columnMask) should equal rowMask
                if ((rowMask & columnMask) == rowMask) {
                    coveredRowCount++;
                }
            }
          
            // Update the maximum number of covered rows
            maxCoveredRows = max(maxCoveredRows, coveredRowCount);
        }
      
        return maxCoveredRows;
    }
};