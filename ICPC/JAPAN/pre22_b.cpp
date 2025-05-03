#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	for (int n; cin >> n && n;) {
		vector v(n, vector{ 0, 0 });
		for (int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (v[i][0] != v[i][1]) continue;
			v[i].clear();
			cnt++;
		}
		int res = 0, p = 0;
		while (cnt < n) {
			if (v[p].empty()) { p = ++p % n; continue; }
			int x = p;
			while (v[p = ++p % n].empty());
			sort(v[x].begin(), v[x].end());
			auto it = find(v[p].begin(), v[p].end(), v[x][0]);
			if (it != v[p].end()) v[p].erase(it), cnt++;
			else v[p].push_back(v[x][0]);
			v[x].erase(v[x].begin());
			res++;
		}
		cout << res << '\n';
	}
}