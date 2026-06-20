#include <stdio.h>

#include <nds.h>
#include <filesystem.h>
#include <fat.h>
#include <unistd.h>

typedef struct SaveData {int curNight;} SaveData;
SaveData daSaveData;

void saveGame() 
{
    FILE *file = fopen("fat:/saves/fnaf_ds.sav", "wb");
    if (file) 
    {
        fwrite(&daSaveData, sizeof(struct SaveData), 1, file);
        fclose(file);
    }
}

void loadGame() 
{
    FILE *file = fopen("fat:/saves/fnaf_ds.sav", "rb");
    if (file) 
    {
        fread(&daSaveData, sizeof(struct SaveData), 1, file);
        fclose(file);
    }
}

void createSave()
{
    FILE *file = fopen("fat:/saves/fnaf_ds.sav", "rb");
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