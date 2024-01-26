#include "config_parser.h"
#include <string.h>
#include <stdio.h>

values_list* GetConfigValues(config *config_ptr, char *section_name, char *variable_name) {
	for(config *current = config_ptr; current != NULL; current = current->next) {
		if(strcmp(current->sectionName,section_name) == 0 && strcmp(current->variableName,variable_name) == 0){
			return current->variableValues;		
		}
	}
	printf("Не найденна секция %s или переменная %s",section_name,variable_name);
	return NULL;
}