#include <iostream>
#include <iomanip>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <typeinfo> // accepte aussi <typeinfo.h> sauf VS2022
#include <string.h>
using namespace std;

class FigGeom
{
public:
  FigGeom() { cout<<"Ctor de FigGeom @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  virtual ~FigGeom() { cout<<"Dtor de FigGeom @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  void Show() const {cout<<"Une FigGeom("<<typeid(*this).name()<<") avec une surface de "<<GetSurface()<<"\n";}
  virtual float GetSurface() const = 0; //{ return 0; }
  virtual void ShowAll() const { Show(); };
};

class Cercle: public FigGeom
{
  float r;
public:
  Cercle(float _r): r(_r) { cout<<"Ctor de Cercle @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  ~Cercle() { cout<<"Dtor de Cercle @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  void Show() const {cout<<"Une Cercle("<<typeid(*this).name()<<") avec une surface de "<<GetSurface()<<"\n";}
  float GetSurface() const override { return float(M_PI)*r*r; }
  void ShowAll() const override { Show(); cout<<" qui hérite de "; /*FigGeom*/__super::ShowAll(); };
};

class Ellipse: public Cercle
{
  float e;
public:
  Ellipse(float _r, float _e): Cercle(_r), e(_e) { cout<<"Ctor de Ellipse @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  ~Ellipse() { cout<<"Dtor de Ellipse @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  void Show() const {cout<<"Une Ellipse("<<typeid(*this).name()<<") avec une surface de "<<GetSurface()<<"\n";}
  float GetSurface() const override { return e*Cercle::GetSurface(); }
  void ShowAll() const override { Show(); cout<<" qui hérite de "; /*Cercle*/__super::ShowAll(); };
};

class Carre: public FigGeom
{
protected:
  float a;
public:
  Carre(float _a): a(_a) { cout<<"Ctor de Carre @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  ~Carre() { cout<<"Dtor de Carre @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  void Show() const {cout<<"Une Carre("<<typeid(*this).name()<<") avec une surface de "<<GetSurface()<<"\n";}
  float GetSurface() const override { return a*a; }
  void ShowAll() const override { Show(); cout<<" qui hérite de "; __super::ShowAll(); };
  void Special() const { cout<<"Je fais quelque chose de spécial\n";}
};

class Rect: public Carre
{
  float b;
public:
  Rect(float _a, float _b): Carre(_a), b(_b) { cout<<"Ctor de Rect @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  ~Rect() { cout<<"Dtor de Rect @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  void Show() const {cout<<"Une Rect("<<typeid(*this).name()<<") avec une surface de "<<GetSurface()<<"\n";}
  float GetSurface() const override { return a*b; }
  void ShowAll() const override { Show(); cout<<" qui hérite de "; __super::ShowAll(); };
};

class Triangle: public FigGeom
{
  float a;
public:
  Triangle(float _a): a(_a) { cout<<"Ctor de Triangle @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  ~Triangle() { cout<<"Dtor de Triangle @="<<this<<" de type "<<typeid(*this).name()<<" et taille "<<sizeof(*this)<<"\n";}
  void Show() const {cout<<"Une Triangle("<<typeid(*this).name()<<") avec une surface de "<<GetSurface()<<"\n";}
  float GetSurface() const override { return 0.25f*sqrt(3.0f)*a*a; }
  void ShowAll() const override { Show(); cout<<" qui hérite de "; __super::ShowAll(); };
};

void test1()
{
#if 0
  FigGeom* tab[]={new Cercle(1), new Ellipse(2,0.5f), 0, new Carre(2.5f), new Triangle(1), new Rect(0.5f, 12.0f)};
  const size_t NB_FIG=sizeof(tab)/sizeof(tab[0]);
#elif 1
  const size_t NB_FIG=20;
  FigGeom* tab[NB_FIG];
  for(int i=0; i<NB_FIG; i++)
    switch(rand()%6)
    {
    case 0: tab[i]=0; break; // une place vide 
    case 1: tab[i]=new Cercle(10.0f+(rand()%5)); break; // cercle 
    case 2: tab[i]=new Ellipse(10.0f+(rand()%5),0.3f); break; // ellipse 
    case 3: tab[i]=new Carre(10.0f+(rand()%5)); break; // carré 
    case 4: tab[i]=new Rect(10.0f+(rand()%5),10.0f+(rand()%5)); break; // rectangle 
    case 5: tab[i]=new Triangle(10.0f+(rand()%5)); break; // triangle 
    }
#endif
  cout<<"Type pour tous les objets:\n";
  for(size_t i=0; i<NB_FIG; i++) if(tab[i]) cout<<"tab["<<i<<"] pointe vers "<<typeid(*tab[i]).name()<<"\n";
  cout<<"Show pour tous les objets:\n";
  for(size_t i=0; i<NB_FIG; i++) if(tab[i]) tab[i]->Show();
  cout<<"ShowAll pour tous les objets:\n";
  for(size_t i=0; i<NB_FIG; i++) if(tab[i]) tab[i]->ShowAll();

  float St=0;
  for(size_t i=0; i<NB_FIG; i++) if(tab[i]) St+=tab[i]->GetSurface();
  cout<<"Surface totale : "<<St<<"\n";

  size_t NbCercles=0;
  for(size_t i=0; i<NB_FIG; i++) if(tab[i] && dynamic_cast<Cercle*>(tab[i])) NbCercles++; // NON: (Carre*)(tab[i])  ou   static_cast<Carre*>(tab[i])) !!!
  cout<<"Nb d'objets de type Cercle : "<<NbCercles<<"\n";
  NbCercles=0;
  for(size_t i=0; i<NB_FIG; i++) if(tab[i] && strcmp(typeid(*tab[i]).name(),"class Cercle")==0) NbCercles++;
  cout<<"Nb d'objets complets de type Cercle : "<<NbCercles<<"\n";

  Carre* pc;
  for(size_t i=0; i<NB_FIG; i++) if(tab[i] && ((pc=dynamic_cast<Carre*>(tab[i]))!=0)) pc->Special();

  cout<<"Destruction de tous les objets:\n";
  for(size_t i=0; i<NB_FIG; i++) if(tab[i]) delete tab[i];
}

#include <crtdbg.h>
#include "..\ConsoleCP.h"
void main()
{
  ConsoleCodePage cp;
  test1();
  cout<<"Memory leaks : "<<(_CrtDumpMemoryLeaks()?"YES":"NO")<<"\n";
}
