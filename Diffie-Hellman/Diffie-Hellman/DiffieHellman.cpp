#include <iostream>
#include <fstream>

using namespace std;

int modular(int, unsigned int, unsigned int);								//need a function to compute very large int power int modulo int

void main()
{
	int p;
	int g;
	int nprime;
	int Sa;
	int Sb;
	int Ta;
	int Tb;
	int akey;
	int bkey;

	fstream x;
	

	cout << "Pick a nth prime(n<10,000) for p: ";
	cin >> nprime;
	x.open("1st-10k-prime.txt");
	for (int i = 0; i < nprime-1; i++)
	{
		int tmp;
		x >> tmp;
	}
	x >> p;
	x.close();																//close file to reset >> operator to the begining of the file

	cout << "The " << nprime << "th prime for p is " << p;

	cout << endl << "Pick a nth prime(n<10,000) for q: ";
	cin >> nprime;

	x.open("1st-10k-prime.txt");
	for (int j = 0; j < nprime-1; j++)
	{
		int tmp2;
		x >> tmp2;
	}
	x >> g;
	x.close();

	cout << "The " << nprime << "th prime for g is " << g << endl<<endl;				//This section ask user to pick primes and integer values

	cout << "User A pick a integer in the range of 1-100: ";
	cin >> Sa;

	cout << "User B pick a integer in the range of 1-100: ";
	cin >> Sb;

	Ta = modular(g, Sa, p);
	Tb = modular(g, Sb, p);

	cout << endl << "User A sends (" << g << "^" << Sa << ") % " << p << " = " << Ta << " to user B.";								//This section displays what the users are computing and sending
	cout << endl << "User B sends (" << g << "^" << Sb << ") % " << p << " = " << Tb << " to user A." << endl << endl;
	
	akey = modular(Tb, Sa, p);
	bkey = modular(Ta, Sb, p);

	cout << "User A computes (" << Tb << "^" << Sa << ") % " << p << " = " << akey << ", this is the secret key." << endl;				
	cout << "User B computes (" << Ta << "^" << Sb << ") % " << p << " = " << bkey << ", this is the secret key." << endl<<endl;		
	cout << "Both of the secret key above should match." << endl;
	system("pause");
}

int modular(int base, unsigned int exp, unsigned int mod)			//Function that uses a technique for modulo exponentiation
{
	int x = 1;
	int i;
	int power = base % mod;

	for (i = 0; i < sizeof(int) * 8; i++) 
	{
		int least_sig_bit = 0x00000001 & (exp >> i);
		if (least_sig_bit)											//Splitting up the base and mod it to reduce size of base^exp
			x = (x * power) % mod;
		power = (power * power) % mod;
	}

	return x;
}