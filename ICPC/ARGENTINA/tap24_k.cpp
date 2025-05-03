#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	int a = 0, b = 0, c = 0;
	for (int j = m - 1; j >= 0; j--) {
		for (int i = 0; i <= n - 4; i++) {
			if (v[i][j] != '#') continue;
			int cnt = 0;
			while (cnt < 5 && v[i + cnt][j] == '#') cnt++;
			if (cnt == 1) {
				a++;
				v[i][j - 2] = v[i][j - 1] = v[i][j] = '.';
				v[i + 1][j - 1] = '.';
				v[i + 2][j - 1] = '.';
				v[i + 3][j - 1] = '.';
				v[i + 4][j - 1] = '.';
			}
			else {
				cnt == 5 ? b++ : c++;
				v[i][j - 2] = v[i][j - 1] = v[i][j] = '.';
				v[i + 1][j - 2] = v[i + 1][j] = '.';
				v[i + 2][j - 2] = v[i + 2][j - 1] = v[i + 2][j] = '.';
				v[i + 3][j - 2] = '.';
				v[i + 4][j - 2] = '.';
				if (cnt == 5) {
					v[i + 3][j] = '.';
					v[i + 4][j] = '.';
				}
			}
		}
	}
	cout << a << ' ' << b << ' ' << c << '\n';
}