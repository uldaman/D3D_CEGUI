#define WIN32_LEAN_AND_MEAN

#ifndef _MAIN_H
#define _MAIN_H

char *GetDirectoryFile(char *filename);
void *DetourFunc(BYTE *src, const BYTE *dst, const int len);
bool RetourFunc(BYTE *src, BYTE *restore, const int len);

#endif