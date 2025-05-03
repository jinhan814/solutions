#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	int res = s.size() > 1 ? s.size() - 1 : 1;
	for (int x = 1; x <= 9; x++) {
		string t = string(s.size(), x | 48);
		res += t.size() - (s < t);
	}
	cout << res << '\n';
}