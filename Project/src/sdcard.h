#pragma once
#include <Arduino.h>
#include <FS.h> //Работа с файловой системой

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void createDir(fs::FS &fs, const char *path);
void removeDir(fs::FS &fs, const char *path);
void readFile(fs::FS &fs, const char *path);
void writeFile(fs::FS &fs, const char *path, const char *message);
void sdSaveConf(fs::FS &fs, const char *path, const char *littlefspath);
bool sdLoadConf(fs::FS &fs, const char *path, const char *littlefspath);
void appendFile(fs::FS &fs, const char *path, const char *message);
void renameFile(fs::FS &fs, const char *path1, const char *path2);
void deleteFile(fs::FS &fs, const char *path);
void testFileIO(fs::FS &fs, const char *path);
