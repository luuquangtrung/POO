#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

//****************** tests sur les opérateurs () ***************
class Gene
{
  float f, A, ph;
public:
  Gene(float _f, float _A, float _ph=0): f(_f), A(_A), ph(_ph) {}
  float operator ()(float t)const { return A*sin(2*float(M_PI)*f*t+ph);}
};

#define TEST_FINTERV
class FInterv
{
  float t, tend, dt;
public:
  FInterv(float _t0, float _tend, float _dt): t(_t0), tend(_tend), dt(_dt) {}
  operator bool() { /*printf("Fin: %s\n",(t<tend?"NON":"OUI"));*/ return t<tend;}
  operator float() { /*printf("t=%8.3f\n",t);*/ return t;}
  FInterv& operator++() { t+=dt; return *this;}
};

void test0()
{
  Gene g(10,5);
  for(float t=0; t<0.2f; t+=0.01f) printf("g(%6.3f)=%6.3f\n",t,g(t)); 
#ifdef TEST_FINTERV
  for(FInterv t(0,0.2f,0.01f); t; ++t) printf("g(%6.3f)=%6.3f\n",float(t),g(t)); 
#endif
}

void main()
{
  test0();
}
