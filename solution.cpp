
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 500005;

struct MinHeap {
    int arr[MAXN];
    int cnt;
    
    MinHeap() {
        cnt = 0;
    }
    
    void push(int x) {
        arr[++cnt] = x;
        for (int i = cnt, j = cnt >> 1; j; i = j, j >>= 1) {
            if (arr[j] > arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
    }
    
    void pop() {
        if (cnt == 0) return;
        arr[1] = arr[cnt--];
        for (int i = 1, j = i << 1; j <= cnt; i = j, j <<= 1) {
            if (j + 1 <= cnt && arr[j + 1] < arr[j]) j++;
            if (arr[j] < arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
    }
    
    int top() {
        return cnt > 0 ? arr[1] : -1;
    }
    
    bool empty() {
        return cnt == 0;
    }
    
    void clear() {
        cnt = 0;
    }
    
    int size() {
        return cnt;
    }
    
    int get_at(int idx) {
        return arr[idx];
    }
};

struct MaxHeap {
    int arr[MAXN];
    int cnt;
    
    MaxHeap() {
        cnt = 0;
    }
    
    void push(int x) {
        arr[++cnt] = x;
        for (int i = cnt, j = cnt >> 1; j; i = j, j >>= 1) {
            if (arr[j] < arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
    }
    
    void pop() {
        if (cnt == 0) return;
        arr[1] = arr[cnt--];
        for (int i = 1, j = i << 1; j <= cnt; i = j, j <<= 1) {
            if (j + 1 <= cnt && arr[j + 1] > arr[j]) j++;
            if (arr[j] > arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
    }
    
    int top() {
        return cnt > 0 ? arr[1] : -1;
    }
    
    bool empty() {
        return cnt == 0;
    }
    
    void clear() {
        cnt = 0;
    }
    
    int size() {
        return cnt;
    }
    
    int get_at(int idx) {
        return arr[idx];
    }
};

struct ElevatorSystem {
    int current_floor;
    int direction; // 1 for up, -1 for down
    MinHeap up_requests;   // requests above current floor
    MaxHeap down_requests; // requests below current floor
    
    ElevatorSystem() {
        current_floor = 0;
        direction = 1; // start going up
    }
    
    void add_request(int x) {
        if (x > current_floor) {
            up_requests.push(x);
        } else {
            down_requests.push(x);
        }
    }
    
    void cancel_request(int x) {
        // Since we can't efficiently remove arbitrary elements from heap,
        // we'll rebuild the heaps without the cancelled element
        MinHeap new_up;
        MaxHeap new_down;
        
        // Rebuild up_requests
        while (!up_requests.empty()) {
            int val = up_requests.top();
            up_requests.pop();
            if (val != x) {
                new_up.push(val);
            }
        }
        
        // Rebuild down_requests
        while (!down_requests.empty()) {
            int val = down_requests.top();
            down_requests.pop();
            if (val != x) {
                new_down.push(val);
            }
        }
        
        up_requests = new_up;
        down_requests = new_down;
    }
    
    void action() {
        if (up_requests.empty() && down_requests.empty()) {
            return; // no requests, stay still
        }
        
        if (direction == 1) { // going up
            if (!up_requests.empty()) {
                int next_floor = up_requests.top();
                up_requests.pop();
                current_floor = next_floor;
                
                // Rebuild heaps based on new current floor
                MinHeap new_up;
                MaxHeap new_down;
                
                while (!up_requests.empty()) {
                    int val = up_requests.top();
                    up_requests.pop();
                    if (val > current_floor) {
                        new_up.push(val);
                    } else {
                        new_down.push(val);
                    }
                }
                
                while (!down_requests.empty()) {
                    int val = down_requests.top();
                    down_requests.pop();
                    if (val > current_floor) {
                        new_up.push(val);
                    } else {
                        new_down.push(val);
                    }
                }
                
                up_requests = new_up;
                down_requests = new_down;
            } else {
                direction = -1; // reverse direction
                if (!down_requests.empty()) {
                    int next_floor = down_requests.top();
                    down_requests.pop();
                    current_floor = next_floor;
                    
                    // Rebuild heaps based on new current floor
                    MinHeap new_up;
                    MaxHeap new_down;
                    
                    while (!up_requests.empty()) {
                        int val = up_requests.top();
                        up_requests.pop();
                        if (val > current_floor) {
                            new_up.push(val);
                        } else {
                            new_down.push(val);
                        }
                    }
                    
                    while (!down_requests.empty()) {
                        int val = down_requests.top();
                        down_requests.pop();
                        if (val > current_floor) {
                            new_up.push(val);
                        } else {
                            new_down.push(val);
                        }
                    }
                    
                    up_requests = new_up;
                    down_requests = new_down;
                }
            }
        } else { // going down
            if (!down_requests.empty()) {
                int next_floor = down_requests.top();
                down_requests.pop();
                current_floor = next_floor;
                
                // Rebuild heaps based on new current floor
                MinHeap new_up;
                MaxHeap new_down;
                
                while (!up_requests.empty()) {
                    int val = up_requests.top();
                    up_requests.pop();
                    if (val > current_floor) {
                        new_up.push(val);
                    } else {
                        new_down.push(val);
                    }
                }
                
                while (!down_requests.empty()) {
                    int val = down_requests.top();
                    down_requests.pop();
                    if (val > current_floor) {
                        new_up.push(val);
                    } else {
                        new_down.push(val);
                    }
                }
                
                up_requests = new_up;
                down_requests = new_down;
            } else {
                direction = 1; // reverse direction
                if (!up_requests.empty()) {
                    int next_floor = up_requests.top();
                    up_requests.pop();
                    current_floor = next_floor;
                    
                    // Rebuild heaps based on new current floor
                    MinHeap new_up;
                    MaxHeap new_down;
                    
                    while (!up_requests.empty()) {
                        int val = up_requests.top();
                        up_requests.pop();
                        if (val > current_floor) {
                            new_up.push(val);
                        } else {
                            new_down.push(val);
                        }
                    }
                    
                    while (!down_requests.empty()) {
                        int val = down_requests.top();
                        down_requests.pop();
                        if (val > current_floor) {
                            new_up.push(val);
                        } else {
                            new_down.push(val);
                        }
                    }
                    
                    up_requests = new_up;
                    down_requests = new_down;
                }
            }
        }
    }
    
    int locate() {
        return current_floor;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    ElevatorSystem elevator;
    
    for (int i = 0; i < n; i++) {
        string command;
        cin >> command;
        
        if (command == "action") {
            elevator.action();
        } else if (command == "add") {
            int x;
            cin >> x;
            elevator.add_request(x);
        } else if (command == "cancel") {
            int x;
            cin >> x;
            elevator.cancel_request(x);
        } else if (command == "locate") {
            cout << elevator.locate() << "\n";
        }
    }
    
    return 0;
}
