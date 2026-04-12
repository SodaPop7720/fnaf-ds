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
    static time_t foxylast = 0;
    time_t foxynow = time(NULL);
    if (foxylast == 0) foxylast = foxynow;
    
    if (usingCams)
    {
        foxylast = foxynow;
        foxyStall = .83 + ((double)rand() * 17.43 / (double)RAND_MAX);
    }

    if (difftime(foxynow, foxylast) >= 5.01 + foxyStall)
    {
        if (!usingCams)
        {
            if (rand() % 20 <= foxyAILevel)
            {
                foxyPhase += 1;
            }
        }
        foxylast = foxynow;
    }
    
    return foxyPhase;
}