#include "Functions.h"
typedef enum
{
    PROGRAM_TOKEN_ERREUR,
    CONST_TOKEN_ERREUR,
    VAR_TOKEN_ERREUR,
    BEGIN_TOKEN_ERREUR,
    END_TOKEN_ERREUR,
    IF_TOKEN_ERREUR,
    THEN_TOKEN_ERREUR,
    WHILE_TOKEN_ERREUR,
    DO_TOKEN_ERREUR,
    READ_TOKEN_ERREUR,
    WRITE_TOKEN_ERREUR,
    PV_TOKEN_ERREUR,
    PT_TOKEN_ERREUR,
    PLUS_TOKEN_ERREUR,
    MOINS_TOKEN_ERREUR,
    MULT_TOKEN_ERREUR,
    DIV_TOKEN_ERREUR,
    VIR_TOKEN_ERREUR,
    AFF_TOKEN_ERREUR,
    EG_TOKEN_ERREUR,
    INF_TOKEN_ERREUR,
    INFEG_TOKEN_ERREUR,
    SUP_TOKEN_ERREUR,
    SUPEG_TOKEN_ERREUR,
    DIFF_TOKEN_ERREUR,
    PO_TOKEN_ERREUR,
    PF_TOKEN_ERREUR,
    FIN_TOKEN_ERREUR,
    ID_TOKEN_ERREUR,
    NUM_TOKEN_ERREUR,
} Codes_LEX_Erreurs;
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void CONSTS();
void VARS();
void INSTS();
void INST();
void COND();
void EXPR();
void TERM();
void FACT();
struct node *ptr = NULL;
void Symbole_Suiv()
{
    if (ptr == NULL)
        printf("A");
    else
        printf("%s ", Cour_Token.value);
    ptr = ptr->next;
    Cour_Token = ptr->info;
}

void Test_Symbole(Codes_LEX token, Codes_LEX_Erreurs erreur)
{
    if (Cour_Token.token == token)
    {

        Symbole_Suiv();
    }
    else
    {
        // printf("error\n");
    }
}
void BLOCK()
{
    CONSTS();
    VARS();
    INSTS();
}

void PROGRAM()
{
    ptr = head;
    Cour_Token = ptr->info;
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_TOKEN_ERREUR);
    Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
    Test_Symbole(PV_TOKEN, PV_TOKEN_ERREUR);
    BLOCK();
    Test_Symbole(PT_TOKEN, PT_TOKEN_ERREUR);
}

void CONSTS()
{
    switch (Cour_Token.token)
    {
    case CONST_TOKEN:
        Symbole_Suiv();
        Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
        Test_Symbole(EG_TOKEN, EG_TOKEN_ERREUR);
        Test_Symbole(NUM_TOKEN, NUM_TOKEN_ERREUR);
        Test_Symbole(PV_TOKEN, PV_TOKEN_ERREUR);
        while (Cour_Token.token == ID_TOKEN)
        {
            Symbole_Suiv();
            Test_Symbole(EG_TOKEN, EG_TOKEN_ERREUR);
            Test_Symbole(NUM_TOKEN, NUM_TOKEN_ERREUR);
            Test_Symbole(PV_TOKEN, PV_TOKEN_ERREUR);
        };
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    default:
        printf("error8\n");
        break;
    }
}
void VARS()
{
    switch (Cour_Token.token)
    {
    case VAR_TOKEN:
        Symbole_Suiv();
        Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
        while (Cour_Token.token == VIR_TOKEN)
        {
            Symbole_Suiv();
            Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
        }
        Test_Symbole(PV_TOKEN, PV_TOKEN_ERREUR);
        break;
    case BEGIN_TOKEN:
        break;
    default:
        // Erreur(CONST_VAR_BEGIN_ERR);
        break;
    }
}
void INSTS()
{
    Test_Symbole(BEGIN_TOKEN, BEGIN_TOKEN_ERREUR);
    INST();
    while (Cour_Token.token == PV_TOKEN)
    {
        Symbole_Suiv();
        INST();
    }
    Test_Symbole(END_TOKEN, END_TOKEN_ERREUR);
}
void INST()
{
    switch (Cour_Token.token)
    {
    case BEGIN_TOKEN:
        INSTS();
        break;
    case ID_TOKEN:
        AFFEC();
        break;
    case IF_TOKEN:
        SI();
        break;
    case WHILE_TOKEN:
        TANTQUE();
        break;
    case WRITE_TOKEN:
        ECRIRE();
        break;
    case READ_TOKEN:
        LIRE();
        break;
    default:
        printf("%s \n", Cour_Token.identif);
        break;

        //case esilon :) a faire après
    }
}
void AFFEC()
{
    Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
    Test_Symbole(AFF_TOKEN, AFF_TOKEN_ERREUR);
    EXPR();
}
void SI()
{
    Test_Symbole(IF_TOKEN, IF_TOKEN_ERREUR);
    COND();
    Test_Symbole(THEN_TOKEN, THEN_TOKEN_ERREUR);
    INST();
}
void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN, WHILE_TOKEN_ERREUR);
    // printf("%ssqs", Cour_Token.value);
    COND();
    Test_Symbole(DO_TOKEN, DO_TOKEN_ERREUR);
    INST();
}
void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN, WRITE_TOKEN_ERREUR);
    Test_Symbole(PO_TOKEN, PO_TOKEN_ERREUR);
    EXPR();
    while (Cour_Token.token == VIR_TOKEN)
    {
        Symbole_Suiv();
        EXPR();
    }
    Test_Symbole(PF_TOKEN, PF_TOKEN_ERREUR);
}
void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_TOKEN_ERREUR);
    Test_Symbole(PO_TOKEN, PO_TOKEN_ERREUR);
    Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
    while (Cour_Token.token == VIR_TOKEN)
    {
        Symbole_Suiv();
        Test_Symbole(ID_TOKEN, ID_TOKEN_ERREUR);
    }
    Test_Symbole(PF_TOKEN, PF_TOKEN_ERREUR);
}
void COND()
{
    EXPR();
    switch (Cour_Token.token)
    {
    case EG_TOKEN:
        break;
    case DIFF_TOKEN:
        break;
    case INF_TOKEN:
        break;
    case SUP_TOKEN:
        break;
    case INFEG_TOKEN:
        break;
    case SUPEG_TOKEN:
        break;
    default:
        printf("error10\n");
        break;

        return;
    }
    Symbole_Suiv();
    EXPR();
}
void EXPR()
{
    TERM();
    while (Cour_Token.token == PLUS_TOKEN || Cour_Token.token == MOINS_TOKEN)
    {
        Symbole_Suiv();
        TERM();
    }
}
void TERM()
{
    FACT();
    while (Cour_Token.token == MULT_TOKEN || Cour_Token.token == DIV_TOKEN)
    {
        Symbole_Suiv();
        FACT();
    }
}
void FACT()
{
    switch (Cour_Token.token)
    {
    case ID_TOKEN:
        Symbole_Suiv();
        break;
    case NUM_TOKEN:
        Symbole_Suiv();
        break;
    case PO_TOKEN:
        EXPR();
        Test_Symbole(PF_TOKEN, PF_TOKEN_ERREUR);
        break;
    }
}
