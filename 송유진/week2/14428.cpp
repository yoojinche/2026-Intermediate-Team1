#include <iostream>
#include <vector>

using namespace std;

long long arr[100001];
int tree[400004]; 

int get_min_index(int a, int b) {
    if (a == 0) return b; 
    if (b == 0) return a; 
    if (arr[a] == arr[b]) return a < b ? a : b; 
    return arr[a] < arr[b] ? a : b; 
}

int init(int node, int start, int end) {
    if (start == end) return tree[node] = start; 
    int mid = (start + end) / 2;
    return tree[node] = get_min_index(init(node * 2, start, mid),
        init(node * 2 + 1, mid + 1, end));
}

int update(int node, int start, int end, int index, long long val) {
    if (index < start || index > end) return tree[node];

    if (start == end) return tree[node]; 

    int mid = (start + end) / 2;
    return tree[node] = get_min_index(update(node * 2, start, mid, index, val),
        update(node * 2 + 1, mid + 1, end, index, val));
}

int query(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 0; 
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return get_min_index(query(node * 2, start, mid, left, right),
        query(node * 2 + 1, mid + 1, end, left, right));
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;

    arr[0] = 1e18;

    for (int i = 1; i <= n; i++) cin >> arr[i];

    init(1, 1, n);

    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int cmd; cin >> cmd;
        if (cmd == 1) {
            int a; long long b; cin >> a >> b;
            arr[a] = b; 
            update(1, 1, n, a, b); 
        }
        else if (cmd == 2) {
            int a, b; cin >> a >> b;
            cout << query(1, 1, n, a, b) << "\n";
        }
    }
    return 0;
}