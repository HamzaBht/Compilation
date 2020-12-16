#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
typedef enum
{
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    EG_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    FIN_TOKEN,
    ID_TOKEN,
    NUM_TOKEN,
    ERREUR_TOKEN,
    NULL_TOKEN
} Codes_LEX;
typedef struct
{
    Codes_LEX token;
    char identif[21];
    char value[21];
} Maptoken;
//-----
typedef enum
{
    CAR_INC,
    FICH_VID,
    ID_LONG,
    NUM_LONG,
} Erreur;
//------
typedef struct
{
    Erreur code_err;
    char message_erreur[40];
} Erreurs;
//-------------------------------------
Erreurs mes_err[4] = {{CAR_INC, "caractère inconnu"},
                      {FICH_VID, "fichier vide"},
                      {ID_LONG, "l'identifiant est long"},
                      {NUM_LONG, "le nombre est grand"}};
//--------
int Error_table[(int)1e5];
int curseur = 0;
//------
Maptoken specials[17] = {
    {PV_TOKEN, "PV_TOKEN"},
    {PT_TOKEN, "PT_TOKEN"},
    {PLUS_TOKEN, "PLUS_TOKEN"},
    {MOINS_TOKEN, "MOINS_TOKEN"},
    {MULT_TOKEN, "MULT_TOKEN"},
    {DIV_TOKEN, "DIV_TOKEN"},
    {VIR_TOKEN, "VIR_TOKEN"},
    {AFF_TOKEN, "AFF_TOKEN"},
    {EG_TOKEN, "EG_TOKEN"},
    {INF_TOKEN, "INF_TOKEN"},
    {INFEG_TOKEN, "INFEG_TOKEN"},
    {SUP_TOKEN, "SUP_TOKEN"},
    {SUPEG_TOKEN, "SUPEG_TOKEN"},
    {DIFF_TOKEN, "DIFF_TOKEN"},
    {PO_TOKEN, "PO_TOKEN"},
    {PF_TOKEN, "PF_TOKEN"},
    {FIN_TOKEN, "FIN_TOKEN"},
};

Maptoken key_words[11] = {
    {PROGRAM_TOKEN, "PROGRAM"},
    {CONST_TOKEN, "CONST"},
    {VAR_TOKEN, "VAR"},
    {BEGIN_TOKEN, "BEGIN"},
    {END_TOKEN, "END"},
    {IF_TOKEN, "IF"},
    {THEN_TOKEN, "THEN"},
    {WHILE_TOKEN, "WHILE"},
    {DO_TOKEN, "DO"},
    {READ_TOKEN, "READ"},
    {WRITE_TOKEN, "WRITE"},
};

//nombre total des token
int nbTokens = 0;
//caractere courant
char cour_char;
// notre fichier a complier
FILE *file;
//courant token
Maptoken Cour_Token;
//linked list(tokens table)
typedef struct node
{
    Maptoken info;
    struct node *next;
} node;
//the head of the linked list
node *head = NULL;
//functions
void read_char();
void read_string();
void read_number();
void read_symbole();
void tokenmap(int a);
void push();
void Analex();
void commentignore();
void display();
//____________
//partie syntaxique
//---------------------
