#include <iostream>
#include <vector>

using namespace std;
#define MOD 1000000007

long long arr[1000001];
long long tree[4000004];

long long init(int node, int start, int end) {
    if (start == end) return tree[node] = arr[start];
    int mid = (start + end) / 2;
    return tree[node] = (init(node * 2, start, mid) * init(node * 2 + 1, mid + 1, end)) % MOD;
}

long long update(int node, int start, int end, int index, long long val) {
    if (index < start || index > end) return tree[node];

    if (start == end) return tree[node] = val;

    int mid = (start + end) / 2;
    return tree[node] = (update(node * 2, start, mid, index, val) *
        update(node * 2 + 1, mid + 1, end, index, val)) % MOD;
}

long long multiply(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 1;

    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return (multiply(node * 2, start, mid, left, right) *
        multiply(node * 2 + 1, mid + 1, end, left, right)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) cin >> arr[i];
    init(1, 1, n);

    for (int i = 0; i < m + k; i++) {
        int a, b; long long c;
        cin >> a >> b >> c;
        if (a == 1) {
            arr[b] = c;
            update(1, 1, n, b, c); 
        }
        else if (a == 2) {
            cout << multiply(1, 1, n, b, c) << "\n";
        }
    }
    return 0;
}