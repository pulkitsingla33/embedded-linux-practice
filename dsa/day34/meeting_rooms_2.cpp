// C++ program to find minimum no of rooms using
// sorting and two pointers.

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Function to find the minimum number of rooms
// required
int minMeetingRooms(vector<int> &start, vector<int> &end) {
    int n = start.size();

    // no. of rooms at any point of time.
    int room = 0;
    int res = 0;

    // sorting the start and end time of meetings
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    // pointing to the current index of start array and end array.
    int i = 0, j = 0;

    while (i < start.size()) {

        // encountered start time of meeting.
        if (start[i] < end[j]) {
            // increase no of rooms
            room++;
            i++;
        }

        // encountered end time of meeting.
        else {
            // decrease no of rooms.
            room--;
            j++;
        }
        // updating final result
        res = max(res, room);
    }
    return res;
}

int main() {

    vector<int> start = {2, 9, 6};
    vector<int> end = {4, 12, 10};
    cout << minMeetingRooms(start, end);
    return 0;
}