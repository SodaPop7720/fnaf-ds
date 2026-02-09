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

int foxyTime()
{
    static time_t last = 0;
    time_t now = time(NULL);
    if (last == 0) last = now;
    
    if (usingCams)
        last = now;

    if (difftime(now, last) >= 5.01)
    {
        if (!usingCams)
        {
            if (rand() % 20 <= foxyAILevel)
            {
                foxyPhase += 1;
            }
        }
        last = now;
    }
    
    return foxyPhase;
}