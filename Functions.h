#include "declarations.h"

void read_char()
{
    cour_char = fgetc(file);
}
//------------
void read_string()
{
    memset(Cour_Token.value, '\0', 21);

    int nbchar = 0;
    Cour_Token.value[nbchar] = cour_char;

    nbchar++;
    read_char();
    while (((cour_char >= 'a' && cour_char <= 'z') || (cour_char >= '0' && cour_char <= '9')) && nbchar <= 20)
    {

        Cour_Token.value[nbchar] = cour_char;
        nbchar++;
        read_char();
    }
    if (nbchar <= 20)
    {
        tokenmap(2);
    }
    else
    {
        Error_table[curseur] = ID_LONG;
        curseur++;
        tokenmap(-1);
    }
}
//-----------------------
void read_number()
{

    int taille = 0;

    Cour_Token.value[taille] = cour_char;
    taille++;
    read_char();
    while (cour_char >= '0' && cour_char <= '9' && taille <= 11)
    {

        Cour_Token.value[taille] = cour_char;
        taille++;
        read_char();
    }
    if (taille <= 11)
    {

        tokenmap(1);
    }
    else
    {
        Error_table[curseur] = NUM_LONG;
        curseur++;
        tokenmap(-1);
    }
}
//-----------------------
void read_symbole()
{

    // memset(cour_noeud.token_str,'', sizeof(cour_noeud.token_str));
    memset(Cour_Token.identif, '\0', 21);
    memset(Cour_Token.value, '\0', 21);
    Cour_Token.token = NULL_TOKEN;
    int check = 0;
    while (cour_char == '\n' || cour_char == '\t' || cour_char == ' ')
    {
        read_char();
    }
    if ((cour_char >= 'a' && cour_char <= 'z') || (cour_char >= 'A' && cour_char <= 'Z'))
    {
        read_string();
        check = 1;
    }
    else if (cour_char >= '0' && cour_char <= '9')
    {
        read_number();
        check = 1;
    }
    else if (cour_char == 59)
    {
        Cour_Token.token = PV_TOKEN;
        Cour_Token.value[0] = ';';
        tokenmap(0);
    }
    else if (cour_char == 46)
    {
        Cour_Token.token = PT_TOKEN;
        Cour_Token.value[0] = '.';
        tokenmap(0);
    }
    else if (cour_char == 43)
    {
        Cour_Token.token = PLUS_TOKEN;
        Cour_Token.value[0] = '+';
        tokenmap(0);
    }
    else if (cour_char == 45)
    {
        Cour_Token.token = MOINS_TOKEN;
        Cour_Token.value[0] = '-';
        tokenmap(0);
    }
    else if (cour_char == 42)
    {
        Cour_Token.token = MULT_TOKEN;
        Cour_Token.value[0] = '*';
        tokenmap(0);
    }
    else if (cour_char == 47)
    {
        Cour_Token.token = DIV_TOKEN;
        Cour_Token.value[0] = '/';
        tokenmap(0);
    }
    else if (cour_char == 44)
    {
        Cour_Token.token = VIR_TOKEN;
        Cour_Token.value[0] = ',';
        tokenmap(0);
    }
    else if (cour_char == 40)
    {
        Cour_Token.token = PO_TOKEN;
        Cour_Token.value[0] = '(';
        tokenmap(0);
    }
    else if (cour_char == 41)
    {
        Cour_Token.token = PF_TOKEN;
        Cour_Token.value[0] = ')';
        tokenmap(0);
    }
    else if (cour_char == 61)
    {
        Cour_Token.token = EG_TOKEN;
        Cour_Token.value[0] = '=';
        tokenmap(0);
    }
    else if (cour_char == ':')
    {
        read_char();
        if (cour_char == '=')
        {
            Cour_Token.token = AFF_TOKEN;
            strcpy(Cour_Token.value, ":=");
            tokenmap(0);
        }
        else
        {
            check = 1;
            Error_table[curseur] = CAR_INC;
            curseur++;
            tokenmap(-1);
        }
    }
    else if (cour_char == 60)
    {
        read_char();
        if (cour_char == 61)
        {
            Cour_Token.token = INFEG_TOKEN;
            strcpy(Cour_Token.value, "<=");
            tokenmap(0);
        }
        else if (cour_char == 62)
        {
            Cour_Token.token = DIFF_TOKEN;
            strcpy(Cour_Token.value, "<>");
            tokenmap(0);
        }
        else
        {
            Cour_Token.token = INF_TOKEN;
            Cour_Token.value[0] = '<';
            tokenmap(0);
            check = 1;
        }
    }
    else if (cour_char == 62)
    {
        read_char();
        if (cour_char == 61)
        {
            Cour_Token.token = SUPEG_TOKEN;
            strcpy(Cour_Token.value, ">=");
            tokenmap(0);
        }
        else
        {
            Cour_Token.token = SUP_TOKEN;
            Cour_Token.value[0] = '>';
            tokenmap(0);
            check = 1;
        }
    }
    else if (cour_char == '{')
    {
        read_char();
        if (cour_char == 42)
        {
            commentignore();
        }
        else
        {
            Error_table[curseur] = CAR_INC;
            curseur++;
            tokenmap(-1);
        }
    }
    else
    {
        if (cour_char != EOF)
        {
            Error_table[curseur] = CAR_INC;
            curseur++;
            tokenmap(-1);
        }
        else
        {
            Cour_Token.token = FIN_TOKEN;
            strcpy(Cour_Token.identif, "EOF_TOKEN");
        }
    }
    if (Cour_Token.token != NULL_TOKEN)
        push(Cour_Token);
    if (!check)
        read_char();
}

//-----------------------

void tokenmap(int type)
{
    if (type == 0)
    {
        for (int i = 0; i < 17; i++)
        {
            if (Cour_Token.token == specials[i].token)
            {
                strcpy(Cour_Token.identif, specials[i].identif);
                break;
            }
        }
    }
    else if (type == 1)
    {
        strcpy(Cour_Token.identif, "NUM_TOKEN");
        Cour_Token.token = NUM_TOKEN;
    }
    else if (type == -1)
    {
        strcpy(Cour_Token.identif, "ERREUR_TOKEN");
        Cour_Token.token = ERREUR_TOKEN;
    }
    else
    {
        int check = 0;
        for (int i = 0; i < strlen(Cour_Token.value); i++)
        {
            if (islower(Cour_Token.value[i]))
                Cour_Token.value[i] = Cour_Token.value[i] - 'a' + 'A';
        }
        // printf("%s ", Cour_Token.value);
        for (int i = 0; i < 11; i++)
        {
            if (strcmp(Cour_Token.value, key_words[i].identif) == 0)
            {
                strcpy(Cour_Token.identif, key_words[i].identif);
                strcat(Cour_Token.identif, "_TOKEN");
                Cour_Token.token = key_words[i].token;
                check = 1;
                break;
            }
        }
        if (check == 0)
        {
            strcpy(Cour_Token.identif, "ID_TOKEN");
            Cour_Token.token = ID_TOKEN;
        }
    }
}
//-------------------------
//----------------------------
void Analex(const char *filename)
{
    file = fopen(filename, "r+");
    read_char();

    while (cour_char != EOF)
    {
        read_symbole();

        // if (Cour_Token.token != NULL_TOKEN)
        // {
        //     printf("%s ", Cour_Token.value);
        // }
        // printf("%s ", Cour_Token.identif);
    }
    if (head == NULL)
    {
        Error_table[curseur] = FICH_VID;
        curseur++;
        printf("Erreur :%s", mes_err[1].message_erreur);
        return;
    }
    // display();

    fclose(file);
}
void push(Maptoken Cour_Token)
{
    struct node *temp, *ptr;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->info = Cour_Token;
    temp->next = NULL;
    if (head == NULL)
    {
        head = temp;
    }
    else
    {
        ptr = head;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = temp;
    }
}
//------------------------
void display()
{
    struct node *ptr;
    if (head == NULL)
    {
        printf("nList is empty:n");
        return;
    }
    else
    {
        ptr = head;
        while (ptr != NULL)
        {
            if (ptr->info.identif[0] != '\n')
                printf("%s ", ptr->info.identif);
            ptr = ptr->next;
        }
    }
}
//--------------
void commentignore()
{

    while (cour_char != EOF)
    {
        read_char();
        if (cour_char == '*')
        {
            read_char();
            if (cour_char == '}')
            {
                break;
            }
        }
    }
}
//------------
