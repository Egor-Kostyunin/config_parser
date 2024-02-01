#include "config_parser.h"
#include <string.h>
#include <stdio.h>

values_list* GetConfigValues(section *config_ptr, char *section_name, char *variable_name) {
	char flag = 0;	
	for(section *current = config_ptr; current != NULL; current = current->next) {
		if(strcmp(current->sectionName, section_name) == 0){
			flag = 1;
			for(param * p = current->params; p != NULL; p = p->next){
				if(strcmp(current->params->variableName, variable_name) == 0)
					return p->variableValues;	
			}
		}
	}
	if(flag){
		printf("Не найденна переменная %s\n",variable_name);
	}
	else {
		printf("Не найденна секция %s\n",section_name);
	}
	return NULL;
}