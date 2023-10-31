# Makefile para automatizar a compilação múltipla de arquivos-fonte e de forma recursiva
# ==================================================
# VARIÁVEIS DE COMPILAÇÃO
# ==================================================
# Nome do projeto
PROJ_NAME = main

# Sistema operacional: escolher "windows" ou "linux" ("sem aspas")
SO = linux

# Compilador
CC = gcc

# Coleção de Flags
CC_FLAGS = -c -W -Wall -ansi -pedantic -std=c99



# ==================================================
# VARIÁVEIS DE DIRETÓRIOS E DE ARQUIVOS
# ==================================================
# Coleção de arquivos .c
C_SOURCE = $(shell find ./source -type f -name "*.c")

# Coleção de arquivos .h
H_SOURCE = $(shell find ./source -type f -name "*.h")

# Coleção de arquivos .o
OBJ = $(patsubst ./source/%.c, ./objects/%.o, $(C_SOURCE))

# Lista de diretórios da pasta source
SOURCE_DIRS := $(shell find ./source -type d)

# Lista de diretórios da pasta objects
OBJ_DIRS = $(patsubst ./source%, ./objects%, $(SOURCE_DIRS))
$(foreach dir, $(OBJ_DIRS), $(shell mkdir -p $(dir)))



# ==================================================
# COMPILAÇÃO E LINKAGEM
# ==================================================
all: $(PROJ_NAME) clean

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

# PARA LIMPAR OS ARQUIVOS .o
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
