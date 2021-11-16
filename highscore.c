#include "definitions.h"

int getHighscore() {
  FILE * fPtr;
  int highscore;

  if ((fPtr = fopen(HIGHSCORE_FILENAME, "rb")) == NULL) {
    return 0;
  }

  fread(&highscore, sizeof(int), 1, fPtr);
  fclose(fPtr);
  return highscore;
}

BOOL writeHighscore(int highscore) {
  FILE * fPtr;

  if ((fPtr = fopen(HIGHSCORE_FILENAME, "wb")) == NULL) {
    return FALSE;
  }

  fwrite(&highscore, sizeof(int), 1, fPtr);
  fclose(fPtr);
  return TRUE;
}

