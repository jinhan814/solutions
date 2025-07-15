#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](i64 n, i64 a, i64 b, int x) {
	int k = 1 << __lg(x | 1) + 1;
	auto calc = [&](i64 a, i64 b) {
		i64 bias = a / k * k;
		vector d(k, -1LL); d[a - bias] = 0;
		deque q(1, a);
		while (q.size()) {
			i64 cur = q.front(); q.pop_front();
			for (i64 nxt : { cur ^ x, (cur ^ x) + 1 }) {
				if (nxt >= n) continue;
				if (cur / k != nxt / k) continue;
				if (d[nxt - bias] != -1) continue;
				d[nxt - bias] = d[cur - bias] + 1;
				q.push_back(nxt);
			}
		}
		return d[b - bias];
	};
	if (a > b && a / k != b / k) return -1LL;
	if (a / k == b / k) return calc(a, b);
	i64 l = calc(a, (a / k * k + k - 1) ^ x) + 1;
	i64 m = calc(0, (k - 1) ^ x) + 1;
	i64 r = calc(b / k * k, b);
	if (l == -1 || r == -1) return -1LL;
	if (b / k - a / k > 1 && m == -1) return -1LL;
	return l + (b / k - a / k - 1) * m + r;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, a, b; cin >> n >> a >> b;
	int x; cin >> x;
	cout << sol(n, a, b, x) << '\n';
}