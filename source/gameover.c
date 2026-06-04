#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "a.h"
#include "game.h"
#include "gameover.h"
#include "mainmenu.h"

int gameOver() 
{
    gotJumped = false;

    NF_LoadTiledBg("bg/static0", "static0", 256, 256);
    NF_LoadTiledBg("bg/static1", "static1", 256, 256);
    NF_LoadTiledBg("bg/static2", "static2", 256, 256);
    NF_LoadTiledBg("bg/static3", "static3", 256, 256);
    
    NF_CreateTiledBg(0, 2, "static0");
    NF_CreateTiledBg(1, 2, "static0");
    
    NF_LoadRawSound("sfx/kill", 0, 11025, 0); 
    NF_PlayRawSound(0, 100, 64, false, 0);

    int brightness = 0;
    staticTimer = 0;

    while (staticTimer < 300)
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

    while (brightness > -16)
    {
        brightness -= 1;
        setBrightness(3, brightness);

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
    
    NF_DeleteTiledBg(0, 2);
    NF_DeleteTiledBg(1, 2);
    NF_UnloadTiledBg("static0");
    NF_UnloadTiledBg("static1");
    NF_UnloadTiledBg("static2");
    NF_UnloadTiledBg("static3");
    NF_ResetTiledBgBuffers();
    
    NF_LoadTiledBg("bg/gameOver", "gameOver", 256, 256);
    NF_CreateTiledBg(0, 1, "gameOver");

    gameOverImage();

    return 0;
}

int gameOverImage()
{
    int brightness = -16;
    int timerTillMenu = 0;

    while (brightness < 0)
    {
        brightness += 1;
        setBrightness(3, brightness);

        swiWaitForVBlank();
    }

    while (timerTillMenu < 300)
    {
        timerTillMenu += 1;
        swiWaitForVBlank();
    }

    NF_DeleteTiledBg(0, 1);
    NF_UnloadTiledBg("gameOver");
    NF_ResetTiledBgBuffers();

    NF_ResetRawSoundBuffers();

    menuCreate();
    menuUpdate();

    return 0;
}
