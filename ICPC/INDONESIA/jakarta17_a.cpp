#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(m, 0);
	for (int i = 0; i < m; i++) cin >> v[i];
	int a = -1, b = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < m; j++) {
			int x; cin >> x;
			if (v[j] == x) cnt++;
		}
		if (a < cnt) a = cnt, b = i + 1;
	}
	cout << b << '\n';
}