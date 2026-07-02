#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "game.h"
#include "golden.h"

int goldentimer = 0;

int goldenJumpscare() 
{
    gotJumped = false;

    NF_LoadTiledBg("bg/goldenFreddyJumpscare", "jump", 256, 256);
    NF_CreateTiledBg(0, 0, "jump");
    
    NF_LoadRawSound("sfx/gfreddyscare", 0, 11025, 0); 
    NF_PlayRawSound(0, 100, 64, false, 0);

    while (goldentimer < 60)
    {
        goldentimer += 1;
        swiWaitForVBlank();
    }

    return 0;
}
