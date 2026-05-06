#include <iostream>
#include <vector>

using namespace std;

const long long MOD = 1000000007;

vector<long long> arr;
vector<long long> tree;

// 세그먼트 트리 만들기
long long build(int node, int start, int end) {
    if (start == end) {
        return tree[node] = arr[start];
    }

    int mid = (start + end) / 2;

    long long left = build(node * 2, start, mid);
    long long right = build(node * 2 + 1, mid + 1, end);

    return tree[node] = (left * right) % MOD;
}

// 값 변경
long long update(int node, int start, int end, int index, long long value) {
    if (index < start || index > end) {
        return tree[node];
    }

    if (start == end) {
        arr[index] = value;
        return tree[node] = value;
    }

    int mid = (start + end) / 2;

    long long left = update(node * 2, start, mid, index, value);
    long long right = update(node * 2 + 1, mid + 1, end, index, value);

    return tree[node] = (left * right) % MOD;
}

// 구간 곱 구하기
long long query(int node, int start, int end, int left, int right) {
    // 아예 안 겹침
    if (right < start || end < left) {
        return 1;
    }

    // 완전히 포함됨
    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = (start + end) / 2;

    long long leftResult = query(node * 2, start, mid, left, right);
    long long rightResult = query(node * 2 + 1, mid + 1, end, left, right);

    return (leftResult * rightResult) % MOD;
}

// B11505 - 구간 곱 구하기
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    arr.resize(N + 1);
    tree.resize(4 * N);

    for (int i = 1; i <= N; i++) {
        cin >> arr[i];
    }

    build(1, 1, N);

    for (int i = 0; i < M + K; i++) {
        int a, b;
        long long c;

        cin >> a >> b >> c;

        if (a == 1) {
            // b번째 수를 c로 변경
            update(1, 1, N, b, c);
        } else if (a == 2) {
            // b부터 c까지의 곱 출력
            cout << query(1, 1, N, b, c) << '\n';
        }
    }

    return 0;
}
