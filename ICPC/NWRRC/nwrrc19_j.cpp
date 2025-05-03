#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 10;
int add(int a, int b) { return a + b < mod ? a + b : a + b - mod; }
int sub(int a, int b) { return a < b ? a - b + mod : a - b; }
int mul(int a, int b) { return a * b % mod; }

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector eq(n, vector(2 * n, 0));
	for (int i = 0; i < n; i++) {
		string s; cin >> s;
		for (int j = 0; j < n; j++) eq[i][j] = s[j] - 48;
		eq[i][i]++;
		eq[i][n + i]++;
	}
	for (int rank = 0; rank < n; rank++) {
		for (int i = 0; i < rank; i++) {
			int x = eq[i][rank];
			for (int j = 0; j < 2 * n; j++) {
				int val = mul(eq[rank][j], x);
				eq[i][j] = sub(eq[i][j], val);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int val = sub(0, eq[i][n + j]);
			if (i == j) val = add(val, 1);
			cout << val;
		}
		cout << '\n';
	}
}