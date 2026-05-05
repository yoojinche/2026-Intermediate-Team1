#include <iostream>
#include <algorithm> 

using namespace std;

long long arr[1000001];
long long tree[4000004];

void update(int node, int start, int end, int index, long long diff) {
    if (index < start || index > end) return;

    tree[node] += diff;

    if (start != end) {
        int mid = (start + end) / 2;
        update(node * 2, start, mid, index, diff);
        update(node * 2 + 1, mid + 1, end, index, diff);
    }
}

long long sum(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 0;

    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return sum(node * 2, start, mid, left, right) + sum(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int cmd;
        long long a, b;
        cin >> cmd >> a >> b;

        if (cmd == 0) {
            if (a > b) {
                swap(a, b);
            }
            cout << sum(1, 1, n, a, b) << "\n";

        }
        else if (cmd == 1) {
            long long diff = b - arr[a]; 
            arr[a] = b;
            update(1, 1, n, a, diff);
        }
    }

    return 0;
}