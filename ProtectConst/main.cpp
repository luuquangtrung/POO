#include <stdio.h>

const float* SearchMin(const float* tab, size_t sz)
{
  const float* pmin=tab;
  for(size_t i=0; i<sz; i++) if(tab[i]<*pmin) pmin=tab+i;
  return pmin;
}

void test1()
{
  float tab[]={2.5f, 3.8f, -5.6f, 14.3f, 1.05f};
  const float tab2[]={2.5f, 3.8f, -5.6f, 14.3f, 1.05f};
  const float* pmin=SearchMin(tab,sizeof(tab)/sizeof(tab[0]));
  printf("Val min: %f\n",*pmin);
  pmin=SearchMin(tab2,sizeof(tab2)/sizeof(tab2[0]));
  printf("Val min: %f\n",*pmin);
}

void main()
{
  test1();
}
