#include <stdio.h>

int main(){
    float num1, num2, ris; // operandi e risultato    
    char op; // operatore
    scanf("%f", &num1);
    scanf("%f", &num2);
    scanf(" %c", &op);
    switch(op){
        case '+':
            ris = num1 + num2;
            break;
        case '-':
            ris = num1 - num2;
            break;
        case '/':
            ris = num1 / num2;
            break;
        case '%':
            ris = (int)num1 % (int)num2;
            break;
    }
    printf("%.1f", ris);
    return 0;
}
