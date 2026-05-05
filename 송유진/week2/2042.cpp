#include <iostream>
#include <vector>
using namespace std;

long long arr[1000001];
long long tree[4000004];

long long init(int node, int start, int end) {
	if (start == end) {
		return tree[node] = arr[start];
	}
	int mid = (start + end) / 2;
	return tree[node] = init(node * 2, start, mid) + init(node * 2 + 1, mid + 1, end);
}

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

	int n, m, k;
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}

	init(1, 1, n);

	for (int i = 0; i < m + k; i++) {
		long long a, b, c;
		cin >> a >> b >> c;

		if (a == 1) {
			long long diff = c - arr[b];
			arr[b] = c;
			update(1, 1, n, b, diff);
		}
		else if (a == 2) {
			cout << sum(1, 1, n, b, c) << "\n";
		}
	}

	return 0;
}