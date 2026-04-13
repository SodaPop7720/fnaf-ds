#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <nds.h>

extern int foxyAILevel;

extern bool foxyRunning;

extern bool usingCams;
extern const char* camName;

extern int foxyAttack();

int onCreate();
int onPostCreate();
int onUpdate();
int noScreenRefresh();

#endif 