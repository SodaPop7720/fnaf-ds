#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "game.h"
#include "nightnumber.h"
#include "savedata.h"

int coolSwagTimer = 0;

int showNightNumber()
{
    NF_LoadSpriteGfx("sprite/nightNumber", 0, 64, 32);
    NF_LoadSpritePal("sprite/nightNumber", 0);

    NF_VramSpriteGfx(0, 0, 0, true);
    NF_VramSpritePal(0, 0, 0);

    NF_CreateSprite(0, 0, 0, 0, 96, 80);
    NF_SpriteFrame(0, 0, daSaveData.curNight - 1);
    NF_EnableSpriteRotScale(0, 0, 0, false);
    
    NF_LoadRawSound("sfx/blip", 0, 11025, 0);
    NF_PlayRawSound(0, 100, 64, false, 0);

    while (coolSwagTimer < 150)
    {
        coolSwagTimer++;
        
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        swiWaitForVBlank();

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }
    
    NF_UnloadSpriteGfx(0);
    NF_UnloadSpritePal(0);
    NF_FreeSpriteGfx(0, 0);
    NF_DeleteSprite(0, 0);
    
    NF_ResetRawSoundBuffers();
    
    coolSwagTimer = 0;

    onCreate();
    onPostCreate();
    onUpdate();

    return 0;
}
