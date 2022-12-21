#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>

// define constants and global variables

int addStudent(FILE *filePointer);
int modify(FILE *filePointer);
int display(FILE *filePointer);
int Individual(FILE *filePointer);
int password();
FILE* del(FILE* fp);
int printChar(char ch, int n);
void title();
FILE *passwordFile;
int checkPassword();
int setPassword();


typedef struct pass{
    char pass[25];
} pa;

typedef struct Stud {
    char name[100];
    char dept[50];
    int roll;
    float sgpa[12];
    float cgpa;
} Student;

int printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
    return 0;
}

int setConsoleTitle(char *message){
    puts("******************************************");
    printf("**** %s ****** \n", message);
    puts("******************************************");
 
    return 0;
}

int getOrCreateDatabaseFile(FILE *databaseFile){
    // Try to get or create database
    if((databaseFile = fopen("db.txt", "rb+"))== NULL){
        // The daabae does not exist so we have to create it
        if((databaseFile = fopen("db.txt", "wb+")) == NULL){
            // Unable to create database file
            fprintf(stderr, "unable to create or open database");
            exit(1);
            return 0;
        }
    }
    return 0;
}

int getCharacter(){
    char key;
	scanf("%c", &key);
    return 0;
}

int welcomeMessage(){
    printf(" \n\n\n\n\n     *  *  *  *  *  *  *  *");
	printf("\n\n     *                    *");
	printf("\n\n     *       Welcome      *");
	printf("\n\n     *                    *");
	printf("\n\n     *  *  *  *  *  *  *  *");
	printf("\n\nPress any key to continue...... ");
    getCharacter();
    printf("\n\nKosi Asuzu Project December 2022");
    printf("\n\nThe A Team");
    printf("\n\nExample International University\n\t\t\t");
    printf("\n\n\npress any key to Enter...");
    getCharacter();
    return 0;
}

int getUserChoice(int *option){
    printf("\n\t");
        printChar('*',64);

        printf("\n\n1. Add Student");
        printf("\n\n2. Modify Student");
        printf("\n\n3. Show All Student");
        printf("\n\n4. Individual View");
        printf("\n\n5. Remove Student");
        printf("\n\n6. Change Password");
        printf("\n\n7. Logout\n\t");
        printf("\n\nEnter Your Option :--> ");
        scanf("%d",option);
        return 0;
}

int main(){
    int ch, id, k, i;
    char c, add, pas[50];
    setConsoleTitle("Student Management Application");
    FILE *databaseFile;
    Student s;
    int option;
    char another;

    // Try to get or create database
    if((databaseFile = fopen("db.txt", "rb+"))== NULL){
        // The daabae does not exist so we have to create it
        if((databaseFile = fopen("db.txt", "wb+")) == NULL){
            // Unable to create database file
            fprintf(stderr, "unable to create or open database");
            exit(1);
            return 0;
        }
    }


    printf("<<<< Loading Please Wait >>>> \n");
	for(i=0; i<5; i++){
        printf("\t(*_*)");
        sleep(2);
    }
    puts("");
    welcomeMessage();
    checkPassword();
    choice:
        getUserChoice(&option);

    switch(option){
        case 1:
            addStudent(databaseFile);
            goto choice;
            break;
        case 2:
            modify(databaseFile);
            goto choice;
            break;
        case 3:
            display(databaseFile);
            goto choice;
            break;
        case 4:
            Individual(databaseFile);
            goto choice;
            break;
        case 5:
            databaseFile = del(databaseFile);
            goto choice;
            break;
        case 6:
            setPassword();
            goto choice;
            break;
        case 7:
            return 1;
            break;
        default:
            printf("No Action Detected. \n");
            printf("Press Any Key to go back to the option selection. \n");
            fflush(stdin);
            getCharacter();
            goto choice;
    }
    return 0;
}

FILE* del(FILE *filePointer){
    FILE *tempDatabase;

    if((tempDatabase = fopen("temp.txt", "wb+")) == NULL){
        puts("Unable to delete item because we can not modify the file system");
        return 0;
    }
    int targetRollId;
    int found = 0;

    puts("Enter the roll number of the student you would like to delete: ");
    fflush(stdin);
    scanf("%d", &targetRollId);

    Student s;
    rewind(filePointer);

    while(fread(&s, sizeof(s), 1, filePointer) == 1){
        if(s.roll == targetRollId){
            printf("Deleting student %s \n", s.name);
            printChar('=', 60);
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, tempDatabase);
    }

    if(found != 1){
        printf("Student with roll id %d not found .... \n", targetRollId);
        printChar('=', 60);
    }

    fclose(filePointer);
    fclose(tempDatabase);

    remove("db.txt");
    rename("temp.txt", "db.txt");

    if((tempDatabase=fopen("db.txt","rb+"))==NULL)
    {
        printf("ERROR");
        exit(4);
        return  NULL;
    }

    puts("Operation complete.");
    puts("Press any key to continue");
    fflush(stdin);

    getCharacter();

    return tempDatabase;
}

int addStudent(FILE *filePointer){
    puts("*** Welcome to the student data entry section ***");
    char userChoice = 'y';
    Student s;
    int i;
    float cgpa;

    fseek(filePointer, 0, SEEK_END);
    while(userChoice == 'y' || userChoice == 'Y'){
        printf("Enter Full Name of Student: ");
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';

        printf("Enter Depertment Name: ");
        fflush(stdin);
        fgets(s.dept,50,stdin);
        s.dept[strlen(s.dept)-1]='\0';

        printf("Enter Roll number: ");
        scanf("%d",&s.roll);

        printf("Enter SGPA for 12 semesters\n");
        for(i=0, cgpa=0; i<12; i++)
        {
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];

        }
        cgpa /= 12;
        s.cgpa = cgpa;

        fwrite(&s, sizeof(s), 1, filePointer);
        printf("Added student %s to the database \n", s.name);
        fflush(stdin);
        puts("Would you like to add anohter add another student ? (y/n)");
        scanf("%c", &userChoice);
    }
    return 0;
}

int modify(FILE *filePointer){
    puts("**Welcome to the profile modification sub system ");
    puts("Please enter the roll id of the student you would like to modify");

    fflush(stdin);
    int targetRollId;

    scanf("%d", &targetRollId);
    Student s;
    int found = 0;
    int i;
    float cgpa;
    rewind(filePointer);

    while(fread(&s, sizeof(s), 1, filePointer)){
        if(s.roll == targetRollId){
            found = 1;
            break;
        }
    }
    if(found == 1){

        printf("Student with roll id %d found, please enter new details \n", targetRollId);
        fseek(filePointer,-sizeof(s),SEEK_CUR);
        printChar('=',38);

        printf("Student Name: %s \n",s.name);
        printf("Student Roll: %d \n",s.roll);
        printChar('=',38);

        printf("Enter New Data for the student\n");
        printf("Enter Full Name of Student: \n");
        fflush(stdin);
        fgets(s.name,100,stdin);
        s.name[strlen(s.name)-1]='\0';

        printf("Enter Department: \n");
        fflush(stdin);
        fgets(s.dept,50,stdin);
        s.dept[strlen(s.dept)-1]='\0';

        printf("Enter Roll number: \n");
        scanf("%d",&s.roll);


        printf("tEnter SGPA for 12 semesters\n");
        for(i=0,cgpa=0; i<12; i++)
        {
            scanf("%f",&s.sgpa[i]);
            cgpa+=s.sgpa[i];

        }
        cgpa=cgpa/8.0;

        s.cgpa = cgpa;
        fwrite(&s,sizeof(s),1,filePointer);


    }else{
        printf("Student with roll id %d not found ... \n", targetRollId);
    }
    puts("Enter any key to continue ...");
    fflush(stdin);
    getCharacter();
    return 0;
}

int display(FILE* filePointer){
    Student s;
    printChar('=', 35); 
    puts("");
    rewind(filePointer);

    while((fread(&s,sizeof(s),1,filePointer))==1)
    {
        printf("NAME : %s \n",s.name);
        printf("Depertment : %s \n",s.dept);
        printf("ROLL : %d \n",s.roll);
        printf("SGPA: ");

        for(int i=0; i<12; i++)
            printf("| %.2f |",s.sgpa[i]);
        printf("GPA : %.2f\n\t",s.cgpa);
        printChar('-',65);
        puts("");
    }
    puts("");
    printChar('=', 35);
    puts("");
    puts("Enter any key to continue ...");
    fflush(stdin);
    getCharacter();
    return 0;
}

int Individual(FILE *filePointer){
    Student s;
    puts("Enter the roll id of the student you wish to view : ");
    fflush(stdin);
    int targetRollId;
    scanf("%d", &targetRollId);
    rewind(filePointer);

    while(fread(&s, sizeof(s), 1, filePointer) == 1){
        if(targetRollId == s.roll){
            printf("NAME : %s \n",s.name);
            printf("Depertment : %s \n",s.dept);
            printf("ROLL : %d \n",s.roll);
            printf("SGPA: ");

            for(int i=0; i<12; i++)
                printf("| %.2f |",s.sgpa[i]);
            printf("GPA : %.2f\n\t",s.cgpa);
            printChar('-',65);
            puts("");
            puts("Enter any key to continue ...");
            fflush(stdin);
            getCharacter();
            return 0;
        }
    }
    printf("Student with roll id %d not found ", targetRollId);
    puts("Enter any key to continue ...");
    fflush(stdin);
    getCharacter();
    return 0;
}
int setPassword(){
    puts("Enter your password");
    fflush(stdin);
    char password[25];
    fgets(password, 25, stdin);
    puts("Save Password (y/n)");
    fflush(stdin);
    char c;
    scanf("%c", &c);

    if(c == 'y' || c == 'Y'){
        passwordFile = fopen("password.txt", "w+");
        fwrite(&password, 25, 1, passwordFile);\
        fclose(passwordFile);
        puts("Password saved successfully");
        puts("<<<returning to main menu>>>");
    } else{
        puts("Password not saved");
        puts("Press any key to return to main menu...");
        getCharacter();
    }

    return 0;
}

int checkPassword(){
    // if password doesn't exist, create a password
    if(!(passwordFile = fopen("password.txt", "rb+"))){
        fclose(passwordFile);
        puts("Password does not currently exists, please create one");
        setPassword();
    }else {
        puts("Enter your password ...");
        char inputPassword[25];
        fflush(stdin);
        fgets(inputPassword, 25, stdin);
        passwordFile = fopen("password.txt", "rb+");
        char password[25];
        fgets(password,25,passwordFile);
        if(strcmp(inputPassword,password)==0){
            puts("Password is correct, continuing to application...");
            puts("Press and key to contiue...");
            fflush(stdin);
            getCharacter();
        }
        else{
            puts("Invalid passord");
            exit(2);
        }
    }

    return 0;
}