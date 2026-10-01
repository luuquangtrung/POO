#include "..\FractFlux.h"
//#include "..\FigGeomFlux.h"
#include <fstream>
#include "..\BeginEnd.h"
#include "..\ConsoleColor.h"

// tests unitaires
using namespace std;
using namespace ConsoleColor;
void test1_(ostream& os)
{
  CFract f1(2,16),f2(1,2);
  os<<f1<<"+"<<f2<<"="<<f1+f2<<endl;
  os<<f1<<"*"<<f2<<"="<<f1*f2<<endl;
}
void test1()
{
  BeginEnd;
  test1_(cout);
  fstream fs("test1.txt",ios::out);
  test1_(fs);
  ofstream ofs("test1b.txt");
  test1_(ofs);
}

void test2a(ostream& os)
{
  const int N=10;
  for(int i=-N; i<=N; i++) os<<CFract(i,10);
}
void test2b(istream& is)
{
  CFract f;
  while(is>>f) { cout<<"Fraction lue: "<<f<<"\n"; }
}

void test2()
{
  BeginEnd;
  {
    ofstream ofs("test2.txt");
    test2a(ofs);
  }
  {
    ifstream ifs("test2.txt");
    test2b(ifs);
  }
}

#if 0
void test3_(ostream& os)
{
  float x[]={0,1,2}, y[]={2,1,2};
  CFigGeom f1(5,0x00FF00), f2(7,0xAABBCC);
  f1.Affiche(os); f2.Affiche(os);
  os << f1 << f2;
  CFigGeom f3(0), f4(f1), f5(f3), f6(sizeof(x)/sizeof(x[0]),x,y);
  os << f3 << f4 << f5 << f6;
  f4=f3;
  os << f4;
  f3=f2;
  os << f3;
}

void test3()
{
  BeginEnd;
  test3_(cout);
  "penta.txt"<<CFigGeom(5,0xAABBCC);
}
#endif

void main()
{
  test1();
  test2();
  //test3();
}
