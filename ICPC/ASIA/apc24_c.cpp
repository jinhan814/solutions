#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector v(n, 0LL);
		for (int i = 0; i < n; i++) cin >> v[i];

		auto sol = [&] {
			if (n == 1) return (1LL << v[0]) - 1;
			int p = 1;
			for (int i = 2; i < n; i++)  if (v[p - 1] - v[p] < v[i - 1] - v[i]) p = i;
			auto k = v[p - 1] - v[p];
			auto x = ((1LL << v[p - 1] + 1) - 1) - (1LL << k + 1) - (p - 1);
			for (int i = 0; i < n; i++) {
				int cnt = __builtin_popcountll(x + i);
				if (cnt != v[i]) return -1LL;
			}
			return x;
		};

		auto res = sol();
		cout << res << '\n';
	}
}