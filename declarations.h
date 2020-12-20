#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define SIZE 10007
typedef enum
{
    ARRAY,
    STRING,
    RECORD
} np_type;
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
typedef struct
{
    Codes_LEX token;
    char identif[21];
    char value[21];
    int ligne;
    int colonne;
    int p_type;
    int np_type;
    int size;
    char r_value[100];
    bool isconst;
} Maptoken;

//--------
typedef struct
{
    Codes_LEX token;
    char message_erreur[100];

} Maptoken_erreur;

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

Maptoken_erreur maperror[35] = {
    {PROGRAM_TOKEN, "Error: un  'PROGRAM' est manquant "},
    {CONST_TOKEN, "Error :au niveau de la définition  des constantes "},
    {VAR_TOKEN, "Error :au niveau de la définition  des variables "},
    {BEGIN_TOKEN, "Error : un 'BEGIN'est  manquant  "},
    {END_TOKEN, "Error : un 'END' est  manquant"},
    {IF_TOKEN, "Error : un 'IF'est  manquant"},
    {THEN_TOKEN, "Error : un 'THEN'est  manquant"},
    {WHILE_TOKEN, "Error : un 'WHILE'est  manquant"},
    {DO_TOKEN, "Error : un 'DO'est  manquant"},
    {READ_TOKEN, "Error : erreur de lecture "},
    {WRITE_TOKEN, "Error : erreur d'écréture"},
    {PV_TOKEN, "Error : un ';'est  manquant"},
    {PT_TOKEN, "Error : un '.'est  manquant"},
    {PLUS_TOKEN, "Error :une opération mathématique ne peut etre efféctuer sans opérateur"},
    {MOINS_TOKEN, "Error :une opération mathématique ne peut etre efféctuer sans opérateur"},
    {MULT_TOKEN, "Error :une opération mathématique ne peut etre efféctuer sans opérateur"},
    {DIV_TOKEN, "Error :une opération mathématique ne peut etre efféctuer sans opérateur"},
    {VIR_TOKEN, "Error : un ','est  manquant"},
    {AFF_TOKEN, "Error : un ':='est  manquant"},
    {EG_TOKEN, "Error : un '='est  manquant"},
    {INF_TOKEN, "Error :une opération  booléenne ne peut etre efféctuer sans opérateur"},
    {INFEG_TOKEN, "Error :une opération  booléenne ne peut etre efféctuer sans opérateur"},
    {SUP_TOKEN, "Error :une opération  booléenne ne peut etre efféctuer sans opérateur"},
    {SUPEG_TOKEN, "Error :une opération  booléenne ne peut etre efféctuer sans opérateur"},
    {DIFF_TOKEN, "Error :une opération  booléenne ne peut etre efféctuer sans opérateur"},
    {PO_TOKEN, "Error : un '('est  manquant"},
    {PF_TOKEN, "Error : un ')'est  manquant"},
    {FIN_TOKEN, "Error :erreur"},
    {ERREUR_TOKEN, "Error : erreur de syntaxe"}};

//nombre total des token
int nbTokens = 0, ligne = 1, colonne = 1, indx;
//caractere courant
char cour_char;
// notre fichier a complier
FILE *file;
//courant token
Maptoken Cour_Token, Cour_symbole, prev_token;
//linked list(tokens table)
typedef struct node
{
    Maptoken info;
    struct node *next;
} node;
//the head of the linked list
node *head = NULL;

//-----
struct DataItem
{
    Maptoken data;
    int key;
    bool isset;
};
struct DataItem *hashArray[SIZE];
struct DataItem *dummyItem;
struct DataItem *item;
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
