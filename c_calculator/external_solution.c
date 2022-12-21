#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(int argc, char* argv[]){
    float valueOne;
    float valueTwo;
    char operator;
    float answer;

    printf("Enter Calculation : \n");
    scanf("%f %c %f", &valueOne, &operator, &valueTwo);

    switch (operator)
    {
        case '/': 
            answer = valueOne/valueTwo;
            break;
        case '*': 
            answer = valueOne*valueTwo;
            break;
        case '+': 
            answer = valueOne+valueTwo;
            break;
        case '-': 
            answer = valueOne-valueTwo;
            break;
        case '^': 
            answer = pow(valueOne,valueTwo);
            break;
        case ' ': 
            answer = sqrt(valueTwo);
            break;
        default: goto fail;
    }

    printf("%.9g%c%.9g =  %.6g\n\n",valueOne,operator, valueTwo, answer);
    goto exit;

    fail:
      printf("Fail. \n");
    exit:
      printf("Execution complete. \n");
      return 0;
}