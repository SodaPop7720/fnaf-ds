#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "ending.h"
#include "mainmenu.h"
#include "savedata.h"

int endingStuff()
{
    NF_LoadRawSound("sfx/musicbox", 0, 11025, 0);
    NF_PlayRawSound(0, 100, 64, true, 0);

    switch (daSaveData.curNight - 1)
    {
        case 5: NF_LoadTiledBg("bg/ending", "ending", 256, 256); break;
        case 6: NF_LoadTiledBg("bg/ending6", "ending", 256, 256); break;
        case 7: NF_LoadTiledBg("bg/ending7", "ending", 256, 256); break;
    }
    NF_CreateTiledBg(0, 1, "ending");

    int timerTillGame = 0;
    
    int brightness = -16;
    while (brightness < 0)
    {
        brightness += 1;
        setBrightness(3, brightness);
        
        swiWaitForVBlank();
    }

    while (1)
    {
        timerTillGame += 1;
        if (timerTillGame == 1200)
        {
            NF_DeleteTiledBg(0, 1);
            NF_UnloadTiledBg("ending");
            NF_ResetTiledBgBuffers();

            break;
        }
        
        swiWaitForVBlank();
    }

    soundKill(0);
    NF_UnloadRawSound(0);
    NF_ResetRawSoundBuffers();

    menuCreate();
    menuUpdate();

    return 0;
}
