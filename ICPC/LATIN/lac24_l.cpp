#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	int res = 1;
	for (int i = 0; i < n; i++) {
		string s, t; cin >> s >> t;
		if (s.find('-') == -1) continue;
		if (t.find('*') == -1) continue;
		res = 0;
	}
	cout << "NY"[res] << '\n';
}