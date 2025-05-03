#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, a, b; cin >> n >> a >> b;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];

	vector buc(0, array{ 0, 0, 0 });
	for (int i = 1; i < b; i++) buc.push_back({ 2, a, 0 });
	for (int i = b + 1; i <= n; i++) buc.push_back({ 0, a, 0 });
	for (int i = 1; i < a; i++) buc.push_back({ 1, 1, 0 });
	for (int i = a + 1; i <= n; i++) buc.push_back({ 3, 1, 0 });
	for (int i = 2; i <= n; i++) if (v[a - 1][i - 1] == '.') buc.push_back({ 1, i, 1 });
	for (int i = a - 1; i >= 1; i--) {
		for (int j = 2; j <= n; j++) buc.push_back({ 0, i, 0 });
		for (int j = 2; j <= n; j++) if (v[i - 1][j - 1] == '.') buc.push_back({ 1, j, 1 });
	}
	for (int i = a + 1; i <= n; i++) {
		for (int j = 2; j <= n; j++) buc.push_back({ 0, i, 0 });
		for (int j = 2; j <= n; j++) if (v[i - 1][j - 1] == '.') buc.push_back({ 3, j, 1 });
	}
	for (int i = 1; i <= n; i++) if (v[i - 1][0] == '.') buc.push_back({ 2, i, 1 });

	cout << buc.size() << '\n';
	for (auto [a, b, c] : buc) {
		cout << "RULD"[a] << ' ' << b << ' ';
		cout << (c ? "pull" : "push") << '\n';
	}
}