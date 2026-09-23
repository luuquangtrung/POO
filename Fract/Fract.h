#ifndef _FRACT_H_
#define _FRACT_H_
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

// Fraction soit toujours valide b!=0
// Fraction à représentation unique: a et b premiers entre eux (pgdc(a,b)==1) et b>0 
class CFract
{
  int a, b;
  void Norm() // fraction simplifiée
  {
    if(a==0) {b=1; return;}
    if(b<0) {a=-a; b=-b;}
    bool neg=(a<0);
    if(neg) a=-a;
    int div=2;
    while(div<=__min(a,b))
    {
      if((a%div)==0 && (b%div==0)) {a/=div; b/=div;}
      else div++;
    }
    if(neg) a=-a;
  }
public:
  //CFract():a(0), b(1) { printf("Ctor 0 params: "); Affiche(); }
  //CFract(int _a, int _b):a(_a), b(_b) { printf("Ctor 2 params: "); Affiche(); }
  //CFract(int _a):a(_a), b(1) { printf("Ctor 1 params: "); Affiche(); }
  /*explicit*/ CFract(int _a=0, int _b=1):a(_a), b(_b?_b:1) { Norm(); printf("Ctor 0/1/2 params: "); Affiche(); }
  CFract(const CFract& f):a(f.a), b(f.b) { printf("Ctor de copie: "); Affiche(); }
  ~CFract() { printf("Dtor: "); Affiche(); }
  void Affiche() const { printf("CFract (%d/%d) @=%p\n",a,b,this); }
  const int& GetA() const { return a; }
  const int& GetB() const { return b; }
  void SetA(int _a) { a=_a; Norm(); }
  void SetB(int _b) { if(_b!=0) {b=_b; Norm();} }
  // attrib virtuels
  __declspec(property(get=GetA, put=SetA)) int A;
  __declspec(property(get=GetB, put=SetB)) int B;
  CFract& MultTo(const CFract& f) { a*=f.a; b*=f.b; Norm(); return *this;}
  CFract& AddTo(const CFract& f) { a=a*f.b+b*f.a; b*=f.b; Norm(); return *this;}
  CFract& SubTo(const CFract& f) { a=a*f.b-b*f.a; b*=f.b; Norm(); return *this;}
  //CFract operator+(const CFract& f) const { CFract c; c.a=a*f.b+b*f.a; c.b=b*f.b; c.Norm(); return c;}
  //CFract operator+(const CFract& f) const { return CFract(a*f.b+b*f.a,b*f.b);}
  //CFract operator+(const CFract& f) const { return CFract(*this).AddTo(f);}
  //CFract operator+(const CFract& f) const { return CFract(f).AddTo(*this);}
  CFract operator +(const CFract& f) const { return CFract(f)+=*this;}
  CFract operator -(const CFract& f) const { return CFract(f)-=*this; }
  CFract operator *(const CFract& f) const { return CFract(f)*=*this; }
  CFract operator /(const CFract& f) const { return CFract(*this)/=f;}
  CFract& operator +=(const CFract& f) { return AddTo(f); }
  //CFract& operator+=(const CFract& f) { return *this = *this + f; }
  CFract& operator -=(const CFract& f) { return SubTo(f);}
  CFract& operator *=(const CFract& f) { return MultTo(f);}
  CFract& operator /=(const CFract& f) { return operator*=(!f); }
  // TODO: -, *, -=, *=, /=, / (!!!!!!)
  CFract operator-() const { return CFract(-a,b); }
  CFract operator+() { return *this; }
  //! Opérateur ! : retourne la fraction inversée (sans la modifier) :
  //! gestion de la possible division par 0:
  //! 1. éviter l'opération en faisant rien
  //! 2. éviter l'opération en remplaçant 'a' par 1, ou un nombre très grand ou très petit
  //! 3. afficher un message d'erreur et arrêter le programme avec assert
  //! 4. éviter en déclenchant une exception (à voir plus tard)
  //! Dans tous les cas: gestion unique !!! Notre choix: 2. basé sur le comportement du ctor
  CFract operator!() const { return CFract(b,a); }
  //! inverse la fraction pour qui l'on travaille
  CFract& operator~() { return *this=!*this; }
  //! opérateurs booléens ==, >, <, >=, <=, !=
  bool operator ==(const CFract& f) const { return a==f.a && b==f.b; } 
  bool operator <(const CFract& f) const { return a*f.b < f.a*b; } 
  bool operator >(const CFract& f) const { return a*f.b > f.a*b; } 
  bool operator <=(const CFract& f) const { return !operator>(f); } 
  bool operator >=(const CFract& f) const { return !operator<(f); }
  // opérateurs de pré/post in/décrémentation
  //CFract& operator++() { a+=b; return *this;}
  CFract& operator++() { return *this+=1;}
  CFract operator++(int ) { CFract c(*this); ++(*this); return c; }
  //CFract operator++(int ) { CFract c(*this); operator++(); return c; }
  CFract& operator --() { return SubTo(1); } // pre-décrementation
  CFract operator --(int) { CFract f(*this); SubTo(1); return f; } // post-décrementation
  //! opérateur(s) parenthèses: notre choix => fonctionnement comme des setters
  CFract& operator()(int _a=0, int _b=1) { *this=CFract(_a,_b); return *this; }
  // operateurs de typecast
  operator float() const { return a/(float)b; }
  operator double() const { return a/(double)b; }
};

#endif //_FRACT_H_