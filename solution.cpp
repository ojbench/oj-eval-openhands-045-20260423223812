
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
};

struct ElevatorSystem {
    int current_floor;
    int direction; // 1 for up, -1 for down
    MinHeap up_heap;   // requests >= current floor
    MaxHeap down_heap; // requests <= current floor
    
    ElevatorSystem() {
        current_floor = 0;
        direction = 1; // start going up
    }
    
    void add_request(int x) {
        if (x >= current_floor) {
            up_heap.push(x);
        } else {
            down_heap.push(x);
        }
    }
    
    void cancel_request(int x) {
        // Remove from appropriate heap
        if (x >= current_floor) {
            MinHeap new_up;
            while (!up_heap.empty()) {
                int val = up_heap.top();
                up_heap.pop();
                if (val != x) {
                    new_up.push(val);
                }
            }
            up_heap = new_up;
        } else {
            MaxHeap new_down;
            while (!down_heap.empty()) {
                int val = down_heap.top();
                down_heap.pop();
                if (val != x) {
                    new_down.push(val);
                }
            }
            down_heap = new_down;
        }
    }
    
    void action() {
        if (up_heap.empty() && down_heap.empty()) {
            return; // no requests, stay still
        }
        
        if (direction == 1) { // going up
            if (!up_heap.empty()) {
                int next_floor = up_heap.top();
                up_heap.pop();
                current_floor = next_floor;
                
                // Clean up heaps: move elements that are now in wrong heap
                MinHeap new_up;
                while (!up_heap.empty()) {
                    int val = up_heap.top();
                    up_heap.pop();
                    if (val > current_floor) {
                        new_up.push(val);
                    } else {
                        down_heap.push(val);
                    }
                }
                up_heap = new_up;
            } else {
                direction = -1; // reverse direction
                if (!down_heap.empty()) {
                    int next_floor = down_heap.top();
                    down_heap.pop();
                    current_floor = next_floor;
                    
                    // Clean up heaps: move elements that are now in wrong heap
                    MaxHeap new_down;
                    while (!down_heap.empty()) {
                        int val = down_heap.top();
                        down_heap.pop();
                        if (val < current_floor) {
                            new_down.push(val);
                        } else {
                            up_heap.push(val);
                        }
                    }
                    down_heap = new_down;
                }
            }
        } else { // going down
            if (!down_heap.empty()) {
                int next_floor = down_heap.top();
                down_heap.pop();
                current_floor = next_floor;
                
                // Clean up heaps: move elements that are now in wrong heap
                MaxHeap new_down;
                while (!down_heap.empty()) {
                    int val = down_heap.top();
                    down_heap.pop();
                    if (val < current_floor) {
                        new_down.push(val);
                    } else {
                        up_heap.push(val);
                    }
                }
                down_heap = new_down;
            } else {
                direction = 1; // reverse direction
                if (!up_heap.empty()) {
                    int next_floor = up_heap.top();
                    up_heap.pop();
                    current_floor = next_floor;
                    
                    // Clean up heaps: move elements that are now in wrong heap
                    MinHeap new_up;
                    while (!up_heap.empty()) {
                        int val = up_heap.top();
                        up_heap.pop();
                        if (val > current_floor) {
                            new_up.push(val);
                        } else {
                            down_heap.push(val);
                        }
                    }
                    up_heap = new_up;
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
