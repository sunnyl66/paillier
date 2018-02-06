#include <iostream>
#include <math.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

using namespace std;

int moddiv(int x, int y){
  int ans = 0;
  ans = x%y;

  //cout << ans << endl;
  return ans;
}
int inverseMod(int x, int y){

  assert(__gcd(x,y) == 1);

  //cout << "GCD = 1 Inverse Mod Calculation Continues" << endl;

  int ans;
  for (int i = 0; i < y ; i ++){
    if(moddiv(i*x,y) == 1){
      ans = i;
      //cout << "Inverse is " << ans << endl;
    }
  }
  return ans;

}

int lcm(int x, int y){


  int ans = (x * y) / (__gcd(x,y));

  return ans;

}
int getRandom_G(int x){


  srand(time(NULL));
  int ans = rand() % x + 1;

  return ans;

}
float L_function(int x,int n){
  float ans = (x-1)/n;
  return ans;

}

int encrypt(int m, int n, int g){

  assert(0 <= m && m < n);
  int c;

  srand(time(NULL));
  int r = rand() % n;
  cout << "r = " << r << endl;

  c = moddiv( pow(g,m)*pow(r,n)   , pow(n,2)  );

  return c;
}

int decrypt(int c, int lambda, int mu, int n){
  int m;
  m = L_function(moddiv(pow(c,lambda),pow(n,2)), n) * moddiv(mu,n);

  return m;

}

int main(){
  cout << "Pallier cryptosystem begins" << endl;

  cout << "Key Generation Process" << endl;
  //choose two large prime numbers
  int p = 43;
  int q = 41;

  cout << "inputs p = " << p << "and q = " << q << " have been selected" << endl;


  assert(__gcd(p*q,(p-1)*(q-1)) == 1);

  cout << "\tp and q inputs satisfy gcd 1 property(wiki)... program continues" << endl;

  int n = p * q;
  int lambda = lcm(p-1,q-1);

  //select randoom inter g where g belongs to Z* n^2
  int g = getRandom_G(pow(n,2));
  g = 55;
  //inverseMod(3,11);

  //int mu = inverseMod(L_function(pow(g,lambda),pow(n,2)),n);


  long a1 = moddiv(pow(g,lambda),pow(n,2));
   a1 = (pow(3,4));

  cout << "a1 " << a1 << endl;
  int a2 = L_function(a1,n);
  cout << "a2 " << a2 << endl;
  int a3 = inverseMod(a2,n);
  cout << "a3 " << a3 << endl;

  int mu = inverseMod(L_function(moddiv(pow(g,lambda), pow(n,2)),n),n);


  cout << "p = " << p << endl;
  cout << "q = " << q << endl;
  cout << "n = " << n << endl;
  cout << "lamdba = " << lambda << endl;
  cout << "g = " << g << endl;
  cout << "mu = " << mu << endl << endl;;

  cout << "Encryption Process" << endl;
  int m = 15;
  cout << "Message m = " << m << endl;
  int c = encrypt(m,n,g);
  cout << "ciphertext c = " << c << endl << endl;
  cout << "Decryption Process" << endl;
  int m1 = decrypt(c,lambda,mu,n);
  cout << "Message m recovered to be= " << m1 << endl;


  return 0;
}
