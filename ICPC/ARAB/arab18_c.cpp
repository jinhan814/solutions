#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		map v{ pair(string{}, array{ 0, 0, 0 }) };
		for (int i = 0; i < n; i++) {
			string s; cin >> s;
			int a, b, c; cin >> a >> b >> c;
			v[s] = { a, b, c };
		}
		for (int i = 0; i < m; i++) {
			string s, t, u; cin >> s >> t >> u;
			int res = v[u][t[0] == 's' ? 0 : t[0] == 'm' ? 1 : 2];
			res += 100 / m;
			if (res % 5 == 4) res++;
			if (res % 5 == 1) res--;
			cout << s << ' ' << res << '\n';
		}
	}
}