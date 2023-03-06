#include "GenericType.h"


GenericType *GenericTypeInt(int data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = (int*)malloc(sizeof(int));
    *(int*)genericType->data = data;
    genericType->type = TYPE_VARIABLE_INT;
    genericType->name = name;
    genericType->size = sizeof(int);
    return genericType;
}
GenericType *GenericTypeFloat(float data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = (float*)malloc(sizeof(float));
    *(float*)genericType->data = data;
    genericType->type = TYPE_VARIABLE_FLOAT;
    genericType->name = name;
    genericType->size = sizeof(float);
    return genericType;
}
GenericType *GenericTypeString(char *data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    int length = strlen(data);
    genericType->data = (char*)malloc(sizeof(char) * (length+1));
    strcpy((char*)genericType->data, data);
    ((char*)genericType->data)[length] = '\0';
    genericType->type = TYPE_VARIABLE_STRING;
    genericType->name = name;
    genericType->size = sizeof(char) * (length+1);
    return genericType;
}
GenericType *GenericTypeChar(char data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = (char*)malloc(sizeof(char));
    *(char*)genericType->data = data;
    genericType->type = TYPE_VARIABLE_CHAR;
    genericType->name = name;
    genericType->size = sizeof(char);
    return genericType;
}
GenericType *GenericTypeBool(bool data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = (bool*)malloc(sizeof(bool));
    *(bool*)genericType->data = data;
    genericType->type = TYPE_VARIABLE_BOOL;
    genericType->name = name;
    genericType->size = sizeof(bool);
    return genericType;
}
GenericType *GenericTypeList(List* data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = List_new();
    *(List*)genericType->data = *data;
    genericType->type = TYPE_VARIABLE_LIST;
    genericType->name = name;
    genericType->size = sizeof(List);
    return genericType;
}

GenericType *GenericTypeGeneric(void *data, char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = data;
    genericType->type = TYPE_VARIABLE_GENERIC;
    genericType->name = name;
    genericType->size = 0;
    return genericType;
}

GenericType *GenericTypeUnknown(char *name)
{
    GenericType *genericType = (GenericType*)malloc(sizeof(GenericType));
    genericType->data = NULL;
    genericType->type = TYPE_VARIABLE_UNKNOWN;
    genericType->name = name;
    genericType->size = sizeof(void*);
    return genericType;
}

void GenericTypeFree(GenericType *genericType)
{
    switch(genericType->type)
    {
        case TYPE_VARIABLE_INT:
            free((int*)genericType->data);
            break;
        case TYPE_VARIABLE_FLOAT:
            free((float*)genericType->data);
            break;
        case TYPE_VARIABLE_STRING:
            free((char*)genericType->data);
            break;
        case TYPE_VARIABLE_CHAR:
            free((char*)genericType->data);
            break;
        case TYPE_VARIABLE_BOOL:
            free((bool*)genericType->data);
            break;
        case TYPE_VARIABLE_LIST:
            List_free((List*)genericType->data);
            break;
        case TYPE_VARIABLE_GENERIC:
            break;
        case TYPE_VARIABLE_UNKNOWN:
            break;
    }
    free(genericType);
}

int GenericTypeGetInt(GenericType *genericType)
{
    return *(int*)genericType->data;
}
float GenericTypeGetFloat(GenericType *genericType)
{
    return *(float*)genericType->data;
}
char *GenericTypeGetString(GenericType *genericType)
{
    return (char*)genericType->data;
}
char GenericTypeGetChar(GenericType *genericType)
{
    return *(char*)genericType->data;
}
bool GenericTypeGetBool(GenericType *genericType)
{
    return *(bool*)genericType->data;
}
List* GenericTypeGetList(GenericType *genericType)
{
    return (List*)genericType->data;
}

void *GenericTypeGetGeneric(GenericType *genericType)
{
    return genericType->data;
}

bool GenericTypeIsEqual(GenericType *genericType1, GenericType *genericType2)
{
    if(genericType1->type != genericType2->type)
        return false;
    switch(genericType1->type)
    {
        case TYPE_VARIABLE_INT:
            return GenericTypeGetInt(genericType1) == GenericTypeGetInt(genericType2);
        case TYPE_VARIABLE_FLOAT:
            return GenericTypeGetFloat(genericType1) == GenericTypeGetFloat(genericType2);
        case TYPE_VARIABLE_STRING:
            return strcmp(GenericTypeGetString(genericType1), GenericTypeGetString(genericType2)) == 0;
        case TYPE_VARIABLE_CHAR:
            return GenericTypeGetChar(genericType1) == GenericTypeGetChar(genericType2);
        case TYPE_VARIABLE_BOOL:
            return GenericTypeGetBool(genericType1) == GenericTypeGetBool(genericType2);
        case TYPE_VARIABLE_LIST:
            return GenericTypeGetList(genericType1)==GenericTypeGetList(genericType2);
        case TYPE_VARIABLE_GENERIC:
            return GenericTypeGetGeneric(genericType1) == GenericTypeGetGeneric(genericType2);
        case TYPE_VARIABLE_UNKNOWN:
            return true;
    }
    return false;
}

void GenericTypeSet(GenericType *genericType, void *data)
{
    switch(genericType->type)
    {
        case TYPE_VARIABLE_INT:
            *(int*)genericType->data = *(int*)data;
            break;
        case TYPE_VARIABLE_FLOAT:
            *(float*)genericType->data = *(float*)data;
            break;
        case TYPE_VARIABLE_STRING:
            free((char*)genericType->data);
            int length = strlen((char*)data);
            genericType->data = (char*)malloc(sizeof(char) * (length+1));
            strcpy((char*)genericType->data, (char*)data);
            ((char*)genericType->data)[length] = '\0';
            break;
        case TYPE_VARIABLE_CHAR:
            *(char*)genericType->data = *(char*)data;
            break;
        case TYPE_VARIABLE_BOOL:
            *(bool*)genericType->data = *(bool*)data;
            break;
        case TYPE_VARIABLE_LIST:
            *(List*)genericType->data = *(List*)data;
            break;
        case TYPE_VARIABLE_GENERIC:
            genericType->data = data;
            break;
        case TYPE_VARIABLE_UNKNOWN:
            break;
    }
}