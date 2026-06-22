#ifndef SAVEDATA_H
#define SAVEDATA_H

typedef struct SaveData {int curNight;} SaveData;
extern SaveData daSaveData;

void saveGame();
void loadGame();
void createSave();

#endif