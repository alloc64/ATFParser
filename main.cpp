#include <cstdlib>
#include <iostream>
#include <windows.h>

struct FileStructATF {
    int iExcercise;
    int iStrikesPerSec;
    float fAccuracy;
    float f;
    int i;
};


int main(int argc, char *argv[]) {
    SetConsoleTitle("ATF File generator");
    if(argc < 2)
        return 0;

    FILE *ATFfile = fopen(argv[1], "rb");

    if (!ATFfile) {
        printf("error: file not found!\n");
        return 2;
    }

    char ATFHeader[2187];
    fread(ATFHeader, sizeof(char), 2187, ATFfile);
    fclose(ATFfile);

    FILE *ATFNewFile = fopen("atf_new.atf", "wb");
    if (!ATFNewFile) {
        printf("error: cannot crate file!\n");
        return 3;
    }

    FileStructATF *AtfStruct = new FileStructATF[130];

    for (int o = 0; o < 130; o++) {
        for (int i = 0; i < 12; i++) {
            AtfStruct[i].iExcercise = 1;
            AtfStruct[i].iStrikesPerSec = rand() % 270;
            if (AtfStruct[i].iStrikesPerSec < 100) AtfStruct[i].iStrikesPerSec += 100;
            AtfStruct[i].fAccuracy = 100.000;

        }
    }
    int iNumLessons = 0;

    printf("ATF File generator\n\n");
    printf("Insert lesson count: ");
    scanf("%d", &iNumLessons);

    fwrite(&ATFHeader, sizeof(char), sizeof(ATFHeader), ATFNewFile);
    for (int o = 0; o < iNumLessons * 2; o++) {
        for (int i = 0; i < 12; i++) {
            fwrite(&AtfStruct[i], sizeof(FileStructATF), 1, ATFNewFile);
        }
    }
    fclose(ATFNewFile);

    printf("atf_new.atf was created!\nDone!\n");

    system("PAUSE");
    return EXIT_SUCCESS;
}
