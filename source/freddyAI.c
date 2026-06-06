#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "daTime.h"
#include "bonnieAI.h"
#include "chicaAI.h"
#include "freddyAI.h"
#include "game.h"

int freddyLocation = 0;
int freddyCountdown = 1000;

/* 
0 = stage
1 = dining area
2 = restroom
3 = kitchen
4 = hall
5 = corner
6 = he gonna kill u
*/

int freddyTime()
{
    time_t freddyTimer = time(NULL);

    static time_t freddylast = 0;
    static time_t freddykilllast = 0;

    if (freddylast == 0) freddylast = freddyTimer;
    if (freddykilllast == 0) freddykilllast = freddyTimer;
    
    if (difftime(freddyTimer, freddylast) >= 3.02 && bonnieLocation > 0 && chicaLocation > 0)
    {
        if (rand() % 20 < freddyAILevel && !usingCams)
        {
            if (freddyLocation <= 4)
            {
                freddyMove();
            }
            else
            {
                if (freddyLocation == 5 && strstr(camName, "cam4b") == NULL)
                {
                    if (rdoor) freddyLocation -= 1; else freddyLocation += 1;
                }
            }
        }

        freddylast = freddyTimer;
    }

    if (difftime(freddyTimer, freddykilllast) >= 1)
    {
        if (rand() % 4 == 0 && freddyLocation > 5) gotJumped = true;
        freddykilllast = freddyTimer;
    }
    
    return freddyLocation;
}

int freddyMove()
{
    freddyCountdown -= 100 * freddyAILevel;
    while (1)
    {
        freddyCountdown -= 1;
        if (freddyCountdown <= 0 && !usingCams)
        {
            NF_PlayRawSound(9, 100, 64, false, 0);
            freddyLocation += 1;

            if(usingCams)
                updateCams();
            
            freddyCountdown = 1000;
            break;
        }
    }

    return 0;
}