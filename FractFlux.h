#ifndef FRACT_H
#define FRACT_H

#include <iostream>
#include <iomanip>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "ConsoleColor.h"
#include "isHelper.h"
//! CFract modélise une fraction de nombres entiers
//! Version release, flux C, ctors implicites et opérateurs de typecast vers float et double
//! Fraction toujours valide : b!=0
//! Si le ctor reçoit b==0 il sera remplacé par 1 (idem pour toute opération d'inversion/division)
//! Fraction à représentation unique : a et b premiers entre eux (pgdc(a,b)==1) et b>0
//! Définir la macro DO_VERB pour activer les messages lors des ctors/dtor/typecast
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
#if DO_VERB
  CFract(int _a=0, int _b=1):a(_a), b(_b==0 ? 1 : _b) { Norm(); printf("Ctor 0-2 params :"); Affiche();}
  CFract(const CFract& f):a(f.a), b(f.b) {  printf("Ctor copie :"); Affiche();}
  ~CFract() { printf("Dtor :"); Affiche(); }
  FILE* Affiche(FILE* pf) const { fprintf(pf,"CFract (%d/%d) @=%p\n",a,b,this); return pf;}
  //! opérateurs de typecast
  operator float() const { printf("CFract::float\n"); return a/(float)b; }
  operator double() const { printf("CFract::double\n"); return a/(double)b; }
#else
  CFract(int _a=0, int _b=1):a(_a), b(_b==0 ? 1 : _b) { Norm(); } 
  std::ostream& Affiche(std::ostream& os) const 
  { using namespace ConsoleColor; return os<<Push<<FHRed<<'('<<a<<'/'<<b<<')'<<Pop; }
  //! opérateurs de typecast
  operator float() const { return a/(float)b; }
  operator double() const { return a/(double)b; }
#endif
  void Affiche() const { Affiche(std::cout); }
  //bool Read(std::istream& is) { char c1, c2, c3; is>>c1>>a>>c2>>b>>c3; return !!is && c1=='(' && c2=='/' && c3==')'; }
  //bool Read(std::istream& is) { return !!( is>>'('>>a>>'/'>>b>>')'); }
  std::istream& Read(std::istream& is) { return is>>'('>>a>>'/'>>b>>')'; }
  CFract& MultTo(const CFract& f) { a*=f.a; b*=f.b; Norm(); return *this; }
  CFract& AddTo(const CFract& f) { a=a*f.b+b*f.a; b*=f.b; Norm(); return *this; }
  CFract& SubTo(const CFract& f) { a=a*f.b-b*f.a; b*=f.b; Norm(); return *this; }
  const int& GetA() const {return a;}
  const int& GetB() const {return b;}
  void SetA(int _a) { a=_a; Norm(); } 
  void SetB(int _b) { if(_b!=0) { b=_b; Norm();} }
#ifdef _MSC_VER 
  //! attributs virtuels (que pour VC++)
  __declspec(property(get=GetA, put=SetA)) int A;
  __declspec(property(get=GetB, put=SetB)) int B;
#endif
  CFract& operator +=(const CFract& f) { return AddTo(f);}
  CFract& operator -=(const CFract& f) { return SubTo(f);}
  CFract& operator *=(const CFract& f) { return MultTo(f);}
  CFract& operator /=(const CFract& f) { return operator*=(!f); }
  CFract operator +(const CFract& f) const { return CFract(f)+=*this; }
  CFract operator -(const CFract& f) const { return CFract(f)-=*this; }
  CFract operator *(const CFract& f) const { return CFract(f)*=*this; }
  CFract operator /(const CFract& f) const { return CFract(*this)/=f;}
  //! opérateurs unaires
  CFract operator -() { return CFract(-a, b); }
  CFract operator +() { return *this; }
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
  //! opérateurs de pré/post in/décrémentation
  CFract& operator ++() { return *this+=1; }
  const CFract operator ++(int) { CFract res(*this); a+=b; return res; }
  CFract& operator --() { return SubTo(1); } // pré-décrémentation
  CFract operator --(int) { CFract f(*this); SubTo(1); return f; } // post-décrémentation
  //! opérateur(s) parenthèses: notre choix => fonctionnement comme des setters
  CFract& operator()(int _a=0, int _b=1) { return *this=CFract(_a,_b); }
};

inline std::ostream& operator<<(std::ostream& os, const CFract& f) { return f.Affiche(os); }
inline std::istream& operator>>(std::istream& is, CFract& f) {  return f.Read(is); }

#endif // FRACT_H