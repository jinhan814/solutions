#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int m; cin >> m;
	auto rec = [&](const auto& self) -> pair<int, int> {
		int w, k; cin >> w >> k;
		int res = 0, rem = w;
		priority_queue<int> pq;
		while (k--) {
			auto [a, b] = self(self);
			res += a, rem += b;
			pq.push(b);
		}
		while (rem - w >= m) {
			res++, rem -= pq.top();
			pq.pop();
		}
		return pair(res + rem / m, rem % m);
	};
	auto [res, rem] = rec(rec);
	if (rem) res++;
	cout << res << '\n';
}