# MAKEFILE COM PADRÃO ORGANIZACIONAL

# VARIÁVEIS
# Nome do projeto
PROJ_NAME = main

# Sistema operacional: escolher "windows" ou "linux" ("sem aspas")
SO = linux

# Compilador
CC = gcc

# Coleção de arquivos .c
C_SOURCE = $(wildcard ./source/*.c)

# Coleção de arquivos .h
H_SOURCE = $(wildcard ./source/*.h)

# Coleção de arquivos .o
OBJ = $(patsubst ./source/%.c, ./objects/%.o, $(C_SOURCE))

# Coleção de Flags
CC_FLAGS = -c -W -Wall -ansi -pedantic -std=c99

# =====================
# COMPILAÇÃO E LINKAGEM
# =====================
all: objFolder $(PROJ_NAME) clean

$(PROJ_NAME): $(OBJ)
	@echo Fazendo o build do binario usando o GCC Linker: $@
	$(CC) $^ -o $@
	@echo _

./objects/%.o: ./source/%.c ./source/%.h
	@echo Fazendo o build do target usando o GCC Compiler em: $<
	$(CC) $< $(CC_FLAGS) -o $@
	@echo _

./objects/main.o: ./source/main.c $(H_SOURCE)
	@echo Fazendo o build do target usando o GCC Compiler em: $<
	$(CC) $< $(CC_FLAGS) -o $@
	@echo _

objFolder:
	@mkdir objects

clean:
ifeq ($(SO), windows)
	rd /s /q objects
	@echo _
else ifeq ($(SO), linux)
	rm -rf objects
	@echo _
else
	@echo ERRO. Sistema nao suportado: $(SO)
	@echo _
endif

.PHONY: all clean