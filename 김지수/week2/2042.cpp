#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

vector<ll> arr;
vector<ll> tree;

ll mergeValue(ll left, ll right) {
    return left + right;
}

ll buildTree(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }

    int mid = start + (end - start) / 2;

    ll leftSum = buildTree(node * 2, start, mid);
    ll rightSum = buildTree(node * 2 + 1, mid + 1, end);

    return tree[node] = mergeValue(leftSum, rightSum);
}

ll query(int node, int start, int end, int left, int right) {
    if (end < left || right < start) {
        return 0;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = start + (end - start) / 2;

    ll leftSum = query(node * 2, start, mid, left, right);
    ll rightSum = query(node * 2 + 1, mid + 1, end, left, right);

    return mergeValue(leftSum, rightSum);
}

ll update(int node, int start, int end, int index, ll value) {
    if (index < start || end < index) {
        return tree[node];
    }

    if (start == end) {
        return tree[node] = value;
    }

    int mid = start + (end - start) / 2;

    ll leftSum = update(node * 2, start, mid, index, value);
    ll rightSum = update(node * 2 + 1, mid + 1, end, index, value);

    return tree[node] = mergeValue(leftSum, rightSum);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    arr.resize(n);
    tree.resize(n * 4);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    buildTree(1, 0, n - 1);

    for (int i = 0; i < m + k; i++) {
        int command;
        int b;
        ll c;

        cin >> command >> b >> c;

        if (command == 1) {
            update(1, 0, n - 1, b - 1, c);
        } else {
            cout << query(1, 0, n - 1, b - 1, c - 1) << '\n';
        }
    }

    return 0;
}
