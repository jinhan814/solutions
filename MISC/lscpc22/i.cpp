#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k, d; cin >> n >> k >> d;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) cin >> b[i];

	priority_queue<int, vector<int>, greater<>> pq;
	for (int i = 1; i <= min(n, d); i++) pq.push(b[i]);
	for (int i = d + 1; i <= n; i++) pq.push(a[i]);

	int cnt = 0;
	while (cnt < d && pq.size()) {
		if (k < pq.top()) break;
		k -= pq.top(); pq.pop();
		cnt++;
	}
	cout << cnt << '\n';
}