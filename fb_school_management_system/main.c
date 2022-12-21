#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char* STUDENT_FORMAT = "%d,%s,%s";
const char* TEACHER_FORMAT = "%d,%s";
const char* SUBJECT_FORMAT = "%s,%s";

const char* STUDENT_FILE = "students.txt";
const char* TEACHER_FILE = "teachers.txt";
const char* SUBJECT_FILE = "subjects.txt";


typedef struct teacher {
    char* name;
    unsigned int age;
} teacher ;

typedef struct subject {
    char* name;
    teacher teacher;
} subject ;

typedef struct student {
    unsigned int rollnumber;
    char* name;
    subject subject;
} student;

int create_file(const char* filename){
    remove(filename);
    FILE *file = fopen(filename, "w");
    fclose(file);
    return 0;
}

int create_required_files(){
    create_file(STUDENT_FILE);
    create_file(TEACHER_FILE);
    create_file(SUBJECT_FILE);
    return 0;
}

int add_teacher(teacher tchr){
    FILE *file = fopen(TEACHER_FILE, "a+");
    fprintf(file, TEACHER_FORMAT, tchr.age, tchr.name);
    fclose(file);
    return 0;
}

int get_teacher(char* target, teacher* tchr){

    // storing data into a struct pointer works
    // tchr->name = "Hello";
    // tchr->age = 23;
    // return 0;

    FILE *file = fopen(TEACHER_FILE, "r");
    char response[30];
    int response2;
    fscanf(file, "%d,%s", &response2, response);
    printf("The name is %s and the age is %d \n", response, response2);
    strcpy(tchr->name, response);
    tchr->age = response2;
    return 0;

    // char name[20];
    // int age;

    // while(fscanf(file, TEACHER_FORMAT, name, age) == 1){
    //     printf("the name is %s and the age is %d \n", name, age);
    //     if(strcmp(name, target) == 0){
    //         puts("found");
    //         strcpy(tchr->name, name);
    //         tchr->age = age;
    //         printf("name: %s and the age: %d \n", tchr->name, tchr->age);
    //         fclose(file);
    //         return 0;
    //     }
    // }
    // fclose(file);
    // return 1;
}

int add_subject(subject sbjct){
    return 0;
}

int get_subject(subject* sbjct){
    return 0;
}


int add_student(student stdnt){
    return 0;
}

int get_student(student *stdnt){
    return 0;
}

int main(){
    printf("Welcome to the school managementn system application \n");
    create_required_files();
    teacher sample = {"John Egba", 33};
    add_teacher(sample);
    teacher result;
    int success = get_teacher("John", &result);
    printf("getting the teacher was successful ? %d \n", success == 0);
    printf("name: %s and the age: %d \n", result.name, result.age);
    return 0;
}