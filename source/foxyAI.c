#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "daTime.h"
#include "foxyAI.h"
#include "game.h"

int foxyPhase = 0;
double foxyStall = 0.0;

int foxyTime()
{
    time_t foxyTimer = time(NULL);

    static time_t foxylast = 0;
    if (foxylast == 0) foxylast = foxyTimer;

    static time_t foxykilllast = 0;
    if (foxykilllast == 0) foxykilllast = foxyTimer;

    static time_t foxyrunlast = 0;
    if (foxyrunlast == 0) foxyrunlast = foxyTimer;
    
    if (usingCams)
    {
        foxylast = foxyTimer;
        foxyStall = .83 + ((double)rand() * 17.43 / (double)RAND_MAX);
    }

    if (difftime(foxyTimer, foxylast) >= 5.01 + foxyStall)
    {
        if (!usingCams)
        {
            if (rand() % 20 <= foxyAILevel)
            {
                foxyPhase += 1;
            }
            foxyStall = 0;
        }
        foxylast = foxyTimer;
    }

    if (foxyPhase < 3)
    {
        foxykilllast = foxyTimer;
    }

    if (!foxyRunning)
    {
        foxyrunlast = foxyTimer;
    }

    if (difftime(foxyTimer, foxykilllast) >= 25)
    {
        foxyAttack();
        foxykilllast = foxyTimer;
    }

    if (difftime(foxyTimer, foxyrunlast) >= 2)
    {
        foxyAttack();
        foxyrunlast = foxyTimer;
    }
    
    return foxyPhase;
}