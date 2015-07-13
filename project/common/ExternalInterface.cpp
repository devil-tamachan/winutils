#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include "Utils.h"


using namespace winutils;

static void winutils_init ()
{
  Init();
}
DEFINE_PRIM (winutils_init, 0);

static void winutils_exit ()
{
  Exit();
}
DEFINE_PRIM (winutils_exit, 0);

static void winutils_insertnormalmenu (value uid, value str, value callback)
{
  if(!val_is_string(str) || !val_is_int(uid) || !val_is_function(callback))return;
  const char *_str = val_string(str);
  int _uid = val_int(uid);
  InsertNormalMenu(_uid, _str, callback);
}
DEFINE_PRIM (winutils_insertnormalmenu, 3);

static void winutils_insertseparatormenu ()
{
  InsertSeparatorMenu();
}
DEFINE_PRIM (winutils_insertseparatormenu, 0);

static void winutils_setradio (value iFirst, value iLast, value iCheck)
{
  if(!val_is_int(iFirst) || !val_is_int(iLast) || !val_is_int(iCheck))return;
  int _iFirst = val_int(iFirst);
  int _iLast = val_int(iLast);
  int _iCheck = val_int(iCheck);
  SetRadio(_iFirst, _iLast, _iCheck);
}
DEFINE_PRIM (winutils_setradio, 3);

static void winutils_setenable (value iPos, value iEnable)
{
  if(!val_is_int(iPos) || !val_is_int(iEnable))return;
  int _iPos = val_int(iPos);
  int _iEnable = val_int(iEnable);
  SetEnable(_iPos, _iEnable);
}
DEFINE_PRIM (winutils_setenable, 2);

static void winutils_setcheck (value iPos, value bCheck)
{
  if(!val_is_int(iPos) || !val_is_bool(bCheck))return;
  int _iPos = val_int(iPos);
  bool _bCheck = val_bool(bCheck);
  SetCheck(_iPos, _bCheck);
}
DEFINE_PRIM (winutils_setcheck, 2);

static void winutils_enablermousedrag (value bEnable)
{
  if(!val_is_bool(bEnable))return;
  bool _bEnable = val_bool(bEnable);
  EnableRMouseDrag(_bEnable);
}
DEFINE_PRIM (winutils_enablermousedrag, 1);

extern "C" void winutils_main () {
	
	val_int(0); // Fix Neko init
	
  _InitTlsData();
	
}
DEFINE_ENTRY_POINT (winutils_main);



extern "C" int winutils_register_prims () { return 0; }