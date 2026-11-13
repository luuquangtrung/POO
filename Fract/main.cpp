#include "Fract.h"
#include "Fract.h"
#include "..\BeginEnd.h"

void test0()
{
  //CFract f1;
  //f1.Affiche();
  //f1.a=5; f1.b=13;
  ////CFract f2(f1);
  //CFract f2=f1;
  //f2.Affiche();
  //f2.a=40;
  //f2.Affiche();
  //f2=f1;
}

CFract gf(111,93);

void test1()
{
  BeginEnd;
  CFract f1;
  f1.Affiche();
  CFract f1b(5,13);
  //CFract f2(f1);
  CFract f2=f1;
  f2.Affiche();
  CFract f2b(40);
  f2.Affiche();
  f2=f1;
  f1b.Affiche();
  f1b.A=15;
  f1b.B=f1b.A-10;
  f1b.Affiche();
}

void test2()
{
  BeginEnd;
  CFract f1(0,0), f2(122,52), f3(2048,-1024), f4(-25,-125);
  f1.Affiche(); f2.Affiche(); f3.Affiche(); f4.Affiche();
  f3.MultTo(f4).Affiche();
  f2.MultTo(f4).Affiche();
  f1.AddTo(f2).MultTo(f4).Affiche();
  const CFract f5(10,30);
  // f5.MultTo(f1).Affiche(); // NON !!! erreur de compil
  CFract(2,3).MultTo(f2).Affiche();
  CFract(1,2).AddTo(f3).Affiche();
  CFract(1,2).AddTo(CFract(1,3)).Affiche();
  printf("%d %d\n",f1.GetA(),f1.GetB());
  //f1.GetA()=25;
  f1.A=25; f1.B=-5;
  printf("sizeof(f1)=%Iu, %d %d\n",sizeof(f1),f1.A,f1.B);
}

void test3()
{
  BeginEnd;
  CFract(1,7)++.Affiche();
  CFract f(12,5);
  double res=(double)f+2.5;
  double res2=double(f)+2.5;
  //double res3=f+2.5;
  double res3=f+(CFract)2.5;
  CFract f2;
  f2(4,8).Affiche();
}

void main()
{
  BeginEnd;
  test0();
  test1();
  test2();
  test3();
}