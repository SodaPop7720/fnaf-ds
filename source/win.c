#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "a.h"
#include "ending.h"
#include "game.h"
#include "mainmenu.h"
#include "nightNumber.h"
#include "savedata.h"
#include "win.h"

int sixamtimer = 0;
float sixamtexty = 0.0;

int sixAMScreen() 
{
    gotJumped = false;

    NF_LoadTiledBg("bg/6am", "6am", 256, 256);
    NF_CreateTiledBg(0, 0, "6am");

    NF_LoadSpriteGfx("sprite/6amnumbers", 0, 64, 64);
    NF_LoadSpritePal("sprite/6amnumbers", 0);

    NF_VramSpriteGfx(0, 0, 0, false);
    NF_VramSpritePal(0, 0, 0);
    
    NF_CreateSprite(0, 0, 0, 0, 96, 80);
    NF_SpriteLayer(0, 0, 1);
    
    NF_LoadRawSound("sfx/6am", 0, 11025, 0); 
    NF_PlayRawSound(0, 100, 64, false, 0);

    NF_LoadRawSound("sfx/cheer", 1, 11025, 0); 

    sixamtimer = 0;
    sixamtexty = 0.0;

    while (sixamtimer < 90)
    {
        sixamtimer++;

        swiWaitForVBlank();

        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    while (sixamtexty < 31)
    {
        sixamtexty += 0.1;
        NF_MoveSprite(0, 0, 96, 80 - sixamtexty);

        swiWaitForVBlank();

        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }
    
    NF_PlayRawSound(1, 100, 64, false, 0);

    while (sixamtimer < 330)
    {
        sixamtimer++;

        swiWaitForVBlank();

        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    NF_DeleteTiledBg(0, 0);
    NF_UnloadTiledBg("6am");
    NF_ResetTiledBgBuffers();
    
    NF_UnloadSpriteGfx(0);
    NF_UnloadSpritePal(0);
    NF_FreeSpriteGfx(0, 0);
    NF_DeleteSprite(0, 0);
    
    NF_ResetSpriteBuffers();

    soundKill(0);
    NF_ResetRawSoundBuffers();

    if (daSaveData.curNight < 8)
    {
        daSaveData.curNight += 1;
        saveGame();
    }

    if (daSaveData.curNight > 5)
    {
        endingStuff();
    }
    else
    {
        showNightNumber(); 
    }

    return 0;
}
