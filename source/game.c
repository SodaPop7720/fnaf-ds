#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "bonnieAI.h"
#include "chicaAI.h"
#include "custom.h"
#include "daTime.h"
#include "foxyAI.h"
#include "freddyAI.h"
#include "game.h"
#include "gameover.h"
#include "golden.h"
#include "savedata.h"
#include "win.h"

// Not my best code ever I know the codes a little bad yeah

int freddyAILevel = 0;
int bonnieAILevel = 0;
int chicaAILevel = 0;
int foxyAILevel = 0;

const char* whoGotU = "freddy";

int onCreate()
{
    NF_Set2D(0, 0);

    NF_InitTiledBgBuffers();
    NF_InitTiledBgSys(0);
    NF_InitTiledBgSys(1);

    NF_InitSpriteBuffers();
    NF_InitSpriteSys(0);
    NF_InitSpriteSys(1);
    
    NF_InitTextSys(0);
    NF_InitTextSys(1);

    NF_LoadSpriteGfx("sprite/loading", 1, 64, 64);
    NF_LoadSpritePal("sprite/loading", 1);

    NF_VramSpriteGfx(0, 1, 1, false);
    NF_VramSpritePal(0, 1, 1);
    
    NF_CreateSprite(0, 1, 1, 1, 192, 128);
    
    swiWaitForVBlank();
    
    NF_SpriteOamSet(0);
    NF_SpriteOamSet(1);
    oamUpdate(&oamMain);
    oamUpdate(&oamSub);

    NF_LoadTiledBg("bg/office", "office_off", 512, 512);
    NF_LoadTiledBg("bg/officeLeftLight", "office_left", 512, 512);
    NF_LoadTiledBg("bg/officeRightLight", "office_right", 512, 512);
    NF_LoadTiledBg("bg/officeBonnie", "office_bonnie", 512, 512);
    NF_LoadTiledBg("bg/officeChica", "office_chica", 512, 512);
    NF_LoadTiledBg("bg/officePowerOut", "office_power", 512, 512);
    NF_LoadTiledBg("bg/officePowerOutFreddy", "office_powerfred", 512, 512);
    
    NF_LoadTiledBg("bg/nothing", "goldenFreddyOff", 512, 512);
    NF_LoadTiledBg("bg/goldenFreddy", "goldenFreddy", 512, 512);

    NF_LoadTiledBg("bg/nothing", "doors_off", 512, 512);
    NF_LoadTiledBg("bg/LDoor", "doors_L", 512, 512);
    NF_LoadTiledBg("bg/RDoor", "doors_R", 512, 512);
    NF_LoadTiledBg("bg/LRDoor", "doors_LR", 512, 512);
    
    NF_LoadTiledBg("bg/cams/1a", "cam1a", 512, 512);
    NF_LoadTiledBg("bg/cams/1a_fbc", "cam1a_fbc", 512, 512);
    NF_LoadTiledBg("bg/cams/1a_fb", "cam1a_fb", 512, 512);
    NF_LoadTiledBg("bg/cams/1a_fc", "cam1a_fc", 512, 512);
    NF_LoadTiledBg("bg/cams/1a_f", "cam1a_f", 512, 512);

    NF_LoadTiledBg("bg/cams/1b", "cam1b", 512, 512);
    NF_LoadTiledBg("bg/cams/1b_b", "cam1b_b", 512, 512);
    NF_LoadTiledBg("bg/cams/1b_c", "cam1b_c", 512, 512);
    NF_LoadTiledBg("bg/cams/1b_f", "cam1b_f", 512, 512);

    NF_LoadTiledBg("bg/cams/1c", "cam1c", 512, 512);
    NF_LoadTiledBg("bg/cams/1c_1", "cam1c_1", 512, 512);
    NF_LoadTiledBg("bg/cams/1c_2", "cam1c_2", 512, 512);
    NF_LoadTiledBg("bg/cams/1c_3", "cam1c_3", 512, 512);

    NF_LoadTiledBg("bg/cams/2a", "cam2a", 512, 512);
    NF_LoadTiledBg("bg/cams/2a_b", "cam2a_b", 512, 512);
    
    NF_LoadTiledBg("bg/cams/2b", "cam2b", 512, 512);
    NF_LoadTiledBg("bg/cams/2b_b", "cam2b_b", 512, 512);
    NF_LoadTiledBg("bg/cams/2b_g", "cam2b_g", 512, 512);

    NF_LoadTiledBg("bg/cams/3", "cam3", 512, 512);
    NF_LoadTiledBg("bg/cams/3_b", "cam3_b", 512, 512);

    NF_LoadTiledBg("bg/cams/4a", "cam4a", 512, 512);
    NF_LoadTiledBg("bg/cams/4a_c", "cam4a_c", 512, 512);
    NF_LoadTiledBg("bg/cams/4a_f", "cam4a_f", 512, 512);
    
    NF_LoadTiledBg("bg/cams/4b", "cam4b", 512, 512);
    NF_LoadTiledBg("bg/cams/4b_c", "cam4b_c", 512, 512);
    NF_LoadTiledBg("bg/cams/4b_f", "cam4b_f", 512, 512);
    
    NF_LoadTiledBg("bg/cams/5", "cam5", 512, 512);
    NF_LoadTiledBg("bg/cams/5_b", "cam5_b", 512, 512);
    
    NF_LoadTiledBg("bg/cams/6", "cam6", 512, 512);
    
    NF_LoadTiledBg("bg/cams/7", "cam7", 512, 512);
    NF_LoadTiledBg("bg/cams/7_c", "cam7_c", 512, 512);
    NF_LoadTiledBg("bg/cams/7_f", "cam7_f", 512, 512);
    
    NF_LoadTiledBg("bg/cams/6", "camNothing", 512, 512);

    NF_LoadTiledBg("bg/minimap", "minimap", 256, 256);
    
    NF_LoadSpriteGfx("sprite/timeAMspr", 0, 64, 32);
    NF_LoadSpritePal("sprite/timeAMspr", 0);

    NF_VramSpriteGfx(0, 0, 0, true);
    NF_VramSpritePal(0, 0, 0);
    
    NF_LoadTextFont("fnt/default", "top", 256, 256, 0);
    NF_LoadTextFont("fnt/default", "bottom", 256, 256, 0);
    
    NF_CreateTiledBg(0, 3, "office_off");
    NF_ScrollBg(0, 2, 100, 160);
    NF_ScrollBg(0, 3, 100, 160);
    NF_CreateTiledBg(0, 1, "doors_off");
    NF_CreateTiledBg(0, 2, "goldenFreddyOff");
    NF_CreateTiledBg(1, 3, "minimap");
    NF_HideBg(1, 3);

    NF_CreateSprite(0, 0, 0, 0, 192, 0);
    NF_SpriteFrame(0, 0, 0);
    NF_EnableSpriteRotScale(0, 0, 0, false);
    
    NF_CreateTextLayer(0, 0, 0, "top");
    NF_CreateTextLayer(1, 0, 0, "bottom");

    REG_BLDALPHA = 0x0F | (0x0F << 16);

    return 0;
}

bool showHints = true;

bool goldenFreddyCanSpawn = false;
bool goldenFreddy = false;
bool goldenFreddyInOffice = false;
int goldenFreddyKillTimer = 0;

time_t gfTimer = 0;
static time_t gflast = 0;

int onPostCreate()
{
    if (daSaveData.curNight > 1) showHints = false;

    goldenFreddyCanSpawn = false;
    goldenFreddy = false;
    goldenFreddyInOffice = false;

    gfTimer = time(NULL);
    gflast = gfTimer;

    freddyLoad();
    bonnieLoad();
    chicaLoad();
    foxyLoad();

    NF_UnloadSpriteGfx(1);
    NF_UnloadSpritePal(1);
    NF_FreeSpriteGfx(0, 1);
    NF_DeleteSprite(0, 1);

    NF_LoadRawSound("sfx/fan", 0, 11025, 0);
    NF_PlayRawSound(0, 100, 64, true, 0);
    
    NF_LoadRawSound("sfx/door", 2, 11025, 0);
    NF_LoadRawSound("sfx/flip", 3, 11025, 0);
    NF_LoadRawSound("sfx/blip", 4, 11025, 0);
    NF_LoadRawSound("sfx/knock", 5, 11025, 0);
    NF_LoadRawSound("sfx/run", 6, 11025, 0);
    NF_LoadRawSound("sfx/window", 7, 22050, 0);
    NF_LoadRawSound("sfx/error", 8, 11025, 0);
    NF_LoadRawSound("sfx/freddy", 9, 11025, 0);
    NF_LoadRawSound("sfx/walk", 10, 11025, 0);
    NF_LoadRawSound("sfx/power", 11, 11025, 0);
    NF_LoadRawSound("sfx/musicbox", 12, 11025, 0);
    NF_LoadRawSound("sfx/gfreddy", 13, 11025, 0);

    whoGotU = "freddy";

    switch (daSaveData.curNight) // ai levels
    {
        case 1:
            freddyAILevel = 0;
            bonnieAILevel = 0;
            chicaAILevel = 0;
            foxyAILevel = 0;
            break;
        case 2:
            freddyAILevel = 0;
            bonnieAILevel = 3;
            chicaAILevel = 1;
            foxyAILevel = 1;
            break;
        case 3:
            freddyAILevel = 1;
            bonnieAILevel = 0;
            chicaAILevel = 5;
            foxyAILevel = 2;
            break;
        case 4:
            freddyAILevel = (rand() % 2) + 1;
            bonnieAILevel = 2;
            chicaAILevel = 4;
            foxyAILevel = 6;
            break;
        case 5:
            freddyAILevel = 3;
            bonnieAILevel = 5;
            chicaAILevel = 7;
            foxyAILevel = 9;
            break;
        case 6:
            freddyAILevel = 4;
            bonnieAILevel = 10;
            chicaAILevel = 12;
            foxyAILevel = 16;
            break;
        case 7:
            freddyAILevel = freddyCustomAI;
            bonnieAILevel = bonnieCustomAI;
            chicaAILevel = chicaCustomAI;
            foxyAILevel = foxyCustomAI;
            break;
    }

    return 0;
}

int officeX = 50;
float camX = 25;
int scrollSpeed = 3;
float power = 100;
int usage = 1;

bool foxyRunning = false;

bool usingCams = false;
float camSpeed = 0.2;
const char* camName = "cam1a_fbc";
bool camGoLeft = false;

bool lookingLeft = true;
bool ldoor = false;
bool ldoorlight = false;
bool rdoor = false;
bool rdoorlight = false;
bool prev_ldoor = false;
bool prev_ldoorlight = false;
bool prev_rdoor = false;
bool prev_rdoorlight = false;

bool gotJumped = false;
bool powerOut = false;

touchPosition touch_position = { 0 };

int foxyAttack()
{
    if (ldoor)
    {
        NF_PlayRawSound(5, 100, 64, false, 0);
        foxyPhase = 0;
        foxyRunning = false;
    }
    else
    {
        gotJumped = true; 
        whoGotU = "foxy";
    }
    
    return 0;
}

int checkAnimatronics() // I know theres prolly a better way to do this but idgaf
{
    if (strstr(camName, "cam1a") != NULL)
    {
        if (bonnieLocation == 0 && chicaLocation == 0) 
        {
            camName = "cam1a_fbc";
        } 
        else if (chicaLocation == 0) 
        {
            camName = "cam1a_fc";
        }
        else if (bonnieLocation == 0) 
        {
            camName = "cam1a_fb";
        }
        else if (freddyLocation == 0)
        {
            camName = "cam1a_f";
        }
        else
        {
            camName = "cam1a";
        }
    }
    if (strstr(camName, "cam1b") != NULL)
    {
        if (bonnieLocation == 1) 
        {
            camName = "cam1b_b";
        }
        else if (chicaLocation == 1) 
        {
            camName = "cam1b_c";
        }
        else if (freddyLocation == 1) 
        {
            camName = "cam1b_f";
        }
        else 
        {
            camName = "cam1b";
        }
    }
    if (strstr(camName, "cam1c") != NULL)
    {
        switch(foxyPhase)
        {
            case 0: camName = "cam1c"; break;
            case 1: camName = "cam1c_1"; break;
            case 2: camName = "cam1c_2"; break;
            default: camName = "cam1c_3"; break;
        }
    }
    if (strstr(camName, "cam2a") != NULL)
    {
        if (bonnieLocation == 3) 
        {
            camName = "cam2a_b";
        }
        else 
        {
            camName = "cam2a";
        }
    }
    if (strstr(camName, "cam2b") != NULL)
    {
        if (bonnieLocation == 5) 
        {
            camName = "cam2b_b";
        }
        else if (goldenFreddyCanSpawn)
        {
            camName = "cam2b_g";
            goldenFreddy = true;
        }
        else 
        {
            camName = "cam2b";
        }
    }
    if (strstr(camName, "cam3") != NULL)
    {
        if (bonnieLocation == 4) 
        {
            camName = "cam3_b";
        }
        else 
        {
            camName = "cam3";
        }
    }
    if (strstr(camName, "cam4a") != NULL)
    {
        if (chicaLocation == 4) 
        {
            camName = "cam4a_c";
        }
        else if (freddyLocation == 4) 
        {
            camName = "cam4a_f";
        }
        else 
        {
            camName = "cam4a";
        }
    }
    if (strstr(camName, "cam4b") != NULL)
    {
        if (chicaLocation == 5) 
        {
            camName = "cam4b_c";
        }
        else if (freddyLocation == 5)
        {
            camName = "cam4b_f";
        }
        else
        {
            camName = "cam4b";
        }
    }
    if (strstr(camName, "cam5") != NULL)
    {
        if (bonnieLocation == 2)
        {
            camName = "cam5_b";
        }
        else 
        {
            camName = "cam5";
        }
    }
    if (strstr(camName, "cam7") != NULL)
    {
        if (chicaLocation == 2) 
        {
            camName = "cam7_c";
        }
        else if (freddyLocation == 2) 
        {
            camName = "cam7_f";
        }
        else 
        {
            camName = "cam7";
        }
    }
    
    if (foxyPhase > 2 && strstr(camName, "cam2a") != NULL && usingCams)
    {
        camName = "camNothing";
        foxyRunning = true;
        NF_PlayRawSound(6, 100, 64, false, 0);
    }

    return 0;
}

int updateCams()
{
    checkAnimatronics();
    NF_CreateTiledBg(0, 3, camName);

    return 0;
}

int ohNoPowerOut()
{
    goldenFreddyCanSpawn = false;
    goldenFreddy = false;
    goldenFreddyInOffice = false;
    goldenFreddyKillTimer = 0;

    if (usingCams)
    {
        NF_PlayRawSound(3, 127, 64, false, 0);
        usingCams = false;

        NF_ShowBg(0, 1);
        NF_HideBg(0, 2);
        NF_HideBg(1, 3);
    }

    soundKill(0);

    if (ldoor || rdoor) NF_PlayRawSound(2, 127, 64, false, 0);

    ldoor = false;
    rdoor = false;

    ldoorlight = false;
    rdoorlight = false;
    prev_ldoorlight = ldoorlight;
    prev_rdoorlight = rdoorlight;
    
    NF_MoveSprite(0, 0, 256, 0);

    NF_PlayRawSound(11, 100, 64, false, 0);
    NF_CreateTiledBg(0, 3, "office_power");

    return 0;
}

int powerOutTimer = 0;
int powerOutEventFails = 0;
int powerOutPhase = 0;

int powerOutEvents()
{
    if (powerOutPhase == 0)
    {
        if (powerOutTimer < 300)
        {
            powerOutTimer += 1;
            return 0;
        }

        if (rand() % 5 == 0 || powerOutEventFails == 3)
        {
            powerOutEventFails = 0;
        }
        else
        {
            powerOutEventFails += 1;
            powerOutTimer = 0;
            return 0;
        }

        NF_PlayRawSound(12, 100, 64, false, 0);

        powerOutPhase = 1;
        powerOutTimer = 0;
        return 0;
    }
    if (powerOutPhase == 1)
    {
        if (powerOutTimer < 300)
        {
            powerOutTimer += 1;

            if (rand() % 2 == 0)
                NF_CreateTiledBg(0, 3, "office_powerfred");
            else
                NF_CreateTiledBg(0, 3, "office_power");
                
            return 0;
        }

        if (rand() % 5 == 0 || powerOutEventFails == 3)
        {
            powerOutEventFails = 0;
        }
        else
        {
            powerOutEventFails += 1;
            powerOutTimer = 0;
            return 0;
        }

        soundDisable();
        soundEnable();
        
        NF_CreateTiledBg(0, 3, "camNothing");

        powerOutPhase = 2;
        powerOutTimer = 0;
        return 0;
    }
    if (powerOutPhase == 2)
    {
        if (powerOutTimer < 120)
        {
            powerOutTimer += 1;
            return 0;
        }

        if (rand() % 5 == 0 || powerOutEventFails == 9)
        {
            powerOutEventFails = 0;
        }
        else
        {
            powerOutEventFails += 1;
            powerOutTimer = 0;
            return 0;
        }

        powerOutPhase = 3;
        powerOutTimer = 0;
        whoGotU = "freddy";

        return 0;
    }
    return 0;
}

int onUpdate()
{
    while (1)
    {
        scanKeys();
        uint16_t keys_down = keysDown();
        uint16_t keys_held = keysHeld();

        if (camGoLeft)
            camX -= camSpeed;
        else
            camX += camSpeed;
        if (camX < 25)
            camGoLeft = false;
        if (camX > 103)
            camGoLeft = true;

        if (!usingCams)
        {
            if (keys_held & KEY_L)
            {
                lookingLeft = true;
                ldoorlight = false;
                rdoorlight = false;
                officeX -= scrollSpeed;
                if (officeX < 20)
                    officeX = 20;
            }
            
            if (keys_held & KEY_R)
            {
                lookingLeft = false;
                ldoorlight = false;
                rdoorlight = false;
                officeX += scrollSpeed;
                if (officeX > 103)
                    officeX = 103;
            }

            if (keys_held & KEY_LEFT)
            {
                lookingLeft = true;
                ldoorlight = false;
                rdoorlight = false;
                officeX -= scrollSpeed;
                if (officeX < 25)
                    officeX = 25;
            }
        
            if (keys_held & KEY_RIGHT)
            {
                lookingLeft = false;
                ldoorlight = false;
                rdoorlight = false;
                officeX += scrollSpeed;
                if (officeX > 103)
                    officeX = 103;
            }

            if (keys_down & KEY_A && !powerOut)
            {
                if (bonnieLocation <= 6 && chicaLocation <= 6) NF_PlayRawSound(2, 127, 64, false, 0);

                if (lookingLeft)
                {
                    if (bonnieLocation > 6)
                    {
                        NF_PlayRawSound(8, 100, 64, false, 0);
                    }
                    else
                    {
                        ldoor = !ldoor;
                    }
                }
                else
                {
                    if (chicaLocation > 6)
                    {
                        NF_PlayRawSound(8, 100, 64, false, 0);
                    }
                    else
                    {
                        rdoor = !rdoor;
                    }
                }
            }

            if (keys_down & KEY_X)
            {
                showHints = false;
            }

            if (keys_down & KEY_B && !powerOut)
            {
                if (lookingLeft)
                {
                    ldoorlight = !ldoorlight;
                }
                else
                {
                    rdoorlight = !rdoorlight;
                }
            }

            if (ldoorlight != prev_ldoorlight || rdoorlight != prev_rdoorlight)
            {
                const char* bgname;
                if (ldoorlight)
                {
                    if (bonnieLocation > 5)
                    {
                        bgname = "office_bonnie";
                        NF_PlayRawSound(7, 100, 64, false, 0);
                    }
                    else
                    {
                        bgname = "office_left";
                    }
                }
                else if (rdoorlight)
                {
                    if (chicaLocation > 5)
                    {
                        bgname = "office_chica";
                        NF_PlayRawSound(7, 100, 64, false, 0);
                    }
                    else
                    {
                        bgname = "office_right";
                    }
                }
                else
                {
                    bgname = "office_off";
                }

                NF_CreateTiledBg(0, 3, bgname);

                prev_ldoorlight = ldoorlight;
                prev_rdoorlight = rdoorlight;
            }
        }

        if (ldoor != prev_ldoor || rdoor != prev_rdoor)
        {
            const char* doorname;
            if (ldoor & rdoor)
            {
                doorname = "doors_LR";
            }
            else if (ldoor)
            {
                doorname = "doors_L";
            }
            else if (rdoor)
            {
                doorname = "doors_R";
            }
            else
            {
                doorname = "doors_off";
            }

            NF_CreateTiledBg(0, 1, doorname);

            prev_ldoor = ldoor;
            prev_rdoor = rdoor;
        }

        checkAnimatronics();

        gfTimer = time(NULL);
        if (difftime(gfTimer, gflast) >= 1)
        {
            if ((rand() % 32768) == 0 && !goldenFreddy) // yes it is not actually 100000
            {
                goldenFreddyCanSpawn = true;
            }
            gflast = gfTimer;
        }

        if (keys_down & KEY_UP && !powerOut)
        {
            NF_PlayRawSound(3, 127, 64, false, 0);

            ldoorlight = false;
            rdoorlight = false;
            usingCams = !usingCams;

            if (usingCams)
            {
                NF_HideBg(0, 1);
                NF_HideBg(0, 2);
                NF_ShowBg(1, 3);

                updateCams();

                goldenFreddyInOffice = false;
                goldenFreddyKillTimer = 0;
            }
            else
            {
                NF_ShowBg(0, 1);
                NF_ShowBg(0, 2);
                NF_HideBg(1, 3);

                if (goldenFreddy)
                {
                    goldenFreddyInOffice = true;
                    goldenFreddy = false;
                    goldenFreddyCanSpawn = false;
                }

                NF_CreateTiledBg(0, 3, "office_off");

                if (goldenFreddyInOffice)
                {
                    NF_CreateTiledBg(0, 2, "goldenFreddy");
                }
                else
                {
                    NF_CreateTiledBg(0, 2, "goldenFreddyOff");
                }

                if (bonnieLocation > 6 || chicaLocation > 6) gotJumped = true;
            }
        }

        if (goldenFreddyInOffice && !usingCams)
        {
            goldenFreddyKillTimer += 1;
        }
        if (goldenFreddyKillTimer > 300)
        {
            break;
        }
        
        if (keys_held & KEY_TOUCH)
        {
            touchRead(&touch_position);
        }

        if (keys_down & KEY_TOUCH)
        {
            if (usingCams)
            {
                if (touch_position.px > 86 && touch_position.py > 18 && touch_position.px < 103 && touch_position.py < 27)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam1a";
                }
                if (touch_position.px > 78 && touch_position.py > 39 && touch_position.px < 94 && touch_position.py < 48)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam1b";
                }
                if (touch_position.px > 58 && touch_position.py > 78 && touch_position.px < 74 && touch_position.py < 88)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam1c";
                }
                if (touch_position.px > 91 && touch_position.py > 138 && touch_position.px < 107 && touch_position.py < 147)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam2a";
                }
                if (touch_position.px > 91 && touch_position.py > 153 && touch_position.px < 107 && touch_position.py < 161)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam2b";
                }
                if (touch_position.px > 55 && touch_position.py > 123 && touch_position.px < 72 && touch_position.py < 132)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam3";
                }
                if (touch_position.px > 140 && touch_position.py > 138 && touch_position.px < 156 && touch_position.py < 147)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam4a";
                }
                if (touch_position.px > 140 && touch_position.py > 153 && touch_position.px < 156 && touch_position.py < 161)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam4b";
                }
                if (touch_position.px > 32 && touch_position.py > 58 && touch_position.px < 48 && touch_position.py < 67)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam5";
                }
                if (touch_position.px > 190 && touch_position.py > 118 && touch_position.px < 206 && touch_position.py < 127)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam6";
                }
                if (touch_position.px > 185 && touch_position.py > 53 && touch_position.px < 201 && touch_position.py < 62)
                {
                    NF_PlayRawSound(4, 127, 64, false, 0);
                    camName = "cam7";
                }

                updateCams();
                if (strcmp(camName, "cam2b_g") == 0)
                {
                    NF_PlayRawSound(13, 100, 64, false, 0);
                }
            }
        }
        
        if (!powerOut)
        {
            freddyTime();
            bonnieTime();
            chicaTime();
            foxyTime();
        }

        if (gotJumped)
            break;

        if (powerOutPhase == 3)
        {
            gotJumped = true;
            break;
        }

        daTimeShit();
        if (timeAM > 5)
            break;

        if (freddyAILevel > 20) freddyAILevel = 20;
        if (bonnieAILevel > 20) bonnieAILevel = 20;
        if (chicaAILevel > 20) chicaAILevel = 20;
        if (foxyAILevel > 20) foxyAILevel = 20;

        NF_SpriteRotScale(0, 0, 0, 96, 96);
        NF_SpriteFrame(0, 0, timeAM);

        usage = 1;

        if(ldoorlight || rdoorlight)
        {
            usage += 1;
        }
        if(ldoor)
        {
            usage += 1;
        }
        if(rdoor)
        {
            usage += 1;
        }
        if(usingCams)
        {
            usage += 1;
        }

        if (!powerOut)
        {
            power -= 0.0021 * usage;
            if (power <= 0)
            {
                powerOut = true;
                ohNoPowerOut();
            }
        }

        if (powerOut) powerOutEvents();

        if (!usingCams)
        {
            NF_ScrollBg(0, 1, (officeX * 2), 160);
            NF_ScrollBg(0, 2, (officeX * 2), 160);
            NF_ScrollBg(0, 3, (officeX * 2), 160);
        }
        else
        {
            NF_ScrollBg(0, 3, (camX * 2), 160);
        }
        
        char mytext[128];
        snprintf(mytext, sizeof(mytext), "Power Left: %d%%     \n Usage: %d          ", abs(ceil(power - 1)), usage);
        if (powerOut) NF_WriteText(0, 0, 1, 1, "                       \n                    "); else NF_WriteText(0, 0, 1, 1, mytext);

        if (powerOut || !showHints)
        {
            NF_WriteText(1, 0, 1, 1, "         \n                              \n                   \n                 \n                 \n                  ");
        }
        else if (!usingCams) // yes the spaces are required because the ds is weird
        {
            NF_WriteText(1, 0, 1, 1, "Controls:\n L and R: Look Around         \n A: Close Door     \n B: Check Lights \n Up: Open Camera \n X: Hide Controls ");
        }
        else
        {
            NF_WriteText(1, 0, 1, 1, "Controls:\n Touch Screen: Switch Cameras \n Up: Close Camera  \n                 \n                 \n                  ");
        }
        
        NF_UpdateTextLayers();

        swiWaitForVBlank();
        
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);

        //break; //used to test shit
    }
    
    NF_DeleteTiledBg(0, 1);
    NF_DeleteTiledBg(0, 2);
    NF_DeleteTiledBg(0, 3);
    NF_DeleteTiledBg(1, 3);

    NF_UnloadTiledBg("office_off");
    NF_UnloadTiledBg("office_left");
    NF_UnloadTiledBg("office_right");
    NF_UnloadTiledBg("office_bonnie");
    NF_UnloadTiledBg("office_chica");
    NF_UnloadTiledBg("office_power");
    NF_UnloadTiledBg("office_powerfred");

    NF_UnloadTiledBg("doors_off");
    NF_UnloadTiledBg("doors_L");
    NF_UnloadTiledBg("doors_R");
    NF_UnloadTiledBg("doors_LR");
    
    NF_UnloadTiledBg("cam1a");
    NF_UnloadTiledBg("cam1a_fbc");
    NF_UnloadTiledBg("cam1a_fb");
    NF_UnloadTiledBg("cam1a_fc");
    NF_UnloadTiledBg("cam1a_f");

    NF_UnloadTiledBg("cam1b");
    NF_UnloadTiledBg("cam1b_b");
    NF_UnloadTiledBg("cam1b_c");
    NF_UnloadTiledBg("cam1b_f");

    NF_UnloadTiledBg("cam1c");
    NF_UnloadTiledBg("cam1c_1");
    NF_UnloadTiledBg("cam1c_2");
    NF_UnloadTiledBg("cam1c_3");

    NF_UnloadTiledBg("cam2a");
    NF_UnloadTiledBg("cam2a_b");
    
    NF_UnloadTiledBg("cam2b");
    NF_UnloadTiledBg("cam2b_b");
    NF_UnloadTiledBg("cam2b_g");

    NF_UnloadTiledBg("cam3");
    NF_UnloadTiledBg("cam3_b");

    NF_UnloadTiledBg("cam4a");
    NF_UnloadTiledBg("cam4a_c");
    NF_UnloadTiledBg("cam4a_f");
    
    NF_UnloadTiledBg("cam4b");
    NF_UnloadTiledBg("cam4b_c");
    NF_UnloadTiledBg("cam4b_f");
    
    NF_UnloadTiledBg("cam5");
    NF_UnloadTiledBg("cam5_b");
    
    NF_UnloadTiledBg("cam6");
    
    NF_UnloadTiledBg("cam7");
    NF_UnloadTiledBg("cam7_c");
    NF_UnloadTiledBg("cam7_f");

    NF_UnloadTiledBg("minimap");

    NF_ResetTiledBgBuffers();
    
    NF_UnloadSpriteGfx(0);
    NF_UnloadSpritePal(0);
    NF_FreeSpriteGfx(0, 0);
    NF_DeleteSprite(0, 0);
    
    NF_ResetSpriteBuffers();
    
    //NF_UnloadTextFont("top");
    //NF_UnloadTextFont("bottom");
    
    NF_DeleteTextLayer(0, 0);
    NF_DeleteTextLayer(1, 0);

    if (!powerOut) soundKill(0);
    NF_ResetRawSoundBuffers();
    
    // resetting all vars
    officeX = 50;
    camX = 25;
    scrollSpeed = 3;
    power = 100;
    usage = 1;
    timeAM = 0;
    foxyRunning = false;
    usingCams = false;
    camName = "cam1a_fbc";
    camGoLeft = false;
    lookingLeft = true;
    ldoor = false;
    ldoorlight = false;
    rdoor = false;
    rdoorlight = false;
    prev_ldoor = false;
    prev_ldoorlight = false;
    prev_rdoor = false;
    prev_rdoorlight = false;
    freddyLocation = 0;
    bonnieLocation = 0;
    chicaLocation = 0;
    foxyPhase = 0;
    powerOut = false;
    powerOutTimer = 0;
    powerOutEventFails = 0;
    powerOutPhase = 0;

    if (gotJumped) gameOver(); else if (goldenFreddyInOffice) goldenJumpscare(); else sixAMScreen();

    return 0;
}

int noScreenRefresh()
{
    return 0;
}
