#include "synta.h"
int main(int *argc, char *argv[])
{

    Analex("code_test.txt");

    PROGRAM();
    //hello there

    if (Cour_Token.token == FIN_TOKEN)
    {
        printf("BRAVO");
    }
    else
        printf("pas bravo");

    return 0;
}