#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	if (n > 100) n = 100;
	vector a(101, 0.), b(101, 0.); a[1] = b[2] = 1;
	for (int i = 3; i <= 100; i++) {
		a[i] = a[i - 1] + a[i - 2];
		b[i] = b[i - 1] + b[i - 2];
		auto s = a[i] + b[i];
		a[i] /= s;
		b[i] /= s;
	}
	auto res = 100. * a[n] / (a[n] + b[n]);
	cout << fixed << setprecision(10);
	cout << res << ' ' << 100 - res << '\n';
}