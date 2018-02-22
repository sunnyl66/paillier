#include <NTL/ZZ_pXFactoring.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;
using namespace NTL;

/*
	To compile: 
	g++ -g -O2 main2.cpp -o main -lntl -lgmp -lm

	To run:
	./main
*/


/*
	To do list: 

	[x] moddiv - removed
	[ ] inverseMod - NTL might have
	[ ] lcm - NTL might have
	[ ] getRandom_G - use NTL for random
	[x] L_function
	[x] encrypt
	[x] decrypt
*/

ZZ L_function(ZZ x,ZZ n){
	ZZ ans;	// Return Value 
  
	ans = (x-1)/n;
  
	return ans;
}

ZZ encrypt(ZZ m, ZZ n, ZZ g)
{
	assert(0 <= m && m < n);
  	ZZ c;	// Return Value
  	ZZ r;	// Random Value

  	// Convert ZZ to long for power to work (might be a problem)
	long l_m; conv(l_m, m);
	long l_n; conv(l_n, n);

	// Create random # from 0 to n-1
	r = RandomBnd(n);
	cout << "r = " << r << endl;

	// Computes power of stuff
	ZZ pow_g_m; power(pow_g_m, g, l_m);	// g^m
	ZZ pow_r_n; power(pow_r_n, r, l_n);	// r^n
	ZZ pow_n_2; power(pow_n_2, n, 2);	// n^2

	// Does the encryption
	c = MulMod(pow_g_m, pow_r_n, pow_n_2);	// c = ( (g^m)*(r^n) ) / n^2

	return c;
}

ZZ decrypt(ZZ c, ZZ lambda, ZZ mu, ZZ n){
	ZZ m;	// Return Value

	// Convert ZZ to long for power to work (might be a problem)
	long l_lambda; conv(l_lambda, lambda);

	// Computes power of stuff
	ZZ pow_c_lambda; power(pow_c_lambda, c, l_lambda);	// c^lambda
	ZZ pow_n_2; power(pow_n_2, n, 2);	// n^2

	// Just to do c^lambda % n^2
	AddMod(pow_c_lambda, pow_c_lambda, 0, pow_n_2);

	// Decryption
	m = L_function(pow_c_lambda, n) * (mu%n);

	return m;
}

int main()
{
	ZZ m = ZZ(10);
	ZZ n = ZZ(1763);
	ZZ g = ZZ(107);
	
	cout << "m = " << m << endl;
	cout << "n = " << n << endl;
 	cout << "g = " << g << endl;
	
	ZZ c = encrypt(m, n, g);
	cout << "c = " << c << endl;

	return 0;
}
