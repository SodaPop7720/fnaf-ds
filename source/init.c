#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "init.h"
#include "mainmenu.h"

int initEverything()
{
    // init stuff
    NF_Set2D(0, 0);
    NF_Set2D(1, 0);
    
    consoleDemoInit();
    printf("\n LOADING...");
    swiWaitForVBlank();

    nitroFSInit(NULL);
    NF_SetRootFolder("NITROFS");

    NF_Set2D(0, 0);
    NF_Set2D(1, 0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);
    
    NF_InitAffineBgSys(0);
    NF_InitAffineBgSys(1); 

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
    NF_InitSpriteSys(1);
    
    NF_InitTextSys(0);
    NF_InitTextSys(1);
    
    NF_InitRawSoundBuffers();
    NF_InitCmapBuffers();

    soundEnable();

    srand(time(NULL));

    // warning since it wont lemme make it its own thing

    NF_LoadTiledBg("bg/warning", "warning", 256, 256);
    NF_CreateTiledBg(0, 1, "warning");

    int timerTillMenu = 0;

    while (1)
    {
        timerTillMenu += 1;
        if (timerTillMenu == 300)
        {
            NF_DeleteTiledBg(0, 1);
            NF_UnloadTiledBg("warning");
            NF_ResetTiledBgBuffers();

            menuCreate();
            menuUpdate();
            break;
        }
        
        swiWaitForVBlank();
    }
    
    return 0;
}
