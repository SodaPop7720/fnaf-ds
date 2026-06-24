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
#include "bonnieAI.h"
#include "game.h"

int bonnieLocation = 0;

/* 
0 = stage
1 = dining area
2 = backstage
3 = hall
4 = closet
5 = corner
6 = door
7 = he gonna kill u
*/

int bonnieTime()
{
    time_t bonnieTimer = time(NULL);

    static time_t bonnielast = 0;
    if (bonnielast == 0) bonnielast = bonnieTimer;
    
    if (difftime(bonnieTimer, bonnielast) >= 4.97)
    {
        if (rand() % 20 < bonnieAILevel)
        {
            NF_PlayRawSound(10, 50, 64, false, 0);
            switch(bonnieLocation)
            {
                case 0: bonnieLocation = (rand() % 2) + 1; break;
                case 1: bonnieLocation = (rand() % 2) + 2; break;
                case 2: if (rand() % 2 == 0) bonnieLocation = 1; else bonnieLocation = 3; break;
                case 3: bonnieLocation = (rand() % 2) + 4; break;
                case 4: if (rand() % 2 == 0) bonnieLocation = (rand() % 2) + 5; else bonnieLocation = 3; break;
                case 5: if (rand() % 2 == 0) bonnieLocation = 4; else bonnieLocation = 6; break;
                case 6: if (ldoor) bonnieLocation = 1; else bonnieLocation = 7; break;
                case 7: if (usingCams) gotJumped = true; whoGotU = "bonnie"; break;
            }

            if(usingCams)
                updateCams();
        }

        bonnielast = bonnieTimer;
    }
    
    return bonnieLocation;
}