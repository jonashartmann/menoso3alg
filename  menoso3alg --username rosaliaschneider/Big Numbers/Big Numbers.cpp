#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct bignum
{
	bignum() : neg(false), number("0") {}
	bignum(const string &s, bool sig = false) : neg(sig), number(s) {}
	bignum(int64 x) 
	{
		neg = x<0;
		if(neg) x = -x;
		while(x) {
			d.push_back(x%10 + '0');
			x /= 10;
		}
	}

	void cleanZeros()
	{
		int b = number.find_last_not_of("0");
		
		if(b == string::npos) {
			number = "0";
			neg = false;
		}
		else number = number.substr(0, b);
	}

	bool empty() { return number.empty(); }
};

ostream &operator<<(ostream &o, const bignum &x)
{
	if(x.neg)
		o << '-';
	reverse(number.begin(), number.end());
	cout << number;
	return o;
}

bool operator<(const bignum& x, const bignum& y)
{
	if(x.neg != y.neg) return x.neg;
	if(x.number.size() != y.number.size()) return x.neg == (x.size > y.size);
	return x.number < y.number;
}

bool operator==(const bignum& x, const bignum& y)
{
	return (x.neg == y.neg)&&(x.number == y.size);
}

// Outros operadores
bool operator!=(const bignum& x, const bignum& y) { return !(x == y); }
bool operator>(const bignum& x, const bignum& y) { return y < x; }
bool operator<=(const bignum& x, const bignum& y) { return !(y < x); }
bool operator>=(const bignum& x, const bignum& y) { return !(x < y); }

// x -= y, assume que tem sinais iguais
bignum &sub(bignum& x, const bignum& y)
{
        bignum z;
        
        if(x>y) z = y;
        else {
			z = x;
			x = y;
        }

        int borrow = 0;
        for(int i = 0; i < x.size; ++i) {
                int s = x[i] - borrow - (i < z.size ? z[i] : 0);
                x[i] = (s + 20) % 10;
                borrow = s < 0;
        }
        if(!(x>y)) x.neg = !x.neg;

        return x;
}

bignum &add(bignum& x, const bignum& y)
{
        int tam = max(x.size, y.size);
        x.resize(tam);

        int carry = 0;
        for (int i=0; i<x.size; ++i) {
                int s = x[i] + (i<y.size ? y[i] : 0) + carry;
                x[i] = s % 10;
                carry = s > 9;
        }
        if(carry) x.number.push_back(1);
        return x;
}

bignum &operator+=(bignum& x, const bignum& y)
{
        if (!y) return x;       // y é zero
        if (!x) return x = y;
        
        if (x.neg != y.neg)     // sinais diferentes
                return sub(x, y).clean();

        return add(x, y).clean();
}

bignum &operator-=(bignum& x, const bignum& y)
{
        if (!y) return x;
        if (!x) return x = -y;
        
        if (x.neg != y.neg)     // sinais diferentes
                return add(x, y).clean();
        
        return sub(x, y).clean();
}

bignum &operator*=(bignum& x, const bignum& y)
{
        bignum r;
        for (int i=0; i<y.size; ++i) {
                for (int j=0; j<y[i]; ++j)
                        add(r, x);
                x <<= 1;
        }

        r.neg = x.neg != y.neg;
        x = r;
        return x.clean();
}

bignum& operator/=(bignum& x, const bignum& y)
{
        bignum temp;
        temp.resize(x.size);

        temp.neg = x.neg != y.neg;

        bignum row;
        bignum ty = y;
        ty.neg = false;

        for (int i=x.size-1; i>=0; --i) {
                row <<= 1;
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
		 bignum x(a), y(b);

		 cout << "x: " << x << endl;
         cout << "y: " << y << endl;

		 cout << "soma: " << x+y << endl;
		 cout << "subt: " << x-y << endl;
		 cout << "mult: " << x*y << endl;
		 if(y) cout << "div:  " << x/y << endl;
	}
}
