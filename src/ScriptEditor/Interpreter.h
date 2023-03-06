#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "../ParticuleEngine/ParticuleEngine.h"
#include "../ParticuleEngine/Resources.h"
#include "../InterfaceSystem/InterfaceSystem.h"
#include "../InterfaceSystem/EventDataSystem.h"

#include <List.h>
#include "GenericType.h"

enum ScriptToken{
    TOKEN_SC_IF,
    TOKEN_SC_ELSE,
    TOKEN_SC_WHILE,
    TOKEN_SC_FOR,
    TOKEN_SC_FUNCTION,
    TOKEN_SC_RETURN,
    TOKEN_SC_BREAK,
    TOKEN_SC_CONTINUE,
    TOKEN_SC_VAR,
    TOKEN_SC_CALL,

    MAX_TOKEN_SC
}

typedef struct CodeLine CodeLine;
typedef struct ScriptManager ScriptManager;

typedef struct InterpreterToken{
    char *name;
    enum ScriptToken token;
    int (*function)(ScriptManager* scriptManager, CodeLine *line, List *parameters);
}InterpreterToken;

extern InterpreterToken interpreterTokens[MAX_TOKEN_SC];

void Interpreter_init();

typedef struct CodeLine{ // c'est une ligne de code dans un script
    List_node *node;// c'est le noeud de la liste de lignes de code qui contient cette ligne
    enum ScriptToken token;// c'est le token de la ligne de code
    short indent;// c'est l'indentation de la ligne de code
    List *parameters;// c'est la liste des parametres de la ligne de code
}CodeLine;

typedef struct Script{ // c'est un script contenant des lignes de code
    char *name;// c'est le nom du script
    List *lines;// c'est la liste des lignes de code
    List *localVariables;// c'est la liste des variables locales du script
}Script;

typedef struct ScriptContext{// c'est le deroulement d'une partie d'un script
    Script *script;// c'est le script en cours d'execution
    List_node *currentLine;// c'est la ligne de code en cours d'execution
}ScriptContext;

typedef struct ScriptManager{// c'est le deroulement d'un programme complet
    List *scripts;// c'est la liste des scripts
    List *contexts;// c'est la pile des scripts en cours d'execution
}ScriptManager;

ScriptManager *ScriptManager_new();

void ScriptManager_free(ScriptManager *manager);

int ScriptManager_NextLine(ScriptManager *manager);

void ScriptManager_StartFunction(ScriptManager *manager, CodeLine* line, List *parameters);

Script *Script_new(char *name);
void Script_free(Script *script);

void Script_addLine(Script *script, CodeLine *line);
void Script_removeLine(Script *script, CodeLine *line);
void Script_addLineAt(Script *script, CodeLine *line, int index);

CodeLine *CodeLine_new(enum ScriptToken token, short indent);
void CodeLine_free(CodeLine *line);
void CodeLine_addParameter(CodeLine *line, GenericType *parameter);

#endif