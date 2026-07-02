#include <bits/stdc++.h>
using namespace std;

int mostBooked(int n, vector<vector<int>>& meetings) {
    // Sort meetings by start time
    sort(meetings.begin(), meetings.end(),
         [](const vector<int>& a, const vector<int>& b) {
             return a[0] < b[0];
         });

    vector<long long> meetings_per_room(n, 0);

    // Min-heap of free room numbers
    priority_queue<int, vector<int>, greater<int>> free_rooms;
    for (int i = 0; i < n; i++) free_rooms.push(i);

    // Min-heap of (end_time, room_number) for occupied rooms
    priority_queue<pair<long long,int>, vector<pair<long long,int>>,
                   greater<pair<long long,int>>> busy_rooms;

    for (auto& m : meetings) {
        long long start = m[0];
        long long end   = m[1];

        // Free up any rooms whose meeting has ended by 'start'
        while (!busy_rooms.empty() && busy_rooms.top().first <= start) {
            free_rooms.push(busy_rooms.top().second);
            busy_rooms.pop();
        }

        if (!free_rooms.empty()) {
            // A room is available right now — use lowest-numbered free room
            int room = free_rooms.top();
            free_rooms.pop();
            meetings_per_room[room]++;
            busy_rooms.push({end, room});
        } else {
            // No room free — must wait for the earliest room to free up
            auto [free_time, room] = busy_rooms.top();
            busy_rooms.pop();
            long long duration = end - start;
            long long new_end = free_time + duration;
            meetings_per_room[room]++;
            busy_rooms.push({new_end, room});
        }
    }

    int best = 0;
    for (int i = 1; i < n; i++)
        if (meetings_per_room[i] > meetings_per_room[best])
            best = i;

    return best;
}

int main() {
    vector<vector<int>> meetings = {{1,20},{2,10},{3,5},{4,9},{6,8}};
    int n = 2;
    cout << mostBooked(n, meetings) << endl;   // expect 0
    return 0;
}