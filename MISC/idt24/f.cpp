#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, k; cin >> n >> k;
		vector a(n + 1, 0), b(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> a[i];
		for (int i = 1; i <= n; i++) cin >> b[i];

		auto check = [&](int s) -> bool {
			vector buc(0, pair(0, 0));
			vector idx(0, 0);
			for (int i = 1; i <= n; i++) {
				if (b[i] < s) continue;
				int l = a[i] - (b[i] - s);
				int r = a[i] + (b[i] - s);
				buc.push_back({ l, r + 1 }); // [l, r)
				idx.push_back(l);
				idx.push_back(r + 1);
			}

			sort(idx.begin(), idx.end());
			idx.erase(unique(idx.begin(), idx.end()), idx.end());
			for (auto& [a, b] : buc) {
				a = lower_bound(idx.begin(), idx.end(), a) - idx.begin() + 1;
				b = lower_bound(idx.begin(), idx.end(), b) - idx.begin() + 1;
			}

			vector psum(idx.size() + 1, 0);
			for (auto [a, b] : buc) psum[a]++, psum[b]--;
			for (int i = 1; i <= idx.size(); i++) psum[i] += psum[i - 1];
			return ranges::max(psum) <= k;
		};

		int lo = -1, hi = 1e9;
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (!check(mid)) lo = mid;
			else hi = mid;
		}
		cout << hi << '\n';
	}
}