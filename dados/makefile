#=============================================================
#* UNIFAL = Universidade Federal de Alfenas .
#* BACHARELADO EM CIENCIA DA COMPUTACAO.
#* Trabalho . . : Imagem de dados
#* Disciplina : Processamento de Imagens
#* Professor . : Luiz Eduardo da Silva
#* Aluno . . . . . : Gabriel Pereira Soares
#* Data . . . . . . : 08/07/2022
#*=============================================================

CC=gcc
#CCFLAGS=-Wall
CCFLAGS=-g
LDFLAGS=-lm
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=dados

all: $(TARGET)

$(TARGET): $(OBJECTS);\
    $(CC) -g -o $@ $^ $(LDFLAGS) 

%.o: %.c %.h;\
    $(CC) $(CCFLAGS) -c $<

%.o: %.c;\
    $(CC) $(CCFLAGS) -c $<

clean:;\
    rm -f *.o *-result.p*m $(TARGET);\