# Config parser
## Сборка
```
make config_parser
```
## Пример
```С
#include "config_parser.h"
#include <stdio.h>

int main(int argc, char **argv) {
	if(argc < 4) {
		puts("./example file_path [section_name] variable_name");
		return 1;
	}

	//Чтение и парсинг файла конфигурации
	config *cfg = ReadConfig(argv[1]);

	//Получение списка значений по названию секции и названию переменной
	//Второй аргумент "[название секции]"
	//Третий аргумент "название переменной"
	values_list *vl = GetConfigValues(cfg, argv[2], argv[3]);
	
	//Вывод значений
	int i = 0;
	for(values_list *v = vl; v != NULL; v = v->next){
		printf("Значение%d %s\n", i, v->valueString);
		i++;
	}
	return 0;
}
```
### Сборка примера
```
make example
```
### Использование программы примера
```
./example file_path [section_name] variable_name
```