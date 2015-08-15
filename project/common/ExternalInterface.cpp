#ifndef STATIC_LINK
#define IMPLEMENT_API
#endif

#if defined(HX_WINDOWS) || defined(HX_MACOS) || defined(HX_LINUX)
#define NEKO_COMPATIBLE
#endif


#include <hx/CFFI.h>
#include "Utils.h"


using namespace winutils;

static value winutils_init ()
{
  Init();
  return alloc_null();
}
DEFINE_PRIM (winutils_init, 0);

static value winutils_exit ()
{
  Exit();
  return alloc_null();
}
DEFINE_PRIM (winutils_exit, 0);

static value winutils_insertnormalmenu (value uid, value str, value callback)
{
  if(!val_is_string(str) || !val_is_int(uid) || !val_is_function(callback))return alloc_null();
  const char *_str = val_string(str);
  int _uid = val_int(uid);
  InsertNormalMenu(_uid, _str, callback);
  return alloc_null();
}
DEFINE_PRIM (winutils_insertnormalmenu, 3);

static value winutils_insertseparatormenu ()
{
  InsertSeparatorMenu();
  return alloc_null();
}
DEFINE_PRIM (winutils_insertseparatormenu, 0);

static value winutils_setradio (value iFirst, value iLast, value iCheck)
{
  if(!val_is_int(iFirst) || !val_is_int(iLast) || !val_is_int(iCheck))return alloc_null();
  int _iFirst = val_int(iFirst);
  int _iLast = val_int(iLast);
  int _iCheck = val_int(iCheck);
  SetRadio(_iFirst, _iLast, _iCheck);
  return alloc_null();
}
DEFINE_PRIM (winutils_setradio, 3);

static value winutils_setenable (value iPos, value iEnable)
{
  if(!val_is_int(iPos) || !val_is_int(iEnable))return alloc_null();
  int _iPos = val_int(iPos);
  int _iEnable = val_int(iEnable);
  SetEnable(_iPos, _iEnable);
  return alloc_null();
}
DEFINE_PRIM (winutils_setenable, 2);

static value winutils_setcheck (value iPos, value bCheck)
{
  if(!val_is_int(iPos) || !val_is_bool(bCheck))return alloc_null();
  int _iPos = val_int(iPos);
  bool _bCheck = val_bool(bCheck);
  SetCheck(_iPos, _bCheck);
  return alloc_null();
}
DEFINE_PRIM (winutils_setcheck, 2);

static value winutils_enablelmousedrag (value bEnable)
{
  if(!val_is_bool(bEnable))return alloc_null();
  bool _bEnable = val_bool(bEnable);
  EnableLMouseDrag(_bEnable);
  return alloc_null();
}
DEFINE_PRIM (winutils_enablelmousedrag, 1);

static value winutils_enablelmousethru (value bThru)
{
  if(!val_is_bool(bThru))return alloc_null();
  bool _bThru = val_bool(bThru);
  EnableLMouseThru(_bThru);
  return alloc_null();
}
DEFINE_PRIM (winutils_enablelmousethru, 1);

static value winutils_setlmousedragclip (value xMin, value xMax, value yMin, value yMax)
{
  if(!val_is_int(xMin) || !val_is_int(xMax) || !val_is_int(yMin) || !val_is_int(yMax))return alloc_null();
  SetLMouseDragClip(val_int(xMin), val_int(xMax), val_int(yMin), val_int(yMax));
  return alloc_null();
}
DEFINE_PRIM (winutils_setlmousedragclip, 4);

static value winutils_sendnclbuttondown ()
{
  SendWM_NCLBUTTONDOWN();
  return alloc_null();
}
DEFINE_PRIM (winutils_sendnclbuttondown, 0);

static value winutils_enableantiflicker (value bEnable)
{
  if(!val_is_bool(bEnable))return alloc_null();
  bool _bEnable = val_bool(bEnable);
  EnableAntiFlicker(_bEnable);
  return alloc_null();
}
DEFINE_PRIM (winutils_enableantiflicker, 1);

extern "C" void winutils_main () {
	
	val_int(0); // Fix Neko init
	
  _InitTlsData();
	
}
DEFINE_ENTRY_POINT (winutils_main);



extern "C" int winutils_register_prims () { return 0; }