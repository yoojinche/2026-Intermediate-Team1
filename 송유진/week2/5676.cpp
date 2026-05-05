#include <iostream>
#include <vector>

using namespace std;

int arr[100001];
int tree[400004];

int get_sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

int init(int node, int start, int end) {
    if (start == end) return tree[node] = get_sign(arr[start]);
    int mid = (start + end) / 2;
    return tree[node] = init(node * 2, start, mid) * init(node * 2 + 1, mid + 1, end);
}

int update(int node, int start, int end, int index, int val) {
    if (index < start || index > end) return tree[node];
    if (start == end) return tree[node] = get_sign(val); 

    int mid = (start + end) / 2;
    return tree[node] = update(node * 2, start, mid, index, val) *
        update(node * 2 + 1, mid + 1, end, index, val);
}

int multiply(int node, int start, int end, int left, int right) {
    if (left > end || right < start) return 1; 
    if (left <= start && end <= right) return tree[node];

    int mid = (start + end) / 2;
    return multiply(node * 2, start, mid, left, right) *
        multiply(node * 2 + 1, mid + 1, end, left, right);
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, k;

    while (cin >> n >> k) {
        for (int i = 1; i <= n; i++) cin >> arr[i];
        init(1, 1, n);

        for (int i = 0; i < k; i++) {
            char cmd; int a, b;
            cin >> cmd >> a >> b;
            if (cmd == 'C') {
                arr[a] = b;
                update(1, 1, n, a, b);
            }
            else if (cmd == 'P') {
                int res = multiply(1, 1, n, a, b);
                if (res > 0) cout << '+';
                else if (res < 0) cout << '-';
                else cout << '0';
            }
        }
        cout << "\n";
    }
    return 0;
}