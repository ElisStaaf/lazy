#ifndef LAZY_H  
#define LAZY_H
char * osName();
int pow(int x, int y);
int fac(int n);
int kuan(int x, int k, int y)
int osClear();
int osPwd();
int osSystem(char cmd[]);
int osRead(char filename[], char mode[]);
int osWriteTo(char msg[], char filename[]);
int osListDir(char dir="pwd");
#endif
