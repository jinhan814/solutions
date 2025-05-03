#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		string s; cin >> s;
		vector p(n + 1, 0);
		for (int i = 0; i < n; i++) p[i + 1] = p[i] + (s[i] == '(' ? 1 : -1);

		auto sol = [&] {
			int l = 0, r = n;
			while (l + 1 <= n && p[l + 1] >= 0) l++;
			while (r - 1 >= 0 && p[r - 1] >= 0) r--;
			for (int i = 0; i < n; i++) {
				int mx = max(p[i], p[i + 1]);
				for (int j = i + 2; j <= n; j++) {
					mx = max(mx, p[j]);
					if (i <= l && r <= j && p[i] + p[j] - mx >= 0) return pair(i + 1, j);
				}
			}
		};
		auto [a, b] = sol();
		cout << a << ' ' << b << '\n';
	}
}