#ifndef _BEGIN_END_
#define _BEGIN_END_
struct BeginEnd_
{
  const char* const func;
  BeginEnd_(const char* _func):func(_func) {printf("******** Begin of %s *********\n",func);}
  ~BeginEnd_() {printf("******** End of %s *********\n",func);}
};
#define BeginEnd BeginEnd_ be(__FUNCTION__)
#endif //_BEGIN_END_
