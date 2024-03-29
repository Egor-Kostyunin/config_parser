#include "config_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char trim(char *buffer){
	int buffer_length = strlen(buffer);
	int offset = 0;
	if(buffer_length == 0 || buffer[0] == '\n') return 0;

	while(offset < buffer_length && strchr(" \t",buffer[offset]) != NULL) {
		offset++;
	}

	if(offset == buffer_length) return 0;

	if(offset > 0) {

		for(int i = 0; i < buffer_length; i++) {
			buffer[i] = buffer[i + offset];
		}

	}

	buffer[buffer_length - offset] = '\0';

	return 1;
}

char rtrim(char *buffer){
	int offset = strlen(buffer)-1;
	if(offset == 0) return 0;

	while(offset > 0 && strchr(" \t\n",buffer[offset]) != NULL) {
		buffer[offset] = '\0';
		offset--;
	}

	if(offset == 0) return 0;

	return 1;
}

section* ReadConfig(char *file_path) {

	FILE *configFile = fopen(file_path, "r");
	section *begin = NULL, *current = NULL;
	param *pbegin = NULL;
	if(configFile == NULL) {
		perror("Не удалось открыть файл конфигурации");
		exit(1);
	}

	char *sectionName = NULL;

	while(feof(configFile) == 0) {
		char buffer[MAX_STR_SIZE];

		//Чтение строки
		if(fgets(buffer, MAX_STR_SIZE, configFile) == NULL && ferror(configFile) != 0) {
			perror("Ошибка чтения файла конфигурации");
			exit(2);
		}
		
		if(feof(configFile) != 0) return begin;

		if(!trim(buffer)) continue;
		
		if(strchr("#!~;",buffer[0]) != NULL) continue;

		char *line = strtok(buffer,"~;=");
		
		if(line == NULL){
			perror("strtok 1 is null");
			exit(3);
		}
		//Смена секции
		if(line[0] == '['){
			free(sectionName);
			//Чтение переменных секции 
			if(begin == NULL) {
				current = begin = (section*)calloc(1,sizeof(section));
			}
			else {
				current->params = pbegin;
				current = current->next = (section*)calloc(1,sizeof(section));			
			}
			if(current == NULL) {
				perror("Не удалось выделить память");
				exit(4);
			}
			sectionName = NULL;
			sectionName = strdup(line);
			if(sectionName == NULL){
				perror("sectionName is null");
				exit(3);
			}
	
			char *o = strchr(sectionName,'[');
			char *c = strchr(sectionName,']');
			if(o == NULL || c == NULL){
				perror("not sectionName");
				exit(3);
			}
			*o = ' ';
			*c = ' ';
			trim(sectionName);
			rtrim(sectionName);
			strcpy(current->sectionName,sectionName);
			rtrim(current->sectionName);
		}
		else{
			if(sectionName == NULL) {
				puts("Неожиданная переменная вне секции");
				return NULL;
			}
			
			
			if(current->params == NULL) {
				pbegin = current->params = (param*)calloc(1,sizeof(param));
			}
			if(current->params == NULL) {
				perror("Не удалось выделить память");
				exit(4);
			}
			
			strcpy(current->params->variableName,line);
			
			rtrim(current->params->variableName);

			char *varValuesLine = strtok(NULL,"~;");

			if(varValuesLine == NULL) {
				perror("strtok 2 is null");
				exit(5);
			}

			varValuesLine = strdup(varValuesLine);
			values_list *vl_begin = NULL;
			values_list *vl = NULL;

			for(char *varValue = strtok(varValuesLine,":"); 
				  varValue != NULL; 
				  varValue = strtok(NULL,":")) {
				if(vl_begin == NULL){
					vl = vl_begin = (values_list*)calloc(1,sizeof(values_list));
				}
				else{
					vl = vl->next = (values_list*)calloc(1,sizeof(values_list));
				}
				if(vl == NULL) {
					perror("Не удалось выделить память под элемент листа");
					exit(6);
				}
				trim(varValue);
				rtrim(varValue);
				strcpy(vl->valueString,varValue);
			}

			current->params->variableValues = vl_begin;

			current->params = current->params->next = (param*)calloc(1,sizeof(param));
			
			free(varValuesLine);
		}
	}
	return begin;
}
