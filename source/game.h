#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <nds.h>

extern int foxyAILevel;

extern bool usingCams;

int onCreate();
int onPostCreate();
int onUpdate();
int noScreenRefresh();

#endif 