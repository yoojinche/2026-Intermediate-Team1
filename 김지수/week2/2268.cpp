#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

struct IndexedTree {
    vector<ll> tree;
    int leafSize;

    IndexedTree(int n) {
        leafSize = 1;
        while (leafSize < n) {
            leafSize *= 2;
        }
        tree.resize(leafSize * 2, 0);
    }

    void update(int node, int left, int right, int index, ll diff) {
        if (index < left || right < index) {
            return;
        }

        tree[node] += diff;

        if (left == right) {
            return;
        }

        int mid = (left + right) / 2;
        update(node * 2, left, mid, index, diff);
        update(node * 2 + 1, mid + 1, right, index, diff);
    }

    ll query(int node, int left, int right, int qLeft, int qRight) {
        if (right < qLeft || qRight < left) {
            return 0;
        }

        if (qLeft <= left && right <= qRight) {
            return tree[node];
        }

        int mid = (left + right) / 2;

        return query(node * 2, left, mid, qLeft, qRight)
             + query(node * 2 + 1, mid + 1, right, qLeft, qRight);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> nums(n + 1, 0);
    IndexedTree indexedTree(n);

    for (int i = 0; i < m; i++) {
        int command, b;
        ll c;

        cin >> command >> b >> c;

        if (command == 0) {
            if (b > c) {
                swap(b, c);
            }

            cout << indexedTree.query(1, 1, indexedTree.leafSize, b, c) << '\n';
        } else {
            ll diff = c - nums[b];
            nums[b] = c;

            indexedTree.update(1, 1, indexedTree.leafSize, b, diff);
        }
    }

    return 0;
}
