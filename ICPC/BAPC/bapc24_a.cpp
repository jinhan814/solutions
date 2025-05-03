#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector p(n + 1, 0), c(n + 1, 0);
	for (int i = 1; i <= n; i++) {
		string s; cin >> s;
		p[i] = i;
		c[i] = ranges::count(s, 'P');
	}
	for (int i = n; i >= 1; i--) {
		while (c[p[i]]--) {
			string s; cin >> s >> s;
			if (s[3] == 'w') continue;
			int j = i - (int)s.size() + 9;
			rotate(p.begin() + j, p.begin() + i, p.begin() + i + 1);
		}
	}
	int res = 1;
	while (p[res] != k) res++;
	cout << res << '\n';
}