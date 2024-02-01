#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#define MAX_STR_SIZE 512
#define MAX_VALUE_STR_SIZE 512
#define MAX_SECTION_NAME_SIZE 512
#define  MAX_VARIABLE_NAME_SIZE 512

typedef struct  values_list_struct {
	char valueString[MAX_VALUE_STR_SIZE];
	struct values_list_struct *next;
} values_list;

typedef struct param_struct {
	char variableName[MAX_VARIABLE_NAME_SIZE];
	values_list *variableValues;
	struct param_struct *next;
} param;

typedef struct section_struct {
	char sectionName[MAX_SECTION_NAME_SIZE];
	param *params;
	struct section_struct *next;
} section;

section* ReadConfig(char *file_path);
values_list* GetConfigValues(section *config_ptr, char *section_name, char *variable_name);
#endif
