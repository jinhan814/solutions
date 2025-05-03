#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string res(10000, 0);
	for (int bit = 0; bit < 5; bit++) {
		string s;
		for (int i = 1; i <= 26; i++) if (i >> bit & 1) s.push_back(96 + i);
		cout << "? " << s << endl;
		int k, x; cin >> k;
		while (k--) cin >> x, res[x - 1] |= 1 << bit;
	}
	while (!res.back()) res.pop_back();
	for (char& c : res) c += 96;
	cout << "! " << res << '\n';
}