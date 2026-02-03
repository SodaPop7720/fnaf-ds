#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "newspaper.h"
#include "game.h"

int newspaperStuff()
{
    NF_LoadTiledBg("bg/newspaper", "newspaper", 256, 256);
    NF_CreateTiledBg(0, 1, "newspaper");

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
        if (timerTillGame == 300)
        {
            NF_DeleteTiledBg(0, 1);
            NF_UnloadTiledBg("newspaper");
            NF_ResetTiledBgBuffers();

            break;
        }
        
        swiWaitForVBlank();
    }
    soundKill(0);
    soundKill(1);
    NF_UnloadRawSound(0);
    NF_UnloadRawSound(1);
    NF_ResetRawSoundBuffers();
    
    onCreate();
    onPostCreate();
    onUpdate();

    return 0;
}
