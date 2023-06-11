//Path In Machine: /Users/rushikeshgadewar/Library/Developer/Xcode/DerivedData/C_Programming-fyimmrpkllxgvuerpjscpdlpwsij/Build/Products/Debug
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>

char fname[100],fname2[100],newcontent[2000];
int shift = 3;
char ch;
int count = 0;
long fileSize;

void fileoperations(void);
void check(void);
void check2(void);
void createfile(void);
void searchfile(void);
void append(void);
void delete(void);
void overwrites(void);
void reads(void);
void renames(void);
void encryptdata(char array[],int shift);
void decryptdata(char array[],int shift);

int main(void)
{
    
            int choice1;
            printf("Welcome To File Encrypter!\n");
            printf("1. Create A New File.\n2. Search A Existing File.\nChoice:");
            scanf("%d",&choice1);
            
            switch(choice1)
            {
                case 1: createfile();
                case 2: searchfile();
                default:printf("Enter A Valid Choice!\n");
            }
    
        return 0;
}

void check2(void){
    FILE *file = fopen(fname2, "r");
        if (file != NULL) {
            printf("File Already Exists.\n");
            fclose(file);
            exit(0);
        }
    
}
void overwrites(void)
{
    FILE *file = fopen(fname, "w");
        if (file != NULL) {
            printf("Enter a string: ");
            scanf(" %[^\n]", newcontent);
            fprintf(file, "%s", newcontent);
            fclose(file);
        }
    fileoperations();
}
void append(void)
{
    FILE *file = fopen(fname, "a");
        if (file != NULL) {
            printf("Enter a string: ");
            scanf(" %[^\n]", newcontent);
            fprintf(file, "%s", newcontent);
            fclose(file);
        }
    fileoperations();
}

void reads(void) {
    FILE *file = fopen(fname, "r");
    if (file != NULL) {
        char data[100];
        fscanf(file, "%[^\n]", data);
        printf("Data read from file: %s\n", data);
        fclose(file);
    }
    fileoperations();
    
}

void renames(void)
{
        printf("Enter The New File Name:\n");
        scanf("%s",fname2);
        strcat(fname2, ".txt");
        check2();
        int result = rename(fname, fname2);
        if (result == 0) {
            printf("File renamed successfully.\n");
        } else {
            printf("Error renaming file!\n");
        }
    strcpy(fname, fname2);
    fileoperations();
}

void delete(void)
{
        int result;
        result = remove(fname);
        if (result == 0) {
            printf("File Deleted Successfully.\n");
        } else {
            printf("Error Deleting File!\n");
        }
    exit(0);

}

void fileoperations(void)
{
        int choice2;
        printf("Enter The Operation You Want To Perform:\n");
        printf("1.Overwrite File Data.\n2.Append Data In The File.\n3.Read File Data.\n4.Rename File.\n5.Delete File.\n6.Encrypt Data.\n7.Decrypt Data.\nChoice:");
        scanf("%d",&choice2);
        switch(choice2)
        {
            case 1: overwrites();
            case 2: append();
            case 3: reads();
            case 4: renames();
            case 5: delete();
            case 6: encryptdata(newcontent,shift);
            case 7: decryptdata(newcontent,shift);
            default:printf("Enter A Valid Choice!\n");
            
        }
    
}

void check(void)
{
    FILE *file = fopen(fname, "r");
        if (file != NULL) {
            printf("File Already Exists.\n");
            fclose(file);
            exit(0);
        }
}

void createfile(void)
{
    printf("Enter The File Name:\n");
    scanf("%s",fname);
    strcat(fname, ".txt");
    check();
    FILE *file = fopen(fname, "w");
        if (file != NULL) {
            fclose(file);
            printf("File Created Successfully!!\n");
        }
    fileoperations();
}

void searchfile(void)
{
    printf("Enter The File Name:\n");
    scanf("%s",fname);
    strcat(fname, ".txt");
    FILE *file = fopen(fname, "r");
    if (file != NULL) {
        printf("File Exists.\n");
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);
        rewind(file);
        fread(newcontent, sizeof(char), fileSize, file);
        newcontent[fileSize] = '\0';
        fileoperations();
        fclose(file);
        
    }else {
        printf("File does not exist.\n");
        main();
        
    }
}


void encryptdata(char* plaintext, int shift)
{
    char* p = plaintext;
    while (*p != '\0') {
        if (*p >= 'a' && *p <= 'z') {
            *p = ((*p - 'a') + shift) % 26 + 'a';
        } else if (*p >= 'A' && *p <= 'Z') {
            *p = ((*p - 'A') + shift) % 26 + 'A';
        }
        p++;
    }
    printf("Encrypted message: %s\n", newcontent);
    FILE *file = fopen(fname, "w");
        if (file != NULL) {
            fprintf(file, "%s", newcontent);
            fclose(file);
        }
    fileoperations();
}

void decryptdata(char* ciphertext, int shift)
{
    char* c = ciphertext;
    while (*c != '\0') {
        if (*c >= 'a' && *c <= 'z') {
            *c = ((*c - 'a') - shift + 26) % 26 + 'a';
        } else if (*c >= 'A' && *c <= 'Z') {
            *c = ((*c - 'A') - shift + 26) % 26 + 'A';
        }
        c++;
    }
    printf("Decrypted message: %s\n", newcontent);
    FILE *file = fopen(fname, "w");
        if (file != NULL) {
            fprintf(file, "%s", newcontent);
            fclose(file);
        }
    fileoperations();
}

