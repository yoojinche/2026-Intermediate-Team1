#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
vector<int> tree;

int buildTree(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }

    int mid = (start + end) / 2;

    return tree[node] = buildTree(node * 2, start, mid)
                      + buildTree(node * 2 + 1, mid + 1, end);
}

void update(int node, int start, int end, int index, int diff) {
    if (index < start || end < index) {
        return;
    }

    tree[node] += diff;

    if (start == end) {
        return;
    }

    int mid = (start + end) / 2;

    update(node * 2, start, mid, index, diff);
    update(node * 2 + 1, mid + 1, end, index, diff);
}

int query(int node, int start, int end, int left, int right) {
    if (end < left || right < start) {
        return 0;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    return query(node * 2, start, mid, left, right)
         + query(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    arr.resize(n);
    tree.resize(n * 4);

    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;

        arr[i] = value % 2;
    }

    buildTree(1, 0, n - 1);

    int m;
    cin >> m;

    while (m--) {
        int command, b, c;
        cin >> command >> b >> c;

        if (command == 1) {
            int index = b - 1;
            int newParity = c % 2;

            if (arr[index] != newParity) {
                int diff = newParity - arr[index];

                arr[index] = newParity;
                update(1, 0, n - 1, index, diff);
            }
        } else if (command == 2) {
            int left = b - 1;
            int right = c - 1;

            int oddCount = query(1, 0, n - 1, left, right);
            int totalCount = c - b + 1;

            cout << totalCount - oddCount << '\n';
        } else if (command == 3) {
            int left = b - 1;
            int right = c - 1;

            cout << query(1, 0, n - 1, left, right) << '\n';
        }
    }

    return 0;
}
