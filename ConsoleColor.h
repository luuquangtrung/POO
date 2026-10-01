#ifndef _CONSOLE_COLOR_
#define _CONSOLE_COLOR_
#include <iostream>
#include <iomanip>
#include <windows.h>

namespace ConsoleColor // collection de manipulateurs de couleur pour le flux console
{
  const WORD MaxAttrLevels=10;
  __declspec(selectany) HANDLE hc=::GetStdHandle(STD_OUTPUT_HANDLE);
  __declspec(selectany) WORD attr[10]={0x0007};
  inline void FBAttr(WORD fbattr) // changement couleur+luminosité texte et fond (8 bits de poids faible : LRGBLRGB)
  {
    *attr=(*attr & 0xFF00) | fbattr;
    ::SetConsoleTextAttribute(hc,*attr);
  }
  inline void FBAttr(WORD fattr, WORD battr) // changement couleur+luminosité texte et fond (4 bits de poids faible : LRGB)
  {
    *attr=(*attr & 0xFF00) | fattr | (battr<<4);
    ::SetConsoleTextAttribute(hc,*attr);
  }
  inline void FBColor(WORD fcolor, WORD bcolor) // changement couleur texte et fond (3 bits de poids faible : RGB)
  {
    *attr=(*attr & 0xFF88) | fcolor | (bcolor<<4);
    ::SetConsoleTextAttribute(hc,*attr);
  }
  inline void FColor(WORD color) // changement couleur texte (3 bits de poids faible : RGB)
  {
    *attr=(*attr & 0xFFF8) | color;
    ::SetConsoleTextAttribute(hc,*attr);
  }
  inline void BColor(WORD color) // changement couleur fond (3 bits de poids faible : RGB)
  {
    *attr=(*attr & 0xFF8F) | (color<<4);
    ::SetConsoleTextAttribute(hc,*attr);
  }
  inline std::ostream& Push(std::ostream& os) // empiler l'état courant
  {
    memmove(attr+1,attr,(MaxAttrLevels-1)*sizeof(WORD));
    return os;
  }
  inline std::ostream& Pop(std::ostream& os) // dépiler le dernier état empilé
  {
    memmove(attr,attr+1,(MaxAttrLevels-1)*sizeof(WORD));
    ::SetConsoleTextAttribute(hc,*attr);
    return os;
  }
  inline std::ostream& FHigh(std::ostream& os) // texte très lumineux
  {
    *attr=(*attr & 0xFFF7) | 0x0008;
    ::SetConsoleTextAttribute(hc,*attr);
    return os;
  }
  inline std::ostream& FLow(std::ostream& os) // texte peu lumineux
  {
    *attr=(*attr & 0xFFF7) | 0x0000;
    ::SetConsoleTextAttribute(hc,*attr);
    return os;
  }
  // couleurs pour le texte (forground)
  inline std::ostream& FClr(WORD clr, std::ostream& os)  {FColor(0x0000);return os;}
  inline std::ostream& FBlack(std::ostream& os)      {FColor(0x0000);return os;}
  inline std::ostream& FBlue(std::ostream& os)       {FColor(0x0001);return os;}
  inline std::ostream& FGreen(std::ostream& os)      {FColor(0x0002);return os;}
  inline std::ostream& FCyan(std::ostream& os)       {FColor(0x0003);return os;}
  inline std::ostream& FRed(std::ostream& os)        {FColor(0x0004);return os;}
  inline std::ostream& FMagenta(std::ostream& os)    {FColor(0x0005);return os;}
  inline std::ostream& FYellow(std::ostream& os)     {FColor(0x0006);return os;}
  inline std::ostream& FWhite(std::ostream& os)      {FColor(0x0007);return os;}
  inline std::ostream& FHBlack(std::ostream& os)     {FColor(0x0000);return os<<FHigh;}
  inline std::ostream& FHBlue(std::ostream& os)      {FColor(0x0001);return os<<FHigh;}
  inline std::ostream& FHGreen(std::ostream& os)     {FColor(0x0002);return os<<FHigh;}
  inline std::ostream& FHCyan(std::ostream& os)      {FColor(0x0003);return os<<FHigh;}
  inline std::ostream& FHRed(std::ostream& os)       {FColor(0x0004);return os<<FHigh;}
  inline std::ostream& FHMagenta(std::ostream& os)   {FColor(0x0005);return os<<FHigh;}
  inline std::ostream& FHYellow(std::ostream& os)    {FColor(0x0006);return os<<FHigh;}
  inline std::ostream& FHWhite(std::ostream& os)     {FColor(0x0007);return os;}
  inline std::ostream& BHigh(std::ostream& os) // fond très lumineux
  {
    *attr=(*attr & 0xFF7F) | 0x0080;
    ::SetConsoleTextAttribute(hc,*attr);
    return os;
  }
  inline std::ostream& BLow(std::ostream& os) // fond peu lumineux
  {
    *attr=(*attr & 0xFF7F) | 0x0000;
    ::SetConsoleTextAttribute(hc,*attr);
    return os;
  }
  // couleurs pour le fond (background)
  inline std::ostream& BBlack(std::ostream& os)      {BColor(0x0000);return os;}
  inline std::ostream& BBlue(std::ostream& os)       {BColor(0x0001);return os;}
  inline std::ostream& BGreen(std::ostream& os)      {BColor(0x0002);return os;}
  inline std::ostream& BCyan(std::ostream& os)       {BColor(0x0003);return os;}
  inline std::ostream& BRed(std::ostream& os)        {BColor(0x0004);return os;}
  inline std::ostream& BMagenta(std::ostream& os)    {BColor(0x0005);return os;}
  inline std::ostream& BYellow(std::ostream& os)     {BColor(0x0006);return os;}
  inline std::ostream& BWhite(std::ostream& os)      {BColor(0x0007);return os;}
};
#endif // _CONSOLE_COLOR_
