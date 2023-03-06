#ifndef GENERIC_TYPE_H
#define GENERIC_TYPE_H

#include "../ParticuleEngine/ParticuleEngine.h"

#include <stdio.h>
#include <stdlib.h>
#include <List.h>

enum TypeVariable
{
    TYPE_VARIABLE_INT,
    TYPE_VARIABLE_FLOAT,
    TYPE_VARIABLE_STRING,
    TYPE_VARIABLE_CHAR,
    TYPE_VARIABLE_BOOL,
    TYPE_VARIABLE_LIST,
    TYPE_VARIABLE_GENERIC,
    TYPE_VARIABLE_UNKNOWN
};


typedef struct GenericType
{
    void *data;
    enum TypeVariable type;
    char *name;
    unsigned int size;
} GenericType;

GenericType *GenericTypeInt(int data, char *name);
GenericType *GenericTypeFloat(float data, char *name);
GenericType *GenericTypeString(char *data, char *name);
GenericType *GenericTypeChar(char data, char *name);
GenericType *GenericTypeBool(bool data, char *name);
GenericType *GenericTypeList(List* data, char *name);
GenericType *GenericTypeGeneric(void *data, char *name);
GenericType *GenericTypeUnknown(char *name);

void GenericTypeFree(GenericType *genericType);

int GenericTypeGetInt(GenericType *genericType);
float GenericTypeGetFloat(GenericType *genericType);
char *GenericTypeGetString(GenericType *genericType);
char GenericTypeGetChar(GenericType *genericType);
bool GenericTypeGetBool(GenericType *genericType);
List* GenericTypeGetList(GenericType *genericType);
void *GenericTypeGetGeneric(GenericType *genericType);

bool GenericTypeIsEqual(GenericType *genericType1, GenericType *genericType2);

void GenericTypeSet(GenericType *genericType, void *data);


#endif