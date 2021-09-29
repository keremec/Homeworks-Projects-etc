#include<iostream>
#include<cmath>

using namespace std;

int decToBin(int dec) {
	int rem, ctr = 0, bin = 0;
	while (dec != 0) {
		rem = dec % 2;
		bin += rem * (int)pow(10, ctr);
		dec = dec / 2;
		ctr++;
	}
	return bin;
	}
int howmanystep(int num) {
	int ctr=1;
	while (num != 0) {
		num = num / 10;
		ctr++;
	}
	return ctr;
}
int modExp(int b, int e, int m){
	int x = 1; int k = howmanystep(e); int a;
	int power = b % m;	
	for (int i = 0; i < k - 1; i++) {
		a = ( e / (int)pow(10, i)) % 10;
		if (a == 1) {
			cout << "Because b" << i << " is 1, we have x = (" << x << " * " << power << ")";
			if (i !=k-2){ cout << " and power = " << power << " ^ 2 mod " << m << " = "; }
			x = (x * power) % m;
			}
		else {
			cout << "Because b" << i << " is 0, we have x = " << x;
			if (i != k - 2) { cout << " and power = " << power << " ^ 2 mod " << m << " = "; }
		}
		power = (power * power) % m;
		if (i != k - 2){ cout << power << endl; }
		else { cout << " mod " << m <<" ==>" << endl; }
	}	
		return x;
}
	
int main() {
	int a, b, bt, m, rslt;
	cout << "MODULAR EXPONENTIATION CALCULATOR" << endl;
	cout << "(a^b mod m solver)\n" << endl;
	cout << "Enter Base (a): "; cin >> a;
	cout << "Enter Exponent (b): "; cin >> bt; b = bt;
	cout << "Enter Modulus (m): "; cin >> m;
	cout << "\n";
	cout << b << " is equivalent to ("; b = decToBin(b); cout << b << ") as binary number...\n" << endl;
	rslt = modExp(a, b, m);
	cout << "\n";
	cout << "Modular Exponentiation of (" << a << "^" << bt << ") mod (" << m << ") = " << rslt;
	return 0;
}