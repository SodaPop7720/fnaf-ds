#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "mainmenu.h"
#include "newspaper.h"

int menuCreate()
{
    // load the shit
    
    NF_LoadTiledBg("bg/titleFred0", "titleFred", 256, 256);
    NF_LoadTiledBg("bg/logo", "logo", 256, 256);
    NF_LoadTiledBg("bg/static0", "static0", 256, 256);
    NF_LoadTiledBg("bg/static1", "static1", 256, 256);
    NF_LoadTiledBg("bg/static2", "static2", 256, 256);
    NF_LoadTiledBg("bg/static3", "static3", 256, 256);

    NF_CreateTiledBg(0, 3, "titleFred");
    NF_CreateTiledBg(0, 0, "logo");
    
    NF_CreateTiledBg(0, 2, "static0");
    NF_CreateTiledBg(1, 2, "static0");
    
    NF_LoadSpriteGfx("sprite/newGame", 0, 64, 32);
    NF_LoadSpritePal("sprite/newGame", 0);
    NF_LoadSpriteGfx("sprite/continue", 1, 64, 32);
    NF_LoadSpritePal("sprite/continue", 1);
    NF_LoadSpriteGfx("sprite/night6", 2, 64, 32);
    NF_LoadSpritePal("sprite/night6", 2);
    NF_LoadSpriteGfx("sprite/customNight", 3, 64, 32);
    NF_LoadSpritePal("sprite/customNight", 3);
    NF_LoadSpriteGfx("sprite/cursor", 4, 32, 32);
    NF_LoadSpritePal("sprite/cursor", 4);

    NF_VramSpriteGfx(1, 0, 0, false);
    NF_VramSpritePal(1, 0, 0);
    NF_VramSpriteGfx(1, 1, 1, false);
    NF_VramSpritePal(1, 1, 1);
    NF_VramSpriteGfx(1, 2, 2, false);
    NF_VramSpritePal(1, 2, 2);
    NF_VramSpriteGfx(1, 3, 3, false);
    NF_VramSpritePal(1, 3, 3);
    NF_VramSpriteGfx(1, 4, 4, false);
    NF_VramSpritePal(1, 4, 4);

    NF_CreateSprite(1, 0, 0, 0, 96, 32);
    NF_CreateSprite(1, 1, 1, 1, 96, 64);
    NF_CreateSprite(1, 2, 2, 2, 96, 96);
    NF_CreateSprite(1, 3, 3, 3, 96, 128);
    NF_CreateSprite(1, 4, 4, 4, 56, 32);

    NF_EnableSpriteRotScale(1, 4, 4, false);

    // audio
    
    NF_LoadRawSound("sfx/darknessmusic", 0, 8000, 0);
    NF_PlayRawSound(0, 127, 64, true, 0);

    NF_LoadRawSound("sfx/static", 1, 11025, 0);
    NF_PlayRawSound(1, 64, 64, false, 0);
    
    NF_LoadRawSound("sfx/blip", 2, 11025, 0);

    // alpha

    REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG2 | BLEND_DST_BG3;
    REG_BLDALPHA = 0x05 | (0x0F << 8);

    return 0;
}

// variables
touchPosition touch_pos = { 0 };
int staticTimer = 0;
int daMenuSelection = 1;
int brightness = 0;
bool doBrightnessThingy = false;

int menuUpdate()
{
    while (1)
    {
        scanKeys();
        uint16_t keys_down = keysDown();
        uint16_t keys_held = keysHeld();
        
        if (keys_held & KEY_TOUCH)
        {
            touchRead(&touch_pos);

            switch (touch_pos.py / 32)
            {
                case 1:
                    NF_MoveSprite(1, 4, 56, 32);
                    if (daMenuSelection != 1)
                        NF_PlayRawSound(2, 127, 64, false, 0);
                    daMenuSelection = 1;
                    break;
                case 2:
                    NF_MoveSprite(1, 4, 56, 64);
                    if (daMenuSelection != 2)
                        NF_PlayRawSound(2, 127, 64, false, 0);
                    daMenuSelection = 2;
                    break;
                case 3:
                    NF_MoveSprite(1, 4, 56, 96);
                    if (daMenuSelection != 3)
                        NF_PlayRawSound(2, 127, 64, false, 0);
                    daMenuSelection = 3;
                    break;
                case 4:
                    NF_MoveSprite(1, 4, 56, 128);
                    if (daMenuSelection != 4)
                        NF_PlayRawSound(2, 127, 64, false, 0);
                    daMenuSelection = 4;
                    break;
            }
        }

        NF_SpriteRotScale(1, 4, 0, 128, 128);

        if (keys_down & KEY_START)
        {
            doBrightnessThingy = true;
        }
        if (keys_down & KEY_A)
        {
            doBrightnessThingy = true;
        }

        if (keys_down & KEY_UP)
        {
            daMenuSelection -= 1;
            if (daMenuSelection < 1)
                daMenuSelection = 4;
        }
        if (keys_down & KEY_DOWN)
        {
            daMenuSelection += 1;
            if (daMenuSelection > 4)
                daMenuSelection = 1;
        }
        
        if (doBrightnessThingy)
        {
            brightness -= 1;
            setBrightness(3, brightness);
        }

        staticTimer++;
        const char *curStatic = "static0";
        switch (staticTimer & 3)
        {
            case 0: curStatic = "static0"; break;
            case 1: curStatic = "static1"; break;
            case 2: curStatic = "static2"; break;
            case 3: curStatic = "static3"; break;
        }
        
        NF_SpriteOamSet(0);
        NF_SpriteOamSet(1);

        if (brightness < -16)
        {
            doBrightnessThingy = false;
            break;
        }

        swiWaitForVBlank();

        NF_CreateTiledBg(0, 2, curStatic);
        NF_CreateTiledBg(1, 2, curStatic);

        oamUpdate(&oamMain);
        oamUpdate(&oamSub);
    }

    NF_DeleteTiledBg(0, 0);
    NF_DeleteTiledBg(0, 2);
    NF_DeleteTiledBg(0, 3);
    NF_DeleteTiledBg(1, 2);
    NF_UnloadTiledBg("titleFred");
    NF_UnloadTiledBg("logo");
    NF_UnloadTiledBg("static0");
    NF_UnloadTiledBg("static1");
    NF_UnloadTiledBg("static2");
    NF_UnloadTiledBg("static3");
    NF_ResetTiledBgBuffers();

    NF_UnloadSpriteGfx(0);
    NF_UnloadSpriteGfx(1);
    NF_UnloadSpriteGfx(2);
    NF_UnloadSpriteGfx(3);
    NF_UnloadSpriteGfx(4);
    NF_UnloadSpritePal(0);
    NF_UnloadSpritePal(1);
    NF_UnloadSpritePal(2);
    NF_UnloadSpritePal(3);
    NF_UnloadSpritePal(4);

    NF_FreeSpriteGfx(1, 0);
    NF_FreeSpriteGfx(1, 1);
    NF_FreeSpriteGfx(1, 2);
    NF_FreeSpriteGfx(1, 3);
    NF_FreeSpriteGfx(1, 4);

    NF_DeleteSprite(1, 0);
    NF_DeleteSprite(1, 1);
    NF_DeleteSprite(1, 2);
    NF_DeleteSprite(1, 3);
    NF_DeleteSprite(1, 4);

    NF_ResetSpriteBuffers();

    newspaperStuff();

    return 0;
}