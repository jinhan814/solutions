#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

auto sol = [](int n, string s) {
	vector p(n + 1, n);
	for (int i = 0; i < n; i++) {
		p[i + 1] = p[i];
		if (s[i] == '(' || s[i] == '{') p[i + 1]++;
		if (s[i] == ')' || s[i] == '}') p[i + 1]--;
	}
	vector c(2 * n + 2, 0);
	vector v(n + 1, 0);
	for (int i = 0; i <= n; i++) c[p[i] + 1]++;
	for (int i = 1; i <= 2 * n; i++) c[i] += c[i - 1];
	for (int i = 0; i <= n; i++) v[c[p[i]]++] = i;
	vector nxt(n + 1, -1);
	i64 ret = 0;
	for (int x = 2 * n; x > 0; x--) {
		for (int i = c[x - 1]; i < c[x];) {
			int j = i + 1;
			while (j < c[x]) {
				int l = v[j - 1];
				int r = v[j] - 1;
				if (s[l] != '(' && s[l] != '{') break;
				if (s[l] == '(' && s[r] != ')') break;
				if (s[l] == '{' && s[r] != '}') break;
				if (l + 1 < r && nxt[l + 1] != r - 1) break;
				nxt[v[i]] = r;
				ret += j - i;
				j++;
			}
			i = j;
		}
	}
	return ret;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	for (int tc_num = 1; tc_num <= tc; tc_num++) {
		int n; cin >> n;
		string s; cin >> s;
		cout << "Case #" << tc_num << '\n';
		cout << sol(n, s) << '\n';
	}
}