#include <stdio.h>

#if 0
class CFichLog
{
  FILE* pf;
  CFichLog(const CFichLog& f) {}
  CFichLog& operator=(const CFichLog& f){ return *this; }
public:
  CFichLog(const char* fname=0)
  {
    if(fname)
    {
      pf=fopen(fname,"wt");
      if(!pf) pf=stdout;
    }
    else pf=stdout;
    Ecrire("Ouverture de log\n");
  }
  ~CFichLog()
  {
    Ecrire("Fermeture de log\n");
    if(pf!=stdout) fclose(pf); 
  }
  void Ecrire(const char*s)    { fprintf(pf,"%s",s);}
  void Ecrire(unsigned long v) { fprintf(pf,"%lu",v);}
  void Ecrire(double v)        { fprintf(pf,"%lf",v);}
  CFichLog& operator<<(const char*s)    { Ecrire(s); return *this; }
  CFichLog& operator<<(unsigned long v) { Ecrire(v); return *this; }
  CFichLog& operator<<(double v)        { Ecrire(v); return *this; }
};

class CCouleur: public CFichLog
{
  unsigned long color;
public:
  CCouleur(unsigned long _color, const char* fname):color(_color),CFichLog(fname)
  {
    Ecrire("Ctor de CCouleur ");Ecrire(color);Ecrire("\n");
    //*this<<"Ctor de CCouleur "<<color<<"\n";
    //operator<<("Ctor de CCouleur ")<<color<<"\n";
  }
  ~CCouleur() { Ecrire("Dtor de CCouleur\n"); }
};

class CPoint2D: public CFichLog
{
  float x, y;
public:
  CPoint2D(float _x, float _y, const char* fname):x(_x),y(_y),CFichLog(fname)
  {
    Ecrire("Ctor de CPoint2D ");Ecrire(x);Ecrire(", ");Ecrire(y);Ecrire("\n");
    //*this<<"Ctor de CPoint2D "<<x<<", "<<y<<"\n";
  }
  ~CPoint2D() { Ecrire("Dtor de CPoint2D\n"); }
};

class CPointCouleur2D: public CCouleur, public CPoint2D
{
public:
  CPointCouleur2D(float x, float y, unsigned long color, const char* fn1, const char* fn2):
      CCouleur(color,fn1),CPoint2D(x,y,fn2)
  {
    //Ecrire("Ctor de CPointCouleur2D\n");
    CFichLog::Ecrire("Ctor de CPointCouleur2D\n");
    CCouleur::Ecrire("Ctor de CPointCouleur2D\n");
    CPoint2D::Ecrire("Ctor de CPointCouleur2D\n");
    *this<<"Ctor de CPointCouleur2D\n";
  }
  ~CPointCouleur2D()
  {
    //Ecrire("Dtor de CPointCouleur2D\n");
    CFichLog::Ecrire("Dtor de CPointCouleur2D\n");
    CCouleur::Ecrire("Dtor de CPointCouleur2D\n");
    CPoint2D::Ecrire("Dtor de CPointCouleur2D\n");
  }
};
#elif 0
class CFichLog
{
  FILE* pf;
  CFichLog(const CFichLog& f) {}
  CFichLog& operator=(const CFichLog& f){ return *this; }
public:
  CFichLog(const char* fname=0)
  {
    if(fname)
    {
      pf=fopen(fname,"wt");
      if(!pf) pf=stdout;
    }
    else pf=stdout;
    Ecrire("Ouverture de log\n");
  }
  ~CFichLog()
  {
    Ecrire("Fermeture de log\n");
    if(pf!=stdout) fclose(pf); 
  }
  void Ecrire(const char*s)    { fprintf(pf,"%s",s);}
  void Ecrire(unsigned long v) { fprintf(pf,"%lu",v);}
  void Ecrire(double v)        { fprintf(pf,"%lf",v);}
  CFichLog& operator<<(const char*s)    { Ecrire(s); return *this; }
  CFichLog& operator<<(unsigned long v) { Ecrire(v); return *this; }
  CFichLog& operator<<(double v)        { Ecrire(v); return *this; }
};

class CCouleur: virtual public CFichLog
{
  unsigned long color;
public:
  CCouleur(unsigned long _color, const char* fname):color(_color),CFichLog(fname)
  {
    Ecrire("Ctor de CCouleur ");Ecrire(color);Ecrire("\n");
    //*this<<"Ctor de CCouleur "<<color<<"\n";
    //operator<<("Ctor de CCouleur ")<<color<<"\n";
  }
  ~CCouleur() { Ecrire("Dtor de CCouleur\n"); }
};

class CPoint2D: virtual public CFichLog
{
  float x, y;
public:
  CPoint2D(float _x, float _y, const char* fname):x(_x),y(_y),CFichLog(fname)
  {
    Ecrire("Ctor de CPoint2D ");Ecrire(x);Ecrire(", ");Ecrire(y);Ecrire("\n");
    //*this<<"Ctor de CPoint2D "<<x<<", "<<y<<"\n";
  }
  ~CPoint2D() { Ecrire("Dtor de CPoint2D\n"); }
};

class CPointCouleur2D: public CCouleur, public CPoint2D
{
public:
  CPointCouleur2D(float x, float y, unsigned long color, const char* fn1, const char* fn2):
      CCouleur(color,fn1),CPoint2D(x,y,fn2)
  {
    //Ecrire("Ctor de CPointCouleur2D\n");
    CFichLog::Ecrire("Ctor de CPointCouleur2D\n");
    CCouleur::Ecrire("Ctor de CPointCouleur2D\n");
    CPoint2D::Ecrire("Ctor de CPointCouleur2D\n");
    *this<<"Ctor de CPointCouleur2D\n";
  }
  ~CPointCouleur2D()
  {
    //Ecrire("Dtor de CPointCouleur2D\n");
    CFichLog::Ecrire("Dtor de CPointCouleur2D\n");
    CCouleur::Ecrire("Dtor de CPointCouleur2D\n");
    CPoint2D::Ecrire("Dtor de CPointCouleur2D\n");
  }
};
#else
class CFichLog
{
  FILE* pf;
  CFichLog(const CFichLog& f) {}
  CFichLog& operator=(const CFichLog& f){ return *this; }
public:
  CFichLog(const char* fname=0)
  {
    if(fname)
    {
      pf=fopen(fname,"wt");
      if(!pf) pf=stdout;
    }
    else pf=stdout;
    Ecrire("Ouverture de log\n");
  }
  ~CFichLog()
  {
    Ecrire("Fermeture de log\n");
    if(pf!=stdout) fclose(pf); 
  }
  void Ecrire(const char*s)    { fprintf(pf,"%s",s);}
  void Ecrire(unsigned long v) { fprintf(pf,"%lu",v);}
  void Ecrire(double v)        { fprintf(pf,"%lf",v);}
  CFichLog& operator<<(const char*s)    { Ecrire(s); return *this; }
  CFichLog& operator<<(unsigned long v) { Ecrire(v); return *this; }
  CFichLog& operator<<(double v)        { Ecrire(v); return *this; }
};

class CCouleur: virtual public CFichLog
{
  unsigned long color;
public:
  CCouleur(unsigned long _color, const char* fname):color(_color),CFichLog(fname)
  {
    Ecrire("Ctor de CCouleur ");Ecrire(color);Ecrire("\n");
    //*this<<"Ctor de CCouleur "<<color<<"\n";
    //operator<<("Ctor de CCouleur ")<<color<<"\n";
  }
  ~CCouleur() { Ecrire("Dtor de CCouleur\n"); }
};

class CPoint2D: virtual public CFichLog
{
  float x, y;
public:
  CPoint2D(float _x, float _y, const char* fname):x(_x),y(_y),CFichLog(fname)
  {
    Ecrire("Ctor de CPoint2D ");Ecrire(x);Ecrire(", ");Ecrire(y);Ecrire("\n");
    //*this<<"Ctor de CPoint2D "<<x<<", "<<y<<"\n";
  }
  ~CPoint2D() { Ecrire("Dtor de CPoint2D\n"); }
};

class CPointCouleur2D: public CCouleur, public CPoint2D, virtual public CFichLog
{
public:
  CPointCouleur2D(float x, float y, unsigned long color, const char* fname):
      CCouleur(color,0),CPoint2D(x,y,0),CFichLog(fname)
  {
    //Ecrire("Ctor de CPointCouleur2D\n");
    CFichLog::Ecrire("Ctor de CPointCouleur2D\n");
    CCouleur::Ecrire("Ctor de CPointCouleur2D\n");
    CPoint2D::Ecrire("Ctor de CPointCouleur2D\n");
    *this<<"Ctor de CPointCouleur2D\n";
  }
  ~CPointCouleur2D()
  {
    //Ecrire("Dtor de CPointCouleur2D\n");
    CFichLog::Ecrire("Dtor de CPointCouleur2D\n");
    CCouleur::Ecrire("Dtor de CPointCouleur2D\n");
    CPoint2D::Ecrire("Dtor de CPointCouleur2D\n");
  }
};
#endif

void test1()
{
  //CPointCouleur2D olj(13.3f,6.3f,0xFF00FF,"log1.txt","log2.txt");
  CPointCouleur2D olj(13.3f,6.3f,0xFF00FF,"log.txt");
}

void main()
{
  test1();
}

