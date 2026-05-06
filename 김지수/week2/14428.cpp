#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
vector<int> tree;

void init(int start, int end, int node) {
    if (start == end) {
        tree[node] = start;
        return;
    }

    int mid = (start + end) / 2;

    init(start, mid, node * 2);
    init(mid + 1, end, node * 2 + 1);

    if (arr[tree[node * 2]] <= arr[tree[node * 2 + 1]]) {
        tree[node] = tree[node * 2];
    } else {
        tree[node] = tree[node * 2 + 1];
    }
}

int query(int start, int end, int node, int left, int right) {
    if (left > end || right < start) {
        return -1;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    int m1 = query(start, mid, node * 2, left, right);
    int m2 = query(mid + 1, end, node * 2 + 1, left, right);

    if (m1 == -1) {
        return m2;
    }

    if (m2 == -1) {
        return m1;
    }

    if (arr[m1] <= arr[m2]) {
        return m1;
    } else {
        return m2;
    }
}

void update(int start, int end, int node, int index, int value) {
    if (index < start || end < index) {
        return;
    }

    if (start == end) {
        tree[node] = index;
        arr[index] = value;
        return;
    }

    int mid = (start + end) / 2;

    update(start, mid, node * 2, index, value);
    update(mid + 1, end, node * 2 + 1, index, value);

    if (arr[tree[node * 2]] <= arr[tree[node * 2 + 1]]) {
        tree[node] = tree[node * 2];
    } else {
        tree[node] = tree[node * 2 + 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    arr.resize(n + 1);
    tree.resize(n * 4);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    init(1, n, 1);

    int m;
    cin >> m;

    while (m--) {
        int command, b, c;
        cin >> command >> b >> c;

        if (command == 1) {
            update(1, n, 1, b, c);
        } else if (command == 2) {
            cout << query(1, n, 1, b, c) << '\n';
        }
    }

    return 0;
}
