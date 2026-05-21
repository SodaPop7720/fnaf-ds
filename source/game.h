#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <nds.h>

extern int bonnieAILevel;
extern int chicaAILevel;
extern int foxyAILevel;

extern bool foxyRunning;

extern bool ldoor;
extern bool rdoor;

extern bool usingCams;
extern const char* camName;

extern bool gotJumped;
extern const char* whoGotU;

extern int foxyAttack();
extern int updateCams();

int onCreate();
int onPostCreate();
int onUpdate();
int noScreenRefresh();

#endif 