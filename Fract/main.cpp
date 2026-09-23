#include "Fract.h"
#include "..\BeginEnd.h"

void test0()
{
  //CFract f1;
  //f1.Affiche();
  //f1.a=12; f1.b=7;
  //CFract f2(f1);
  //f2.Affiche();
  //f2.b=100;
  //f1=f2;
  //f1.Affiche();
}

CFract tgf[3];

void test1()
{
  BeginEnd;
  CFract f1;
  f1.Affiche();
  CFract f1b(12,7);
  CFract f2(f1);
  f2.Affiche();
  //f2.b=100;
  f1=f2;
  f1.Affiche();
  CFract f3(3);
  const CFract f4(3,7);
  f4.Affiche();
  f3.A=13;
  f3.B=f3.A+17;
  f3.Affiche();
  CFract f5=5;
  CFract tf3[]={CFract(),CFract(3,13), 14, f5};
  CFract *fdyn=new CFract(5,7);
  delete fdyn;
  CFract *tdyn=new CFract[3];
  delete[] tdyn;
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
  CFract f2(2,5);
  double res=(double)f2+2.5;
  double res2=double(f2)+2.5;
  //double res3=f2+2.5;
  double res3=f2+CFract(2.5);
}

void main()
{
  BeginEnd;
  test0();
  test1();
  test1();
  test2();
  test3();
}