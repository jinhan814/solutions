#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, k; cin >> n >> k;
	vector v(n, 0.);
	for (int i = 0; i < n; i++) cin >> v[i], v[i] /= 100;
	auto calc = [&](int i) {
		double res = v[i] * k / n, p = 1. * k / n;
		int a = n - k, b = n - 1;
		while (a) {
			i = i ? i - 1 : n - 1;
			p = p * a-- / b--;
			res += v[i] * p;
		}
		return res;
	};
	cout << fixed << setprecision(10);
	for (int i = 0; i < n; i++) cout << 100 * calc(i) << ' ';
	cout << '\n';
}