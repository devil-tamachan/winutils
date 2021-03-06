
#include <hx/CFFI.h>
#include <hx/Thread.h>
#include "Utils.h"
#include <windows.h>

namespace winutils
{
  struct MYTLSDATA
  {
    HWND hMainWnd;// = NULL;
    WNDPROC hOldWndProc;// = NULL;
    HMENU hPopupMenu;// = NULL;
    
    DWORD numMenu;// = 0;
    AutoGCRoot **bufFunc;// = NULL;
    int *bufUid;// = NULL;
    bool bLMouseDrag;// = true;
    bool bLMouseThru;// = true;
    int xMin;
    int xMax;
    int yMin;
    int yMax;
    bool bAntiFlicker;
  };
  DECLARE_TLS_DATA(struct MYTLSDATA, tls_mydata);
  
  struct MYFINDHWND
  {
    DWORD dwPid;
    HWND hWnd;
  };
  
  BOOL CALLBACK MyEnumWindowsCallBack(HWND hWnd, LPARAM lp)
  {
    struct MYFINDHWND& f = *((struct MYFINDHWND *)lp);
    DWORD dwPid = 0;
    GetWindowThreadProcessId(hWnd, &dwPid);
    if(f.dwPid != dwPid)return TRUE; //Continue
    f.hWnd = hWnd;
    return FALSE; //Stop
  }
  
  HWND findMainHWND()
  {
    struct MYFINDHWND f = {0};
    f.dwPid = GetCurrentProcessId();
    EnumWindows(MyEnumWindowsCallBack, (LPARAM)&f);
    return f.hWnd;
  }
  
  bool UTF8toCPACP(char **dst, const char *src)
  {
    wchar_t *pBuf = NULL;
    int lenW = MultiByteToWideChar(CP_UTF8, 0, src, -1, NULL, 0);
    if(lenW==0)return false;
    pBuf = new wchar_t[lenW];
    lenW = MultiByteToWideChar(CP_UTF8, 0, src, -1, pBuf, lenW);
    if(lenW==0)
    {
      delete pBuf;
      return false;
    }
    int lenACP = WideCharToMultiByte(CP_ACP, 0, pBuf, -1, NULL, 0, NULL, NULL);
    if(lenACP==0)
    {
      delete pBuf;
      return false;
    }
    *dst = new char[lenACP];
    lenACP = WideCharToMultiByte(CP_ACP, 0, pBuf, -1, *dst, lenACP, NULL, NULL);
    if(lenACP==0)delete *dst;
    delete pBuf;
    return lenACP!=0;
  }
  
  LRESULT CALLBACK PopupWndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)return 0;
    
    switch(uMsg)
    {
      case WM_ERASEBKGND:
        if(mydata->bAntiFlicker)return 1;
        break;
      case WM_COMMAND:
      {
        WORD uid = LOWORD(wp);
        
        for(int i=0; i<mydata->numMenu; i++)
        {
          if(mydata->bufUid[i] && uid==mydata->bufUid[i])
          {
            if(mydata->bufFunc[i])val_call1(mydata->bufFunc[i]->get(), alloc_int(uid));
            return 0;
          }
        }
        break;
      }
      case WM_LBUTTONDOWN:
      {
        if(mydata->bLMouseDrag)
        {
          WORD x = LOWORD(lp);
          if(mydata->xMin != -1 && mydata->xMin > x)break;
          if(mydata->xMax != -1 && mydata->xMax < x)break;
          WORD y = HIWORD(lp);
          if(mydata->yMin != -1 && mydata->yMin > y)break;
          if(mydata->yMax != -1 && mydata->yMax < y)break;
          LRESULT lr = 0;
          if(mydata->bLMouseThru && mydata->hOldWndProc)lr = CallWindowProc(mydata->hOldWndProc, hWnd, uMsg, wp, lp);
          SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lp);
          //SendMessage(hWnd, WM_SYSCOMMAND, 0xF012/*SC_DRAGMOVE*/, 0);
          return lr;
        }
      }
        break;
      case WM_RBUTTONDOWN:
      {
        if(mydata->hPopupMenu!=NULL)
        {
          SetForegroundWindow(hWnd);
          POINT pt;
          GetCursorPos(&pt);
          TrackPopupMenu(mydata->hPopupMenu, TPM_TOPALIGN | TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        }
        break;// pass msg to hOldWndProc
      }
    }
    
    if(mydata->hOldWndProc)return CallWindowProc(mydata->hOldWndProc, hWnd, uMsg, wp, lp);
    else return 0;
  }
  
  void _InitTlsData()
  {
    struct MYTLSDATA *mydata = new struct MYTLSDATA;
    tls_mydata = mydata;
    mydata->hMainWnd = NULL;
    mydata->hOldWndProc = NULL;
    mydata->hPopupMenu = NULL;
    
    mydata->numMenu = 0;
    mydata->bufFunc = NULL;
    mydata->bufUid = NULL;
    mydata->bLMouseDrag = true;
    mydata->bLMouseThru = true;
    mydata->xMin = -1;
    mydata->xMax = -1;
    mydata->yMin = -1;
    mydata->yMax = -1;
    mydata->bAntiFlicker = false;
  }
  
  void Init()
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    if(mydata->hOldWndProc!=NULL)return; //failed
    mydata->hMainWnd = findMainHWND();
    if(mydata->hMainWnd==NULL)return; //failed
    mydata->hOldWndProc = (WNDPROC)SetWindowLongPtr(mydata->hMainWnd, GWLP_WNDPROC, (LONG_PTR)(PopupWndProc));
    if(mydata->hOldWndProc==NULL)return; //failed
    mydata->hPopupMenu = CreatePopupMenu();
    
   // InsertMenu(hPopupMenu, 0, MF_BYPOSITION | MF_STRING, 8458, "Test");
  }
  
  void InsertNormalMenu(int uid, const char *str, value callback)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    char *strACP = NULL;
    if(mydata->hPopupMenu==NULL || !UTF8toCPACP(&strACP, str))return;
    InsertMenu(mydata->hPopupMenu, -1, MF_BYPOSITION | MF_STRING, uid, strACP);
    (mydata->numMenu)++;
    if(mydata->bufFunc==NULL)mydata->bufFunc = (AutoGCRoot**)malloc(sizeof(AutoGCRoot*) * mydata->numMenu);
    else mydata->bufFunc = (AutoGCRoot**)realloc((void *)mydata->bufFunc, sizeof(AutoGCRoot*) * mydata->numMenu);
    mydata->bufFunc[mydata->numMenu-1] = new AutoGCRoot(callback);
    if(mydata->bufUid==NULL)mydata->bufUid = (int *)malloc(sizeof(int) * mydata->numMenu);
    else mydata->bufUid = (int *)realloc((void *)mydata->bufUid, sizeof(int) * mydata->numMenu);
    mydata->bufUid[mydata->numMenu-1] = uid;
    delete strACP;
  }
  void InsertSeparatorMenu()
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    if(mydata->hPopupMenu==NULL)return;
    InsertMenu(mydata->hPopupMenu, -1, MF_BYPOSITION | MF_SEPARATOR, 0, 0);
    (mydata->numMenu)++;
    if(mydata->bufFunc==NULL)mydata->bufFunc = (AutoGCRoot**)malloc(sizeof(AutoGCRoot*) * mydata->numMenu);
    else mydata->bufFunc = (AutoGCRoot**)realloc((void *)mydata->bufFunc, sizeof(AutoGCRoot*) * mydata->numMenu);
    mydata->bufFunc[mydata->numMenu-1] = NULL;
    if(mydata->bufUid==NULL)mydata->bufUid = (int *)malloc(sizeof(int) * mydata->numMenu);
    else mydata->bufUid = (int *)realloc((void *)mydata->bufUid, sizeof(int) * mydata->numMenu);
    mydata->
    bufUid[mydata->numMenu-1] = 0;
  }
  
  void SetRadio(int iFirst, int iLast, int iCheck)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    CheckMenuRadioItem(mydata->hPopupMenu, iFirst, iLast, iCheck, MF_BYCOMMAND);
  }
  
  void SetEnable(int iPos, int iEnable)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    EnableMenuItem(mydata->hPopupMenu, iPos, MF_BYCOMMAND | iEnable);
  }
  
  void SetCheck(int iPos, bool bCheck)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    int ret = CheckMenuItem(mydata->hPopupMenu, iPos, MF_BYCOMMAND | (bCheck ? MF_CHECKED : MF_UNCHECKED));
  }
  
  void EnableLMouseDrag(bool bCheck)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    mydata->bLMouseDrag = bCheck;
  }
  
  void EnableLMouseThru(bool bThru)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    mydata->bLMouseThru = bThru;
  }
  
  void SetLMouseDragClip(int xMin, int xMax, int yMin, int yMax)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    mydata->xMin = xMin;
    mydata->xMax = xMax;
    mydata->yMin = yMin;
    mydata->yMax = yMax;
  }
  
  void SendWM_NCLBUTTONDOWN()
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    SendMessage(mydata->hMainWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
  }
  
  void EnableAntiFlicker(bool bEnable)
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)_InitTlsData();
    
    mydata->bAntiFlicker = bEnable;
  }
  
  void releaseBufUid()
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)return;
    
    free(mydata->bufUid);
    mydata->bufUid = NULL;
  }
  
  void releaseBufFunc()
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)return;
    
    for(int i=0;i<mydata->numMenu;i++)delete mydata->bufFunc[i];
    free(mydata->bufFunc);
    mydata->bufFunc = NULL;
  }
  
  void Exit()
  {
    struct MYTLSDATA *mydata = tls_mydata;
    if(mydata==NULL)return;
    
    if(mydata->hOldWndProc==NULL || mydata->hMainWnd==NULL)return; //failed
    SetWindowLongPtr(mydata->hMainWnd, GWLP_WNDPROC, (LONG_PTR)(mydata->hOldWndProc));
    mydata->hOldWndProc = NULL;
    mydata->hMainWnd = NULL;
    releaseBufUid();
    releaseBufFunc();
    mydata->numMenu = 0;
    if(mydata->hPopupMenu!=NULL)DestroyMenu(mydata->hPopupMenu);
  }
}