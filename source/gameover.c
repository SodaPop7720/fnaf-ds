#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "a.h"
#include "game.h"
#include "gameover.h"

int gameOver() 
{
    NF_LoadTiledBg("bg/static0", "static0", 256, 256);
    NF_LoadTiledBg("bg/static1", "static1", 256, 256);
    NF_LoadTiledBg("bg/static2", "static2", 256, 256);
    NF_LoadTiledBg("bg/static3", "static3", 256, 256);
    
    NF_CreateTiledBg(0, 2, "static0");
    NF_CreateTiledBg(1, 2, "static0");
    
    soundKill(0);
    NF_UnloadRawSound(0);
    NF_ResetRawSoundBuffers();
    
    NF_LoadRawSound("sfx/kill", 7, 11025, 0); 
    NF_PlayRawSound(7, 100, 64, false, 0);

    while (1)
    {
        staticTimer++;
        const char *curStatic = "static0";
        switch (staticTimer & 3)
        {
            case 0: curStatic = "static0"; break;
            case 1: curStatic = "static1"; break;
            case 2: curStatic = "static2"; break;
            case 3: curStatic = "static3"; break;
        }
        
        swiWaitForVBlank();

        NF_CreateTiledBg(0, 2, curStatic);
        NF_CreateTiledBg(1, 2, curStatic);

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    return 0;
}
