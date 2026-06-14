#include <bits/stdc++.h>
using namespace std;

int sumSubMins(vector<int>& arr) {
    int n = arr.size();
    
    vector<int> left(n), right(n);
    stack<int> st;

    // distance to previous smaller element
    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] > arr[i]) {
            st.pop();
        }
        left[i] = st.empty() ? (i + 1) : (i - st.top());
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // distance to next smaller or equal element
    for (int i = n - 1; i >= 0; i--) {
        while (!st.empty() && arr[st.top()] >= arr[i]) {
            st.pop();
        }
        right[i] = st.empty() ? (n - i) : (st.top() - i);
        st.push(i);
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        
        // Contribution of current element
        result += arr[i] * left[i] * right[i];
    }

    return result;
}

int main() {
    vector<int> arr = {1, 2, 3, 4};
    cout << sumSubMins(arr) << endl; 
    return 0;
}