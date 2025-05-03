#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s, t; cin >> s >> t;

	auto sol = [&]() -> bool {
		int i = 0;
		for (char c : t) {
			if (i == s.size()) return 0;
			if (s[i++] == c) continue;
			while (i < s.size() && s[i] == '0') i++;
			if (i++ == s.size()) return 0;
		}
		int acc = 0;
		while (i < s.size()) acc ^= s[i++] & 1;
		return !acc;
	};

	cout << (sol() ? "Yes" : "No") << '\n';
}