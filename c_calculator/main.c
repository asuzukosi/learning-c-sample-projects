#include<stdio.h>
#include<stdlib.h>

// we are defining an arithmentic_operation function pointer
// that can take in two integers as input and return an integer
typedef int(*artithmetic_operation)(int, int);

typedef struct prompt {
    int input1;
    int input2;
    char operation;
} prompt;

int add(int a, int b){
    return a + b;
}

int subtract(int a, int b){
    return a - b;
}

int multiply(int a, int b){
    return a * b;
}

int divide(int a, int b){
    return a / b;
}

artithmetic_operation get_operation(char operation){
    switch (operation)
    {
        case '+':
            return add;
            break;
        case '-':
            return subtract;
            break;
        case '*':
            return multiply;
            break;
        case '/':
            return divide;
            break;
        default:
            fprintf(stderr, "invalid input \n");
            exit(2);
            break;
    }
}

prompt read_prompt(){
    int input1;
    int input2;
    char operation;
    printf("Enter your operation: please use appropriat format ie 2+4 (no spaces) \n");
    scanf("%d%c%d", &input1, &operation, &input2);
    prompt data = {input1, input2, operation};
    return data;
}

int main(int argc, char *argv[]){

    printf("Welcome to the simple c calculator\n");
    char stop = 'n';
    while(stop != 'y'){
        prompt response = read_prompt();
        artithmetic_operation operation = get_operation(response.operation);

        printf("The result of the operation is %d \n", operation(response.input1, response.input2));
        printf("Would you like to stop the program ? (y) to stop \n");
        scanf("%c", &stop); // scan away first extra
        scanf("%c", &stop);
    }
   
    
}