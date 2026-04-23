
#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 500005;

struct MinHeap {
    int arr[MAXN], cnt;
    bool in_heap[MAXN];
    
    MinHeap() {
        cnt = 0;
        for (int i = 0; i < MAXN; i++) {
            in_heap[i] = false;
        }
    }
    
    void push(int x) {
        if (in_heap[x]) return;
        arr[++cnt] = x;
        in_heap[x] = true;
        
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
        in_heap[arr[1]] = false;
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
    
    bool contains(int x) {
        return in_heap[x];
    }
    
    void remove(int x) {
        if (!in_heap[x]) return;
        
        int pos = -1;
        for (int i = 1; i <= cnt; i++) {
            if (arr[i] == x) {
                pos = i;
                break;
            }
        }
        
        if (pos == -1) return;
        
        in_heap[x] = false;
        arr[pos] = arr[cnt--];
        
        for (int i = pos, j = i << 1; j <= cnt; i = j, j <<= 1) {
            if (j + 1 <= cnt && arr[j + 1] < arr[j]) j++;
            if (arr[j] < arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
        
        for (int i = pos, j = i >> 1; j; i = j, j >>= 1) {
            if (arr[j] > arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
    }
};

struct MaxHeap {
    int arr[MAXN], cnt;
    bool in_heap[MAXN];
    
    MaxHeap() {
        cnt = 0;
        for (int i = 0; i < MAXN; i++) {
            in_heap[i] = false;
        }
    }
    
    void push(int x) {
        if (in_heap[x]) return;
        arr[++cnt] = x;
        in_heap[x] = true;
        
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
        in_heap[arr[1]] = false;
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
    
    bool contains(int x) {
        return in_heap[x];
    }
    
    void remove(int x) {
        if (!in_heap[x]) return;
        
        int pos = -1;
        for (int i = 1; i <= cnt; i++) {
            if (arr[i] == x) {
                pos = i;
                break;
            }
        }
        
        if (pos == -1) return;
        
        in_heap[x] = false;
        arr[pos] = arr[cnt--];
        
        for (int i = pos, j = i << 1; j <= cnt; i = j, j <<= 1) {
            if (j + 1 <= cnt && arr[j + 1] > arr[j]) j++;
            if (arr[j] > arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
        
        for (int i = pos, j = i >> 1; j; i = j, j >>= 1) {
            if (arr[j] < arr[i]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            } else break;
        }
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
        if (x > current_floor) {
            up_requests.remove(x);
        } else {
            down_requests.remove(x);
        }
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
            } else {
                direction = -1; // reverse direction
                if (!down_requests.empty()) {
                    int next_floor = down_requests.top();
                    down_requests.pop();
                    current_floor = next_floor;
                }
            }
        } else { // going down
            if (!down_requests.empty()) {
                int next_floor = down_requests.top();
                down_requests.pop();
                current_floor = next_floor;
            } else {
                direction = 1; // reverse direction
                if (!up_requests.empty()) {
                    int next_floor = up_requests.top();
                    up_requests.pop();
                    current_floor = next_floor;
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
