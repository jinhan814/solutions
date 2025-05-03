#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int x_mn = 1 << 30, y_mn = 1 << 30;
	int x_mx = -(1 << 30), y_mx = -(1 << 30);
	for (int i = 0; i < n; i++) {
		int x, y, h; cin >> x >> y >> h;
		x_mn = min(x_mn, x - h);
		y_mn = min(y_mn, y - h);
		x_mx = max(x_mx, x + h);
		y_mx = max(y_mx, y + h);
	}
	int x = x_mx + x_mn >> 1;
	int y = y_mx + y_mn >> 1;
	int h = max(x_mx - x_mn, y_mx - y_mn) + 1 >> 1;
	cout << x << ' ' << y << ' ' << h << '\n';
}