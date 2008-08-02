#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

struct bignum
{
	bool neg;
	string number;

	bignum(long long x = 0) : number("")
	{
		neg = x<0;
		if(neg) x = -x;
		while(x) {
			number += char(x%10+'0');
			x /= 10;
		}
	}
    bignum(const string &s)
	{
		for(int i = s.size()-1; i > 0; --i) number += s[i];
		neg = s[0] == '-';
		if(!neg) number += s[0];
	}

	bignum &clean()
	{
		int b = number.find_last_not_of("0");
		number = number.substr(0, b);
		// zero nao eh negativo
		if(number.empty()) neg = false;
        return *this;
	}

	bool operator!() const { return number.empty(); }
	operator bool() const { return !number.empty(); }
	char operator[](int i) const { return number[i]; }
	char &operator[](int i) { return number[i]; }
    inline int size() const { return number.size(); }
};

ostream &operator<<(ostream &o, const bignum &x)
{
	if(!x) return o << 0;

	if(x.neg) o << '-';
	for(int i = x.size()-1; i >=0; --i) o << x.number[i];
	return o;
}

bool operator<(const bignum& x, const bignum& y)
{
	if(x.neg != y.neg) return x.neg;
	if(x.size() != y.size()) return x.neg == (x.size() > y.size());
	
	for(int i = x.size()-1; i >= 0; --i) {
		if(x[i] != y[i]) {
			return x.neg != (x[i] < y[i]);
		}
	}
	return false;
}

bool operator==(const bignum& x, const bignum& y)
{
	return (x.neg == y.neg)&&(x.number == y.number);
}

// variacoes dos operadores de comparação
bool operator!=(const bignum &x, const bignum &y) { return !(x == y); }
bool operator>(const bignum &x, const bignum &y) { return y < x; }
bool operator<=(const bignum &x, const bignum &y) { return !(y < x); }
bool operator>=(const bignum &x, const bignum &y) { return !(x < y); }

// assume que tem sinais iguais
bignum &add(bignum &x, const bignum &y)
{
	int tam = max(x.size(), y.size());
	for(int i = 0; i < tam; ++i) x.number += '0';

	int carry = 0;
	for(int i = 0; i < x.size(); ++i) {
		int s = x[i]-'0' + (i < y.size()? y[i]-'0' : 0) + carry;
		x[i] = (s%10)+'0';
        carry = s > 9;
	}
	if(carry) x.number += '1';
	return x;
}

// assume que tem sinais iguais
bignum &sub(bignum &x, const bignum &y)
{
	bignum z;

	if(x > y) z = y;
	else {
		z = x;
		x = y;
		// n eh usado na subtracao
		x.neg = !x.neg;
	}
	
	int borrow = 0;
    for(int i = 0; i < x.size(); ++i) {
		int s = (x[i]-'0') - borrow - ((i < z.size())? (z[i]-'0') : 0);
		x[i] = ((s + 20)%10) + '0';
		borrow = s < 0;
	}
	return x;
}

bignum& operator+=(bignum& x, const bignum& y)
{
	if(!y) return x;
	if(!x) return x = y;

	if(x.neg != y.neg) return sub(x, y).clean();
	return add(x, y).clean();
}

bignum& operator-=(bignum& x, const bignum& y)
{
	if(!y) return x;
	if(!x) return x = -y;

	if(x.neg != y.neg)  return add(x, y).clean();
	return sub(x, y).clean();
}

bignum& operator*=(bignum& x, const bignum& y)
{
	bignum r;
	for(int i = 0; i < y.size(); ++i) {
		for(int j = 0; j < y[i]; ++j) {
			add(r, x);
            x.number = '1'+x.number;
        }
	}
	r.neg = x.neg != y.neg;
	x = r;
	return x.clean();
}

// FAZER
bignum& operator/=(bignum& x, const bignum& y)
{
	bignum temp;
	//temp.resize(x.size);

	temp.neg = x.neg != y.neg;

	bignum row;
	bignum ty = y;
	ty.neg = false;

	for (int i=x.size()-1; i>=0; --i) {
			//row <<= 1;
			row[0] = x[i];
			row.clean();
			while (ty <= row) {
					++temp[i];
					sub(row, ty).clean();
			}
	}
	return (x = temp).clean();
}

bignum operator+(const bignum& a, const bignum& b)
{
	bignum c = a;
	return c += b;
}

bignum operator-(const bignum& a, const bignum& b)
{
	bignum c = a;
	return c -= b;
}

bignum operator*(const bignum& a, const bignum& b)
{
	bignum c = a;
	return c *= b;
}

bignum operator/(const bignum& a, const bignum& b)
{
	bignum c = a;
	return c /= b;
}

int main()
{
	string a, b;

	while(cin >> a >> b) {
		bignum a1(a), b1(b);
		cout << "soma: " << a1+b1 << endl;
		cout << "sub: " << a1-b1 << endl;
		cout << "mult: " << a1*b1 << endl;
	}
	return 0;
}
