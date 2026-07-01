#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#include <nds.h>
#include <filesystem.h>

#include <nf_lib.h>

#include "custom.h"
#include "nightnumber.h"

int custombrightness = -16;

int freddyCustomAI = 1;
int bonnieCustomAI = 3;
int chicaCustomAI = 3;
int foxyCustomAI = 1;

int customCreate()
{
    NF_LoadTiledBg("bg/customNightBg", "cn", 256, 256);
    
    NF_LoadTextFont("fnt/default", "top", 256, 256, 0);
    NF_LoadTextFont("fnt/default", "bottom", 256, 256, 0);

    NF_CreateTiledBg(0, 1, "cn");
    
    NF_CreateTextLayer(0, 0, 0, "top");
    NF_CreateTextLayer(1, 0, 0, "bottom");
    
    int custombrightness = -16;
    while (custombrightness < 0)
    {
        custombrightness += 1;
        setBrightness(3, custombrightness);
        
        char mytext[128];
        snprintf(mytext, sizeof(mytext), ">>Freddy: < %d >   \n   Bonnie: < %d >   \n   Chica: < %d >    \n   Foxy: < %d >     ", 
            freddyCustomAI, bonnieCustomAI, chicaCustomAI, foxyCustomAI);
        NF_WriteText(1, 0, 1, 1, mytext);
        
        NF_UpdateTextLayers();
        swiWaitForVBlank();
    }

    return 0;
}

int selectedCharacter = 0;

int customUpdate()
{
    while (1)
    {
        scanKeys();
        uint16_t keys_down = keysDown();

        if (keys_down & KEY_UP)
        {
            selectedCharacter -= 1;
            if (selectedCharacter < 0) selectedCharacter = 0;
        }
        if (keys_down & KEY_DOWN)
        {
            selectedCharacter += 1;
            if (selectedCharacter > 3) selectedCharacter = 3;
        }
        if (keys_down & KEY_LEFT)
        {
            switch (selectedCharacter)
            {
                case 0:
                    freddyCustomAI -= 1;
                    if (freddyCustomAI < 0) freddyCustomAI = 0;
                    break;
                case 1:
                    bonnieCustomAI -= 1;
                    if (bonnieCustomAI < 0) bonnieCustomAI = 0;
                    break;
                case 2:
                    chicaCustomAI -= 1;
                    if (chicaCustomAI < 0) chicaCustomAI = 0;
                    break;
                case 3:
                    foxyCustomAI -= 1;
                    if (foxyCustomAI < 0) foxyCustomAI = 0;
                    break;
            }
        }
        if (keys_down & KEY_RIGHT)
        {
            switch (selectedCharacter)
            {
                case 0:
                    freddyCustomAI += 1;
                    if (freddyCustomAI > 20) freddyCustomAI = 20;
                    break;
                case 1:
                    bonnieCustomAI += 1;
                    if (bonnieCustomAI > 20) bonnieCustomAI = 20;
                    break;
                case 2:
                    chicaCustomAI += 1;
                    if (chicaCustomAI > 20) chicaCustomAI = 20;
                    break;
                case 3:
                    foxyCustomAI += 1;
                    if (foxyCustomAI > 20) foxyCustomAI = 20;
                    break;
            }
        }
        if (keys_down & KEY_START)
        {
            break;
        }
        if (keys_down & KEY_A)
        {
            break;
        }

        char mytext[128];

        switch (selectedCharacter)
        {
            case 0:
                snprintf(mytext, sizeof(mytext), ">>Freddy: < %d >   \n   Bonnie: < %d >   \n   Chica: < %d >    \n   Foxy: < %d >     ", 
                    freddyCustomAI, bonnieCustomAI, chicaCustomAI, foxyCustomAI);
                break;
            case 1:
                snprintf(mytext, sizeof(mytext), "  Freddy: < %d >   \n >>Bonnie: < %d >   \n   Chica: < %d >    \n   Foxy: < %d >     ", 
                    freddyCustomAI, bonnieCustomAI, chicaCustomAI, foxyCustomAI);
                break;
            case 2:
                snprintf(mytext, sizeof(mytext), "  Freddy: < %d >   \n   Bonnie: < %d >   \n >>Chica: < %d >    \n   Foxy: < %d >     ", 
                    freddyCustomAI, bonnieCustomAI, chicaCustomAI, foxyCustomAI);
                break;
            case 3:
                snprintf(mytext, sizeof(mytext), "  Freddy: < %d >   \n   Bonnie: < %d >   \n   Chica: < %d >    \n >>Foxy: < %d >     ", 
                    freddyCustomAI, bonnieCustomAI, chicaCustomAI, foxyCustomAI);
                break;
        }

        NF_WriteText(1, 0, 1, 1, mytext);

        NF_UpdateTextLayers();
        swiWaitForVBlank();
    }

    NF_DeleteTiledBg(0, 1);
    NF_UnloadTiledBg("cn");
    NF_ResetTiledBgBuffers();
    
    NF_DeleteTextLayer(0, 0);
    NF_DeleteTextLayer(1, 0);
    
    soundKill(0);
    NF_ResetRawSoundBuffers();

    soundDisable();
    soundEnable();
    
    showNightNumber(); 

    return 0;
}
