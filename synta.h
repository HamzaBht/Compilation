#include "Functions.h"
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
bool c = 0;
struct node *ptr = NULL;
// int verify_symbol(char identif[21])
// {
//     struct DataItem *s = search(identif);
//     if (s == NULL)
//         return -1;
//     else if (s->data.isconst == 1)
//         return -2;
//     return s->key;
// }
void Symbole_Suiv()
{
    if (ptr == NULL)
        printf("A");
    else
        // printf("%s ", Cour_Token.value);
        ptr = ptr->next;
    prev_token = Cour_Token;
    Cour_Token = ptr->info;
}

void Test_Symbole(Codes_LEX token)
{

    if (Cour_Token.token == token)
    {

        Symbole_Suiv();
    }
    else if (c == 0)
    {

        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
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
    Test_Symbole(PROGRAM_TOKEN_ERREUR);
    Test_Symbole(ID_TOKEN);
    // Cour_symbole = prev_token;
    // Cour_symbole.isconst = false;
    // Cour_symbole.p_type = -1;
    // insert(Cour_symbole.value, Cour_symbole);
    Test_Symbole(PV_TOKEN);
    BLOCK();
    Test_Symbole(PT_TOKEN);
}

void CONSTS()
{
    switch (Cour_Token.token)
    {
    case CONST_TOKEN:
        Symbole_Suiv();
        Test_Symbole(ID_TOKEN);
        // Cour_symbole = prev_token;
        // Cour_symbole.isconst = true;
        // Cour_symbole.p_type = 0;
        // Cour_symbole.size = 1;
        Test_Symbole(EG_TOKEN);
        Test_Symbole(NUM_TOKEN);
        // Cour_symbole.np_type = -1;
        // memset(Cour_symbole.r_value, '\0', sizeof(Cour_symbole.r_value));
        // strcpy(Cour_symbole.r_value, prev_token.value);
        // insert(Cour_symbole.value, Cour_symbole);
        Test_Symbole(PV_TOKEN);
        while (Cour_Token.token == ID_TOKEN)
        {
            Symbole_Suiv();
            // Cour_symbole = prev_token;
            // Cour_symbole.isconst = true;
            // Cour_symbole.p_type = 0;
            // Cour_symbole.size = 1;
            Test_Symbole(EG_TOKEN);
            Test_Symbole(NUM_TOKEN);
            // Cour_symbole.np_type = -1;
            // strcpy(Cour_symbole.r_value, prev_token.value);
            // insert(Cour_symbole.value, Cour_symbole);
            Test_Symbole(PV_TOKEN);
        };
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[CONST_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}
void VARS()
{
    switch (Cour_Token.token)
    {
    case VAR_TOKEN:
        Symbole_Suiv();
        Test_Symbole(ID_TOKEN);
        // Cour_symbole = prev_token;
        // Cour_symbole.isconst = false;
        // Cour_symbole.p_type = 0;
        // Cour_symbole.size = 1;
        // insert(Cour_symbole.value, Cour_symbole);
        while (Cour_Token.token == VIR_TOKEN)
        {
            Symbole_Suiv();
            Test_Symbole(ID_TOKEN);
            // Cour_symbole = prev_token;
            // Cour_symbole.isconst = false;
            // Cour_symbole.p_type = 0;
            // Cour_symbole.size = 1;
            // insert(Cour_symbole.value, Cour_symbole);
        }
        Test_Symbole(PV_TOKEN);
        break;
    case BEGIN_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[VAR_TOKEN].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}
void INSTS()
{
    Test_Symbole(BEGIN_TOKEN);
    INST();
    // Symbole_Suiv();
    prev_token = Cour_Token;
    while (Cour_Token.token == PV_TOKEN)
    {
        Symbole_Suiv();
        INST();
        if (Cour_Token.token != END_TOKEN && Cour_Token.token != PV_TOKEN)
        {
            c = 1;
            printf("un ; est manquant ");
            break;
        }
    }
    if (c == 0)
        Test_Symbole(END_TOKEN);
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
    case END_TOKEN:
        break;
    default:
        printf("%s\n dans la ligne : %d coloonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
    }
}
void AFFEC()
{
    Test_Symbole(ID_TOKEN);
    // int l = verify_symbol(prev_token.value);
    // printf("%s", prev_token.identif);
    // if (l == -2)
    // {
    //     printf("affectation non alloué, il s'agit d une constante ");
    //     Test_Symbole(NULL_TOKEN);
    // }
    // else if (l == -1)
    // {
    //     printf("edentifiant n'existe pass");
    // }
    // indx = l;
    Test_Symbole(AFF_TOKEN);
    EXPR();
}
void SI()
{
    Test_Symbole(IF_TOKEN);
    COND();
    Test_Symbole(THEN_TOKEN);
    INST();
}
void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN);
    // printf("%ssqs", Cour_Token.value);
    COND();
    Test_Symbole(DO_TOKEN);
    INST();
}
void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN);
    Test_Symbole(PO_TOKEN);
    EXPR();
    while (Cour_Token.token == VIR_TOKEN)
    {
        Symbole_Suiv();
        EXPR();
    }
    Test_Symbole(PF_TOKEN);
}
void LIRE()
{
    Test_Symbole(READ_TOKEN);
    Test_Symbole(PO_TOKEN);
    Test_Symbole(ID_TOKEN);
    // int l = verify_symbol(prev_token.value);
    // printf("%s", prev_token.value);
    // if (l == -1)
    // {
    //     printf("l'édentifiant n'existe pas ");
    //     Test_Symbole(NULL_TOKEN);
    // }
    while (Cour_Token.token == VIR_TOKEN)
    {

        Symbole_Suiv();
        Test_Symbole(ID_TOKEN);
        // int l = verify_symbol(prev_token.value);
        // if (l == -1)
        // {
        //     printf("l'édentifiant n'existe pas ");
        //     Test_Symbole(NULL_TOKEN);
        // }
    }
    Test_Symbole(PF_TOKEN);
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
        printf("%s\n dans la ligne : %d colonne :%d \n", maperror[Cour_Token.token].message_erreur, Cour_Token.ligne, Cour_Token.colonne);
        break;
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
        // int p = verify_symbol(prev_token.value);
        // if (hashArray[indx]->data.p_type != hashArray[p]->data.p_type)
        // {
        //     printf("Error : opération non permise\n");
        //     Test_Symbole(NULL_TOKEN);
        // }
        break;
    case NUM_TOKEN:
        Symbole_Suiv();
        break;
    case PO_TOKEN:
        EXPR();
        Test_Symbole(PF_TOKEN);
        break;
    }
}
