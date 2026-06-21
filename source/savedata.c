#include <stdio.h>

#include <nds.h>
#include <filesystem.h>
#include <fat.h>
#include <unistd.h>

typedef struct SaveData {int curNight;} SaveData;
SaveData daSaveData;

void saveGame() 
{
    char *cwd = fatGetDefaultCwd();
    char savePath[512];
    snprintf(savePath, sizeof(savePath), "%s/saves/fnaf_ds.sav", cwd);
    free(cwd);

    FILE *file = fopen(savePath, "wb");
    if (file) 
    {
        fwrite(&daSaveData, sizeof(struct SaveData), 1, file);
        fclose(file);
    }
}

void loadGame() 
{
    char *cwd = fatGetDefaultCwd();
    char savePath[512];
    snprintf(savePath, sizeof(savePath), "%s/saves/fnaf_ds.sav", cwd);
    free(cwd);

    FILE *file = fopen(savePath, "rb");
    if (file) 
    {
        fread(&daSaveData, sizeof(struct SaveData), 1, file);
        fclose(file);
    }
}

void createSave()
{
    char *cwd = fatGetDefaultCwd();
    char savePath[512];
    snprintf(savePath, sizeof(savePath), "%s/saves/fnaf_ds.sav", cwd);
    free(cwd);

    FILE *file = fopen(savePath, "rb");
    if (file != NULL) 
    {
        fclose(file);
    }
    else
    {
        daSaveData.curNight = 1;
        saveGame();
    }
}