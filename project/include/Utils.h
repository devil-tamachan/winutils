#ifndef WINUTILS_H
#define WINUTILS_H


namespace winutils
{
  void _InitTlsData();
  void Init();
  void Exit();
  void InsertNormalMenu(int uid, const char *str, value callback);
  void InsertSeparatorMenu();
  void SetRadio(int iFirst, int iLast, int iCheck);
  void SetEnable(int iPos, int iEnable);
  void SetCheck(int iPos, bool bCheck);
  void EnableRMouseDrag(bool bCheck);
}


#endif