#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tp3.h"

void CriaVetor(Tabela *T){
    int i;
    T->dias = malloc(32 * sizeof(Evento));
    //Cria as celulas cabeca:
    for(i = 0; i < 32; i++)
        T->dias[i].prox = (Apontador)malloc(sizeof(Evento));
}



void TrataDadosEntrada(int op_idioma, int op_ano, int *qtdias_mes){
    // Checo se o ano e bissexto:
    if( (op_ano % 4 == 0 && op_ano % 100 != 0) || 
        (op_ano % 4 == 0 && op_ano % 100 == 0 && op_ano % 400 == 0) ){
            qtdias_mes[1] = 29;
    }
}



// https://www.youtube.com/watch?v=u7NAy_kDZ3A
int DiaSemana(int dia, int mes, int ano){
    int k, resultado;
    if(mes == 1){
        mes = 13;
        ano--;      
    } else if(mes == 2){
        mes = 14;
        ano--;
    }
    k = dia + (2 * mes) + (3*(mes + 1) / 5) + ano + (ano / 4) - (ano / 100) + (ano / 400) + 2;
    resultado = k % 7;
    return resultado;
}



void InsereTabela(Tabela *T, char evento, int dia, int mes, int ano, char *descr_evento){
    T->Primeiro = T->dias[dia].prox;
    T->Ultimo = T->Primeiro;
    while(T->Ultimo->prox != NULL)
        T->Ultimo = T->Ultimo->prox;
    // Criacao da Celula e insercao dos dados:
    T->Ultimo->prox= (Apontador)malloc(sizeof(Evento));
    T->Ultimo->evento = evento;
    T->Ultimo->dia = dia;
    T->Ultimo->mes = mes;
    T->Ultimo->ano = ano;
    strcpy(T->Ultimo->descr_evento, descr_evento);
}



void GuardaEventos(char *eventos){
    int n = 0, i = 0;
    printf("Digite quantos eventos deseja guardar[1 a 4]: ");
    scanf("%d", &n);
    printf("Digite os eventos que voce deseja guardar de maneira espacada(Ex: A O F): ");
    for(i = 0; i < n; i++)
        scanf(" %c", &eventos[i]);
    printf("Eventos digitados: ");
    for(i = 0; i < n; i++)
        printf("%c ", eventos[i]);
    printf("\n");
}



int TestaEvento(char *eventos, char evento){
    int i;
    for(i = 0; i < 5; i++){
        if(evento == eventos[i]){
            return 1;
            break;
        }
    }
    return 0;
}



void AbreArquivo(Tabela *T, char *nome_arq, char *eventos){
    FILE *p_arq;
    int dia, mes, ano;
    int resultado;
    char evento, descr[25];
    // Leitura dos eventos a serem guardados:
    GuardaEventos(eventos);
    // Abertura de arquivos:
    p_arq = fopen(nome_arq, "r+");
    //Arquivo nao encontrado:
    if(p_arq == NULL){
        printf("Arquivo nao encontrado. \n");
        exit(1);
    }
    //Arquivo encontrado:
    else{
        while(!feof(p_arq)){
            fscanf(p_arq, "%c %d %d %d", &evento, &dia, &mes, &ano);
            if(fgets(descr, 40, p_arq) != NULL){
                // Checo se o evento da linha do arquivo esta entre os que quero guardar:
                resultado = TestaEvento(eventos, evento);
                if(resultado == 1)
                    InsereTabela(T, evento, dia, mes, ano, descr);
            }}}
}



// Funcao auxiliar para imprimir o arquivo de eventos. Para utiliza-la, basta descomentar a linha 23 do arquivo main.
void ImprimeArquivo(Tabela *T){
    Apontador aux;
    int i;
    printf("Comecou a imprimir: \n");
    for(i = 0; i < 32; i++){
        T->Primeiro = T->dias[i].prox;
        T->Ultimo = T->Primeiro;
        while(T->Ultimo->prox != NULL){
            printf("%c %d %d %d %s", T->Ultimo->evento, T->Ultimo->dia, T->Ultimo->mes, T->Ultimo->ano, T->Ultimo->descr_evento);
            T->Ultimo = T->Ultimo->prox;
        }
    }
    printf("\n");
}



void ProcuraEvento(Tabela *T, int dia, int mes, int ano){
    Apontador aux1, aux2;   
    // Procura na lista encadeada os eventos salvos com o dia correspondente:
    aux1 = T->dias[dia].prox;
    while(aux1->prox != NULL){
        // Nenhum zero:
        if(aux1->mes == mes && aux1->ano == ano){
            if(aux1->evento == 'O')
                printf("\t%s", aux1->descr_evento);
            else
                printf("\t%c %s", aux1->evento, aux1->descr_evento);
        }
        // Datas com ano igual a zero:
        else if(aux1->mes == mes && aux1->ano == 0){
            if(aux1->evento == 'O')
                printf("\t%s", aux1->descr_evento);
            else
                printf("\t%c %s", aux1->evento, aux1->descr_evento);
        }
        // Datas com mes igual a zero:
        else if(aux1->mes == 0 && aux1->ano == ano){
            if(aux1->evento == 'O')
                printf("\t%s", aux1->descr_evento);
            else
                printf("\t%c %s", aux1->evento, aux1->descr_evento);
        }
        aux1 = aux1->prox;
    }
    // Procura na lista encadeada os eventos salvos com dia zero:
    aux2 = T->dias[0].prox;
    while(aux2->prox != NULL){
        if(aux2->mes == mes && aux2->ano == ano){
            if(aux2->evento == 'O')
                printf("\t%s", aux2->descr_evento);
            else
                printf("\t%c %s", aux2->evento, aux2->descr_evento);
        }
        aux2 = aux2->prox;
    }
}



void Atribui(Apontador a, Apontador b){
    //rintf("A: %c B: %c", a->evento, b->evento);
    a->evento = b->evento;
    a->dia = b->dia;
    a->mes = b->mes;
    a->ano = b->ano;
    strcpy(a->descr_evento, b->descr_evento);   
}



void Ordena(Tabela *O, int opcao){
    Apontador i;
    Apontador novo;
    Apontador aux1;
    // Ordenacao por Eventos:
    if(opcao == 1){
        novo = (Apontador)malloc(sizeof(Evento));
        i = O->Primeiro->prox;
        aux1 = i;
        while(i->prox != NULL){
            aux1 = i;
            Atribui(novo, aux1);    
            while(aux1->prox != NULL){
                if(aux1->evento < i->evento){
                    Atribui(novo, aux1);
                    Atribui(aux1, i);
                    Atribui(i, novo);
                }
                else if(aux1->evento == i->evento){
                    if(aux1->ano < i->ano){
                        Atribui(novo, aux1);
                        Atribui(aux1, i);
                        Atribui(i, novo);
                    }
                    else if(aux1->ano == i->ano){
                        if(aux1->mes < i->mes){
                            Atribui(novo, aux1);
                            Atribui(aux1, i);
                            Atribui(i, novo);
                        }
                        else if(aux1->mes == i->mes){
                            if(aux1->dia < i->dia){
                                Atribui(novo, aux1);
                                Atribui(aux1, i);
                                Atribui(i, novo);
                            }}}}  
                aux1 = aux1->prox;
            }
            i = i->prox;
        }} 
    // Ordenacao por Datas cronologicas:
    else if(opcao == 2){
        novo = (Apontador)malloc(sizeof(Evento));
        i = O->Primeiro->prox;
        aux1 = i;
        while(i->prox != NULL){
            aux1 = i;
            Atribui(novo, aux1);    
            while(aux1->prox != NULL){
                if(aux1->ano < i->ano){
                    Atribui(novo, aux1);
                    Atribui(aux1, i);
                    Atribui(i, novo);
                }
                else if(aux1->ano == i->ano){
                    if(aux1->mes < i->mes){
                        Atribui(novo, aux1);
                        Atribui(aux1, i);
                        Atribui(i, novo);
                    }
                    else if(aux1->mes == i->mes){
                        if(aux1->dia < i->dia){
                            Atribui(novo, aux1);
                            Atribui(aux1, i);
                            Atribui(i, novo);
                        }
                        else if(aux1->dia == i->dia){
                            if(aux1->evento < i->evento){
                                Atribui(novo, aux1);
                                Atribui(aux1, i);
                                Atribui(i, novo);
                            }}}}  
                aux1 = aux1->prox;
            }
            i = i->prox;
        }}
}



void ImprimeOrdena(Tabela *T, Tabela *O, int opcao){
    Apontador novo;
    Apontador aux;
    int i;
    // Testa opcao digitada:
    if(opcao != 1 && opcao != 2){
        printf("Opcao nao disponivel.\n");
        exit(1);
    }
    // Criacao da novo Lista encadeada:
    O->Primeiro = (Apontador)malloc(sizeof(Evento));
    O->Ultimo = O->Primeiro;
    O->Primeiro->prox = NULL; 
    // Ordena por eventos:
    for(i = 0; i < 32; i++){
        T->Primeiro = T->dias[i].prox;
        T->Ultimo = T->Primeiro;
        while(T->Ultimo->prox != NULL){
            novo = (Apontador)malloc(sizeof(Evento));
            novo->evento = T->Ultimo->evento;
            novo->dia = T->Ultimo->dia;
            novo->mes = T->Ultimo->mes;
            novo->ano = T->Ultimo->ano;
            strcpy(novo->descr_evento, T->Ultimo->descr_evento);
            O->Ultimo->prox = novo;
            O->Ultimo = O->Ultimo->prox;
            T->Ultimo = T->Ultimo->prox;      
        }
    }
    Ordena(O, opcao);
    aux = O->Primeiro->prox;
    while(aux->prox != NULL){
        printf("\t%c %d %d %d \t%s", aux->evento, aux->dia, aux->mes, aux->ano, aux->descr_evento);
        aux = aux->prox;
    }
    printf("\n");
}



void PesquisaArquivo(Tabela *T, int opcao){
    int i;
    char evento, evento2;
    int dia, mes, ano;
    if(opcao == 1){
        printf("Por favor, digite o tipo de evento buscado(A, F, V, O): ");
        scanf(" %c", &evento);
        printf("Evento digitado: %c\n\n", evento);
        for(i = 0; i < 32; i++){
            T->Primeiro = T->dias[i].prox;
            T->Ultimo = T->Primeiro;
            while(T->Ultimo->prox != NULL){
                if(evento == T->Ultimo->evento)
                    printf("\t%c %s", T->Ultimo->evento, T->Ultimo->descr_evento);
                T->Ultimo = T->Ultimo->prox;
            }
        }
        printf("\n");
    }
    else if(opcao == 2){
        printf("Por favor, digite a data buscada(dd/mm/aaaa): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        printf("Data digitada: %d/%d/%d\n\n", dia, mes, ano);
        ProcuraEvento(T, dia, mes, ano);
        printf("\n");
    }
    else{
        printf("Opcao nao disponivel.\n");
        exit(1);
    }
}