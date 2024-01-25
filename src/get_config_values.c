#include "config_parser.h"
#include <string.h>

values_list* GetConfigValues(config *config_ptr, char *section_name, char *variable_name) {
	for(config *current = config_ptr; current != NULL; current = current->next) {
		if(strcmp(current->sectionName,section_name) == 0 && strcmp(current->variableName,variable_name) == 0){
			return current->variableValues;		
		}
	}
	return NULL;
}