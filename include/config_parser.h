#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#define MAX_VALUE_STR_SIZE 512
#define MAX_SECTION_NAME_SIZE 512
#define  MAX_VARIABLE_NAME_SIZE 512

typedef struct  values_list_struct {
	char valueString[MAX_VALUE_STR_SIZE];
	struct values_vector_struct *next;
} values_list;

typedef struct config_struct {
	char sectionName[MAX_SECTION_NAME_SIZE];
	char variableName[MAX_VARIABLE_NAME_SIZE];
	values_list *variableValues;
	struct config_struct *next;
} config;

config* ReadConfg(char *file_path);
values_list* ParseValuesString(char *values_string);
values_list* GetConfigValues(confg *config_ptr, char *section_name, char *variable_name);
#endif
