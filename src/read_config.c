#include "config_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

config* ReadConfig(char *file_path) {

	FILE configFile = open(filr_path, "r");
	config *begin = NULL, *current = NULL;

	if(configFile == NULL) {
		perror("Не удалось открыть файл конфигурации");
		exit(1);
	}

	char *sectionName = NULL;

	while(feof(configFile) == 0) {
		char buffer[MAX_STR_SIZE];
		if(fgets(buffer, MAX_STR_SIZE, configFile) == NULL && ferror(configFile) != 0) {
			perror("Ошибка чтения файла конфигурации");
			exit(2);
		}

		int buffer_length = strlen(buffer);
		int offset = 0;

		while(offset < buffer_length && strchr(" \t",buffer[offset]) != NULL) {
			offset++;
		}

		if(offset == buffer_length) continue;

		if(offset > 0) {

			for(int i = 0; i < buffer_length; i++) {
				buffer[i] = buffer[i + offset];
			}
		}

		buffer[buffer_length - offset] = '\0';

		if(strchr("#!~;",buffer[0]) != NULL) continue;

		char *line = strtok(buffer,"~;=");

		if(line == NULL){
			perror("strtok 1 is null");
			exit(3);
		}

		if(line[0] == '['){
			free(sectionName);
			sectionName = strdup(line);
		}
		else{

			if(begin == NULL) {
				current = begin = (config*)calloc(1,sizeof(config));
			}

			if(current == NULL) {
				perror("Не удалось выделить память");
				exit(4);
			}

			strcpy(current->sectionName,sectionName);
			strcpy(current->variableName,line);

			char *varValuesLine = strtok(NULL,"~;");

			if(varValuesLine == NULL) {
				perror("strtok 2 is null");
				exit(5);
			}

			varValuesLine = strdup(varValuesLine);
			values_list *vl_begin = NULL;

			for(char *varValue = strtok(varValuesLine,":"), values_list *vl = vl_begin = (values_list*)calloc(1,sizeof(values_list)); 
				  varValue == NULL; 
				  varValue = strtok(NULL,":"), vl = vl->next = (values_list*)calloc(1,sizeof(values_list)) {

				if(vl == NULL) {
					perror("Не удалось выделить память под элемент листа");
					exit(6);
				}

				strcpy(vl->valueString,varValue);
			}

			current->variableValues = vl_begin;

			current = current->next = (config*)calloc(1,sizeof(config));
		}
	}
}
