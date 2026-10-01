#ifndef _IS_HELPER_
#define _IS_HELPER_
#include <iostream>
#include <string>
#include <cstring>
// from https://stackoverflow.com/questions/9825768/safer-but-easy-to-use-and-flexible-c-alternative-to-sscanf
// enhanced/adapted by M.V.

// for single (w)char but works for any other compatible type E
template<typename E, typename T> inline std::basic_istream<E,T>& operator>>(std::basic_istream<E,T>& is, const E& elem)
{
  E buf;     //local buffer
  is >> buf; //read data
  if(buf!=elem) is.setstate(is.rdstate() | std::ios::failbit); //if it failed then set the state
  return is;
}
// for 0-terminated const (w)char tab/array
template<typename E, typename T, size_t N> inline std::basic_istream<E,T>& operator>>(std::basic_istream<E,T>& is, const E(&cstr)[N])
{
  E buf[N-1];   //local buffer
  is >> buf[0]; //skips whitespace
  if(N>2) is.read(buf+1, N-2); //read the rest
  if(memcmp(buf, cstr, (N-1)*sizeof(E))) 
    is.setstate(is.rdstate() | std::ios::failbit); //if it failed then set the state
  return is;
}
// redirect mutable (w)char tabs/arrays to their normal function
template<typename E, typename T, size_t N> inline std::basic_istream<E,T>& operator>>(std::basic_istream<E,T>& is, E(&tab)[N])
{ return std::operator>>(is, tab); }

#endif