#include "FigGeom.h"
#include "..\BeginEnd.h"
#include <crtdbg.h>

class CDessin1
{
  CFigGeom tri, rect, penta;
public:
  CDessin1(unsigned color):tri(3,color),rect(4,color),penta(5,color) {}
};
/********************* fonctions de test unitaires ************************/
void test1()
{
  BeginEnd;
  float x[]={0,1,2}, y[]={2,1,2};
  CFigGeom f1(5,0x00FF00), f2(7,0xAABBCC);
  f1.Affiche();
  f2.Affiche();
  CFigGeom f3(0), f4(f1), f5(f3), f6(sizeof(x)/sizeof(x[0]),x,y);
  f3.Affiche();
  f4.Affiche();
  f5.Affiche();
  f6.Affiche();
  f4=f3;
  f4.Affiche();
  f3=f2;
  f3.Affiche();
  f3=f3;
  f3.Affiche();
}

CFigGeom fglob(10,0x112233);
void test2()
{
  BeginEnd;
  //static CFigGeom fstat(100);
  const float x[]={0,2,2,0}, y[]={0,0,2,2};
  CFigGeom f1(4,0x00FF00), f2(7,0xAABBCC);
  stdout << f1 << f2;
  "fig1.txt"<<f1;
  CFigGeom f3(0), f4(f1), f5(f3), f6(sizeof(x)/sizeof(x[0]),x,y);
  stdout << f3 << f4 << f5 << f6;
  f4=f3;
  f4 >> stdout;
  f3=f2;
  // rajouter l'accesseur (setter) SetSommet
  if(!f3.SetSommet(7,0.5f,-0.5f)) printf("SetSommet(7, ...) impossible\n");
  if(!f3.SetSommet(0,0.5f,-0.5f)) printf("SetSommet(0, ...) impossible\n");
  stdout << f3;
  "fig3.txt"<<f3;
}

void test3()
{
  BeginEnd;
  //CDessin1(0xFF00FF).Affiche(stdout);
  //CDessin1(0xABCDEF).Affiche(stdout);
  //stdout<<CDessin1(0x0000FF)<<CDessin1(0xFF0000);
}

void main()
{
  BeginEnd;
  CFigGeom::ShowInfo();
  test1();
  test1();
  CFigGeom::ShowInfo();
  test2();
  CFigGeom::ShowInfo(); test2();
  //CFigGeom::ShowInfo();
  //test3();
  printf("Memory leaks : %s\n",_CrtDumpMemoryLeaks()?"YES":"NO");
}