#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "custom.h"
#include "nightnumber.h"

int custombrightness = -16;

int customCreate()
{
    NF_LoadTiledBg("bg/customNightBg", "cn", 256, 256);
    NF_CreateTiledBg(0, 1, "cn");
    
    int custombrightness = -16;
    while (custombrightness < 0)
    {
        custombrightness += 1;
        setBrightness(3, custombrightness);
        
        swiWaitForVBlank();
    }

    return 0;
}

int customUpdate()
{
    while (custombrightness < 0)
    {
        swiWaitForVBlank();
    }

    while (1)
    {
        swiWaitForVBlank();
    }

    return 0;
}
