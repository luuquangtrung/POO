#ifndef _FIG_GEOM_
#define _FIG_GEOM_
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#if (_MSC_VER <= 1500) // 1500:VS9, 1600:VS2010, 1800:VS12, 1910-1916:VS15, 1920-1929:VS16, 1930-1940:VS17
#define nullptr 0
#endif // _MSC_VER
#define VERSION_OPT // version optimisée (1 allocation dynamique par objet)
// version classique (2 allocations dynamiques par objet)
class CFigGeom
{
private:
  static size_t nbFigs, nbLabels;
  const size_t label;
  size_t nbs;
  unsigned color;//unsigned __int32
  float *xs, *ys;
  void Clean()
  {
    if(!nbs) return;
#ifdef VERSION_OPT
    delete[] xs;
#else
    delete[] xs; delete[] ys;
#endif
    xs=ys=nullptr;
  }
  void Alloc()
  {
    if(!nbs) return;
#ifdef VERSION_OPT
    xs=new float[2*nbs]; ys=xs+nbs;
#else
    xs=new float[nbs]; ys=new float[nbs];
#endif
  }
  void Copy(const CFigGeom& f)
  {
    for(size_t i=0; i<nbs; i++) { xs[i]=f.xs[i]; ys[i]=f.ys[i]; }
  }
public:
  static int GetNbFigs() {return nbFigs;}
  static void ShowInfo() { printf("Statistiques CFigGeom: %Iu crees, %Iu en vie\n",0,nbFigs);} 
  CFigGeom(const CFigGeom& f): nbs(f.nbs), color(f.color), xs(nullptr), ys(nullptr), label(nbLabels++)
  {
    nbFigs++;  Alloc(); Copy(f);
  }
  CFigGeom(size_t _nbs, unsigned int _color=0xFFFFFF): nbs(_nbs), color(_color), xs(nullptr), ys(nullptr), label(nbLabels++)
  {
    nbFigs++; Alloc();
    for(size_t i=0; i<nbs; i++)
    { xs[i]=float(cos((2*M_PI*i)/nbs)); ys[i]=float(sin((2*M_PI*i)/nbs)); }
  }
  CFigGeom(size_t _nbs, const float* _xs, const float* _ys, unsigned int _color=0xFFFFFF):
    nbs(_nbs), color(_color), xs(nullptr), ys(nullptr), label(nbLabels++)
  {
    nbFigs++; Alloc();
    for(size_t i=0; i<nbs; i++) {xs[i]=_xs[i]; ys[i]=_ys[i];}
  }
  CFigGeom& operator=(const CFigGeom& f)
  {
    if(&f==this) return *this; // pas de copie de soi-même !
    Clean();
    nbs=f.nbs; color=f.color;
    Alloc(); Copy(f);
    return *this;
  }
  ~CFigGeom() { Clean(); nbFigs--; }
  void Affiche() const { Affiche(stdout); }
  void Affiche(FILE* pf) const
  {
    fprintf(pf,"FigGeom #%Iu (%Iu): @=%p, %Iu sommets, perimetre=%8.3f, couleur=%08lX :\n",
      label, nbFigs,this,nbs,Perimetre(),color);
    for(size_t i=0; i<nbs; i++)
      fprintf(pf,"  sommet [%2u] = (%10.3f,%10.3f)\n",i,xs[i],ys[i]);
  }
  bool Affiche(const char* fn) const
  {
    FILE* pf=fopen(fn,"wt");
    if(!pf) return false;
    Affiche(pf);
    fclose(pf);
    return true;
  }
  float Perimetre() const
  {
    float peri=0;
    if(nbs<2) return peri;
    peri=sqrt((xs[0]-xs[nbs-1])*(xs[0]-xs[nbs-1])+(ys[0]-ys[nbs-1])*(ys[0]-ys[nbs-1]));
    for(size_t i=0; i<nbs-1; i++)
      peri+=sqrt((xs[i]-xs[i+1])*(xs[i]-xs[i+1])+(ys[i]-ys[i+1])*(ys[i]-ys[i+1]));
    return peri;
  }
  FILE* operator>>(FILE* pf) { Affiche(pf); return pf;}
  bool GetSommet(size_t idx, float& x, float& y) const
  {
    if(idx>nbs) return false;
    x=xs[idx]; y=ys[idx];
    return true;
  }
  bool SetSommet(size_t idx, float x, float y)
  {
    if(idx>=nbs) return false;
    xs[idx]=x; ys[idx]=y;
    return true;
  }
  //static FILE* operator<<(FILE* pf, const CFigGeom& f) { f.Affiche(pf); return pf;} // NON !!!
  //static void operator<<(const char* fn, const CFigGeom& f) { f.Affiche(fn); }
};
__declspec(selectany) size_t CFigGeom::nbFigs(0);
__declspec(selectany) size_t CFigGeom::nbLabels(0);

inline FILE* operator<<(FILE* pf, const CFigGeom& f) { f.Affiche(pf); return pf;}
inline bool operator<<(const char* fn, const CFigGeom& f) { return f.Affiche(fn); }

#endif // _FIG_GEOM_