#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#include "daTime.h"
#include "game.h"

int timeAM = 0;

int daTimeShit()
{
    static time_t last = 0;
    time_t now = time(NULL);
    if (last == 0) last = now;

    if (difftime(now, last) >= 90.0)
    {
        timeAM += 1;
        last = now;
    }

    return 0;
}
