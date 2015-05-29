

#ifndef __TH32_h__
#define __TH32_h__

#include <windows.h>
#include <tlhelp32.h>

// ToolHelp32 function prototypes
typedef HANDLE (WINAPI* fCreateToolhelp32Snapshot)
(
  DWORD dwFlags,       
  DWORD th32ProcessID  
);

typedef BOOL (WINAPI* fProcess32First)
(
  HANDLE hSnapshot,      
  LPPROCESSENTRY32 lppe  
);
 
typedef BOOL (WINAPI* fProcess32Next)
(
  HANDLE hSnapshot,      
  LPPROCESSENTRY32 lppe  
);

typedef BOOL (WINAPI* fModule32First)
(
  HANDLE hSnapshot,     
  LPMODULEENTRY32 lpme  
);
 
typedef BOOL (WINAPI* fModule32Next)
(
  HANDLE hSnapshot,     
  LPMODULEENTRY32 lpme  
);

extern fCreateToolhelp32Snapshot    _CreateToolhelp32Snapshot;
extern fProcess32First              _Process32First;
extern fProcess32Next               _Process32Next;
extern fModule32First               _Module32First;
extern fModule32Next                _Module32Next;

BOOL GetTh32();

#endif