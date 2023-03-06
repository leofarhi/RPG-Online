#include "Interpreter.h"

void Interpreter_skipBranch(ScriptManager* scriptManager, CodeLine *line){
    int indent = line->indent;
    while(line->node->next != NULL){
        line = line->node->next->data;
        if(line->indent <= indent){
            return;
        }
    }
}

int Interpreter_if(ScriptManager* scriptManager, CodeLine *line, List *parameters){
    return 0;
}
int Interpreter_else(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_while(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_for(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_function(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_return(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_break(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_continue(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}
int Interpreter_var(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}

int Interpreter_call(ScriptManager* scriptManager, CodeLine *line, List *parameters)
{
    return 0;
}

InterpreterToken interpreterTokens[MAX_TOKEN_SC];

void Interpreter_init()
{
    char *names[MAX_TOKEN_SC] = {
        "if",
        "else",
        "while",
        "for",
        "function",
        "return",
        "break",
        "continue",
        "var",
        "call"
    };
    int (*functions[MAX_TOKEN_SC])(ScriptManager* scriptManager, CodeLine *line, List *parameters) = {
        Interpreter_if,
        Interpreter_else,
        Interpreter_while,
        Interpreter_for,
        Interpreter_function,
        Interpreter_return,
        Interpreter_break,
        Interpreter_continue,
        Interpreter_var,
        Interpreter_call
    };
    for(int i = 0; i < MAX_TOKEN_SC; i++){
        interpreterTokens[i].name = names[i];
        interpreterTokens[i].token = i;
        interpreterTokens[i].function = functions[i];
    }
}

ScriptManager *ScriptManager_new()
{
    ScriptManager *manager = malloc(sizeof(ScriptManager));
    manager->scripts = List_new();
    manager->contexts = List_new();
    return manager;
}

void ScriptManager_free(ScriptManager *manager)
{
    while(manager->scripts->size > 0){
        Script *script = List_pop(manager->scripts);
        Script_free(script);
    }
    List_free(manager->scripts);
    while(manager->contexts->size > 0){
        ScriptContext *context = List_pop(manager->contexts);
        free(context);
    }
    List_free(manager->contexts);
    free(manager);
}

int ScriptManager_NextLine(ScriptManager *manager)
{
    ScriptContext *context = manager->contexts->tail->data;
    if (context->currentLine->next == NULL){
        return 0;// A changer car il faut depiler le contexte
    }
    context->currentLine = context->currentLine->next->data;
    return 1;
}

void ScriptManager_StartFunction(ScriptManager *manager, CodeLine* line, List *parameters)
{
    //TODO: Implement
}

Script *Script_new(char *name)
{
    Script *script = malloc(sizeof(Script));
    script->name = name;
    script->lines = List_new();
    script->localVariables = List_new();
    return script;
}
void Script_free(Script *script)
{
    while(script->lines->size > 0){
        CodeLine *line = List_pop(script->lines);
        CodeLine_free(line);
    }
    List_free(script->lines);
    while(script->localVariables->size > 0){
        GenericType *var = List_pop(script->localVariables);
        GenericTypeFree(var);
    }
    free(script);
}

void Script_addLine(Script *script, CodeLine *line)
{
    List_add(script->lines, line);
}
void Script_removeLine(Script *script, CodeLine *line)
{
    List_remove(script->lines, line);
}
void Script_addLineAt(Script *script, CodeLine *line, int index)
{
    List_insertAt(script->lines, index, line);
}

CodeLine *CodeLine_new(enum ScriptToken token, short indent)
{
    CodeLine *line = malloc(sizeof(CodeLine));
    line->token = token;
    line->indent = indent;
    line->parameters = List_new();
    return line;
}
void CodeLine_free(CodeLine *line)
{
    List_free(line->parameters);
    free(line);
}
void CodeLine_addParameter(CodeLine *line, GenericType *parameter)
{
    List_add(line->parameters, parameter);
}