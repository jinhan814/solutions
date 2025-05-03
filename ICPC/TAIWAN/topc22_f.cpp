#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	map m{ pair(string{}, 0) };
	for (int i = 0; i < 6; i++) {
		string s; cin >> s;
		int a, b, c, d, e; cin >> a >> b >> c >> d >> e;
		m[s] = 56 * a + 24 * b + 14 * c + 6 * d + 30 * e;
	}
	int cnt = 0;
	for (auto [a, b] : m) if (b > m["Taiwan"]) cnt++;
	cout << n / 6 + (cnt < n % 6) << '\n';
}