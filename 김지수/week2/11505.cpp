#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

const ll MOD = 1000000007;

vector<ll> arr;
vector<ll> tree;

ll buildTree(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start] % MOD;
    }

    int mid = (start + end) / 2;

    ll leftValue = buildTree(node * 2, start, mid);
    ll rightValue = buildTree(node * 2 + 1, mid + 1, end);

    return tree[node] = (leftValue * rightValue) % MOD;
}

ll update(int node, int start, int end, int index, ll value) {
    if (index < start || end < index) {
        return tree[node];
    }

    if (start == end) {
        return tree[node] = value % MOD;
    }

    int mid = (start + end) / 2;

    ll leftValue = update(node * 2, start, mid, index, value);
    ll rightValue = update(node * 2 + 1, mid + 1, end, index, value);

    return tree[node] = (leftValue * rightValue) % MOD;
}

ll query(int node, int start, int end, int left, int right) {
    if (end < left || right < start) {
        return 1;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    ll leftValue = query(node * 2, start, mid, left, right);
    ll rightValue = query(node * 2 + 1, mid + 1, end, left, right);

    return (leftValue * rightValue) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    arr.resize(n + 1);
    tree.resize(n * 4);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    buildTree(1, 1, n);

    for (int i = 0; i < m + k; i++) {
        int command, b;
        ll c;

        cin >> command >> b >> c;

        if (command == 1) {
            arr[b] = c;
            update(1, 1, n, b, c);
        } else if (command == 2) {
            cout << query(1, 1, n, b, c) << '\n';
        }
    }

    return 0;
}
