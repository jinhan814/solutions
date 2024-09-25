#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n; cin >> n;
	while (n--) {
		string s; cin >> s;
		int res = 0;
		for (int i = 0; i < s.size() - 1 - i; i++) {
			int a = s[i];
			int b = s[s.size() - 1 - i];
			res += abs(a - b);
		}
		cout << res << '\n';
	}
}