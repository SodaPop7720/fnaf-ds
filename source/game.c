#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "game.h"
#include "daTime.h"

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

    NF_LoadTiledBg("bg/office", "office_off", 512, 512);
    NF_LoadTiledBg("bg/officeLeftLight", "office_left", 512, 512);
    NF_LoadTiledBg("bg/officeRightLight", "office_right", 512, 512);
    NF_CreateTiledBg(0, 3, "office_off");
    NF_ScrollBg(0, 3, 100, 160);

    NF_LoadTiledBg("bg/nothing", "doors_off", 512, 512);
    NF_LoadTiledBg("bg/LDoor", "doors_L", 512, 512);
    NF_LoadTiledBg("bg/RDoor", "doors_R", 512, 512);
    NF_LoadTiledBg("bg/LRDoor", "doors_LR", 512, 512);
    NF_CreateTiledBg(0, 1, "doors_off");
    
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

    NF_LoadTiledBg("bg/minimap", "minimap", 256, 256);
    NF_CreateTiledBg(1, 3, "minimap");
    NF_HideBg(1, 3);
    
    NF_LoadSpriteGfx("sprite/timeAMspr", 0, 64, 32);
    NF_LoadSpritePal("sprite/timeAMspr", 0);

    NF_VramSpriteGfx(0, 0, 0, true);
    NF_VramSpritePal(0, 0, 0);

    NF_CreateSprite(0, 0, 0, 0, 192, 0);
    NF_SpriteFrame(0, 0, 0);
    
    NF_EnableSpriteRotScale(0, 0, 0, false);
    
    NF_LoadTextFont("fnt/default", "normal", 256, 256, 0);
    
    NF_CreateTextLayer(0, 0, 0, "normal");
    NF_CreateTextLayer(1, 0, 0, "normal");

    return 0;
}

int onPostCreate()
{
    NF_LoadRawSound("sfx/fan", 0, 11025, 0);
    NF_PlayRawSound(0, 100, 64, true, 0);
    
    NF_LoadRawSound("sfx/door", 2, 11025, 0);
    NF_LoadRawSound("sfx/flip", 3, 11025, 0);
    NF_LoadRawSound("sfx/blip", 4, 11025, 0);

    return 0;
}

int officeX = 50;
float camX = 25;
int scrollSpeed = 3;

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

touchPosition touch_position = { 0 };

int onUpdate()
{
    while (1)
    {
        scanKeys();
        uint16_t keys_down = keysDown();
        uint16_t keys_held = keysHeld();

        char mytext[64];
        snprintf(mytext, sizeof(mytext), "\n\n\n\n\n\n X: %u     \n Y: %u     ", touch_position.px, touch_position.py);
        // NF_WriteText(0, 0, 1, 1, mytext); // dont forget to comment this out later

        if (!usingCams) // yes the spaces are required because the ds is weird
            NF_WriteText(1, 0, 1, 1, "Controls:\n L and R: Look Around         \n A: Close Door     \n B: Check Lights \n Up: Open Camera");
        else
            NF_WriteText(1, 0, 1, 1, "Controls:\n Touch Screen: Switch Cameras \n Up: Close Camera  \n                 \n                ");
        
        NF_UpdateTextLayers();

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

            if (keys_down & KEY_A)
            {
                NF_PlayRawSound(2, 127, 64, false, 0);

                if (lookingLeft)
                {
                    ldoor = !ldoor;
                }
                else
                {
                    rdoor = !rdoor;
                }
            }

            if (keys_down & KEY_B)
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
                    bgname = "office_left";
                }
                else if (rdoorlight)
                {
                    bgname = "office_right";
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

        if (keys_down & KEY_UP)
        {
            NF_PlayRawSound(3, 127, 64, false, 0);

            ldoorlight = false;
            rdoorlight = false;
            usingCams = !usingCams;

            if (usingCams)
            {
                NF_HideBg(0, 1);
                NF_ShowBg(1, 3);

                NF_CreateTiledBg(0, 3, camName);
            }
            else
            {
                NF_ShowBg(0, 1);
                NF_HideBg(1, 3);

                NF_CreateTiledBg(0, 3, "office_off");
            }
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
                    camName = "cam1a_fbc";
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

                NF_CreateTiledBg(0, 3, camName);
            }
        }

        if (!usingCams)
        {
            NF_ScrollBg(0, 1, (officeX * 2), 160);
            NF_ScrollBg(0, 3, (officeX * 2), 160);
        }
        else
        {
            NF_ScrollBg(0, 3, (camX * 2), 160);
        }
        
        daTimeShit();
        if (timeAM > 5)
            break;

        NF_SpriteRotScale(0, 0, 0, 96, 96);
        NF_SpriteFrame(0, 0, timeAM);

        swiWaitForVBlank();
        
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);
        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }
    
    return 0;
}

int noScreenRefresh()
{
    while (1)
    {
        
    }
}
