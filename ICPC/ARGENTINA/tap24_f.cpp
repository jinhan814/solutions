#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, 0);
	for (int i = 0; i < n; i++) cin >> v[i];
	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] > 0) x++;
		if (i > 1 && v[i - 2] == 1 && v[i - 1] == 1 && v[i] == 1) y++;
	}
	cout << 2 * x + y - n << '\n';
}