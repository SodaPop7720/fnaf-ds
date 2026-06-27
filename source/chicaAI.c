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
#include "chicaAI.h"
#include "game.h"

int chicaLocation = 0;

/* 
0 = stage
1 = dining area
2 = restroom
3 = kitchen
4 = hall
5 = corner
6 = door
7 = she gonna kill u
*/

time_t chicaTimer = 0;
static time_t chicalast = 0;

int chicaLoad()
{
    chicalast = chicaTimer;
    return 0;
}

int chicaTime()
{
    chicaTimer = time(NULL);

    chicalast = 0;
    if (chicalast == 0) chicalast = chicaTimer;
    
    if (difftime(chicaTimer, chicalast) >= 4.98)
    {
        if (rand() % 20 < chicaAILevel)
        {
            NF_PlayRawSound(10, 50, 64, false, 0);
            switch(chicaLocation)
            {
                case 0: chicaLocation = 1; break;
                case 1: chicaLocation = (rand() % 2) + 2; break;
                case 2: chicaLocation = (rand() % 2) + 3; break;
                case 3: if (rand() % 2 == 0) chicaLocation = 2; else chicaLocation = 4; break;
                case 4: if (rand() % 2 == 0) chicaLocation = 1; else chicaLocation = 5; break;
                case 5: if (rand() % 2 == 0) chicaLocation = 4; else chicaLocation = 6; break;
                case 6: if (rdoor) chicaLocation = 4; else chicaLocation = 7; break;
                case 7: if (usingCams) gotJumped = true; whoGotU = "chica"; break;
            }

            if(usingCams)
                updateCams();
        }

        chicalast = chicaTimer;
    }
    
    return chicaLocation;
}