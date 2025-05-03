#include <bits/stdc++.h>
using namespace std;

struct vec {
	double x, y, z;
	double norm() const { return sqrt(x * x + y * y + z * z); }
	vec operator-() const { return vec{ -x, -y, -z }; }
	vec operator*(double v) const { return vec{ x * v, y * v, z * v }; }
	vec operator/(double v) const { return vec{ x / v, y / v, z / v }; }
	vec operator+(const vec& v) const { return vec{ x + v.x, y + v.y, z + v.z }; }
	vec operator-(const vec& v) const { return vec{ x - v.x, y - v.y, z - v.z }; }
	vec operator*(const vec& v) const { return vec{ x * v.x, y * v.y, z * v.z }; }
	vec operator^(const vec& v) const { return vec{ y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }
	friend istream& operator>>(istream& in, vec& v) { return in >> v.x >> v.y >> v.z; }
};

auto sol = [](vec n, vec v, vec h) {
	double l = v.norm();
	n = n / n.norm();
	v = v / v.norm();
	vec p = n ^ v;
	vec a = v; a = a * l;
	vec b = -v + p * sqrt(3); b = b / b.norm() * l;
	vec c = -v - p * sqrt(3); c = c / c.norm() * l;
	double r1 = (a - h).norm();
	double r2 = (b - h).norm();
	double r3 = (c - h).norm();
	return tuple(r1, r2, r3);
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		vec n, v; cin >> n >> v;
		double l, h; cin >> l >> h;
		auto [a, b, c] = sol(n, v, vec{ 0, 0, -h });
		cout << fixed << setprecision(6);
		cout << a << ' ' << b << ' ' << c << '\n';
	}
}