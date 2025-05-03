#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
	int l = a + b + c + d + e;
	int r = 4 * a + 6 * b + 8 * c + 12 * d + 20 * e;
	int x = l + r >> 1, y = l + r + 1 >> 1;
	cout << x << ' ';
	if (x != y) cout << y << ' ';
	while (x != l) cout << --x << ' ' << ++y << ' ';
}