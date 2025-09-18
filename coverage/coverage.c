#include <stdio.h>
#include <string.h>

int main(){
    char input[100];
    fgets(input, 100, stdin);
    if (input[0] == '1'){
        if (input[1] == '2'){
            if (input[2] == '3'){
                if (input[3] == '4'){
                    if (input[4] == '5'){
                        printf("CASE 5\n");
                    }
                }
                else{
                    printf("CASE 3\n");
                }
            }
            else{
                printf("CASE 4\n");
            }
        }
    }
}