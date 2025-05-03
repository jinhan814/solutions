#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];
		vector comp = v;
		sort(comp.begin(), comp.end());
		comp.erase(unique(comp.begin(), comp.end()), comp.end());
		auto res = 0LL;
		vector cnt(comp.size(), 0);
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int d = v[j] - v[i];
				auto it = lower_bound(comp.begin(), comp.end(), v[i] - d);
				if (it == comp.end() || *it != v[i] - d) continue;
				res += cnt[it - comp.begin()];
			}
			auto it = lower_bound(comp.begin(), comp.end(), v[i]);
			cnt[it - comp.begin()]++;
		}
		cout << res << '\n';
	}
}