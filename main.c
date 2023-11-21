#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

// Estrutura para armazenar a data
typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

// Estrutura para armazenar a hora
typedef struct {
    int hora;
    int minuto;
} Hora;

// Estrutura para cada evento na agenda
typedef struct {
    Data data;
    Hora inicio;
    Hora fim;
    char descricao[51]; // 50 caracteres + terminador nulo
    char local[51]; // 50 caracteres + terminador nulo
} Evento;

// Funções de preenchimento, comparação, mostragem e remoção
void preencherEvento(Evento *evento);
void mostra_evento(void *info);
void mostra_eventos_data(Lista *lista, Data data);
void mostra_eventos_descricao(Lista *lista, const char *descricao);
void remove_eventos_data(Lista *lista, Data data);
void remove_evento_especifico(Lista *lista, Data data, Hora inicio);

int main() {
  
    Lista listaEventos;
    inicializa_lista(&listaEventos, sizeof(Evento));

    int escolha;
    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar novo evento\n");
        printf("2. Mostrar todos os eventos\n");
        printf("3. Mostrar eventos de uma data\n");
        printf("4. Mostrar eventos por descrição\n");
        printf("5. Remover evento por data ou data e hora\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                // Cadastrar novo evento
                Evento novoEvento;
                preencherEvento(&novoEvento);
                insere_ordem(&listaEventos, &novoEvento, compara_eventos);
                break;
            }
            case 2: {
                // Mostrar todos os eventos
                printf("\nEventos na agenda:\n");
                mostra_lista(listaEventos, mostra_evento);
                break;
            }
            case 3: {
                // Mostrar eventos de uma data
                Data dataBusca;
                printf("Digite a data para mostrar os eventos (DD MM AAAA): ");
                scanf("%d %d %d", &dataBusca.dia, &dataBusca.mes, &dataBusca.ano);
                printf("\nEventos na data especificada:\n");
                mostra_eventos_data(&listaEventos, dataBusca);
                break;
            }
            case 4: {
                // Mostrar eventos por descrição
                char descricaoBusca[51];
                printf("Digite a descrição para mostrar os eventos: ");
                scanf(" %[^\n]s", descricaoBusca);
                printf("\nEventos com a descrição especificada:\n");
                mostra_eventos_descricao(&listaEventos, descricaoBusca);
                break;
            }
            case 5: {
                // Remover evento por data ou data e hora
                int opcaoRemocao;
                printf("Escolha a opção de remoção:\n");
                printf("1. Remover todos os eventos de uma data\n");
                printf("2. Remover evento por data e horário de início\n");
                printf("Opção: ");
                scanf("%d", &opcaoRemocao);

                if (opcaoRemocao == 1) {
                    Data dataRemocao;
                    printf("Digite a data para remover os eventos (DD MM AAAA): ");
                    scanf("%d %d %d", &dataRemocao.dia, &dataRemocao.mes, &dataRemocao.ano);
                    remove_eventos_data(&listaEventos, dataRemocao);
                } else if (opcaoRemocao == 2) {
                    Data dataRemocao;
                    Hora horaRemocao;
                    printf("Digite a data para remover o evento (DD MM AAAA): ");
                    scanf("%d %d %d", &dataRemocao.dia, &dataRemocao.mes, &dataRemocao.ano);
                    printf("Digite o horário de início para remover o evento (HH MM): ");
                    scanf("%d %d", &horaRemocao.hora, &horaRemocao.minuto);
                    remove_evento_especifico(&listaEventos, dataRemocao, horaRemocao);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            }
            case 6: {
                printf("Encerrando o programa. Salvando e desalocando a lista...\n");
                // Implemente a lógica para salvar a lista no arquivo e desalocar a lista
                break;
            }
            default:
                printf("Opção inválida! Por favor, escolha uma opção válida.\n");
                break;
        }
    } while (escolha != 6);

    return 0;
}

void preencherEvento(Evento *evento) {
    printf("Digite a data do evento (DD MM AAAA): ");
    scanf("%d %d %d", &evento->data.dia, &evento->data.mes, &evento->data.ano);

    printf("Digite o horário de início do evento (HH MM): ");
    scanf("%d %d", &evento->inicio.hora, &evento->inicio.minuto);

    printf("Digite o horário de fim do evento (HH MM): ");
    scanf("%d %d", &evento->fim.hora, &evento->fim.minuto);

    printf("Digite a descrição do evento: ");
    scanf(" %[^\n]s", evento->descricao); // Lê uma linha de texto (com espaços)

    printf("Digite o local do evento: ");
    scanf(" %[^\n]s", evento->local); // Lê uma linha de texto (com espaços)
}

void mostra_evento(void *info) {
    Evento *evento = (Evento *)info;
    printf("Data: %02d/%02d/%04d\n", evento->data.dia, evento->data.mes, evento->data.ano);
    printf("Horário de início: %02d:%02d\n", evento->inicio.hora, evento->inicio.minuto);
    printf("Horário de fim: %02d:%02d\n", evento->fim.hora, evento->fim.minuto);
    printf("Descrição: %s\n", evento->descricao);
    printf("Local: %s\n", evento->local);
    printf("--------------------------------\n");
}

void mostra_eventos_data(Lista *lista, Data data) {
    Elemento *atual = lista->cabeca;
    int encontrou = 0;

    while (atual != NULL) {
        Evento *eventoAtual = (Evento *)atual->info;

        if (eventoAtual->data.ano == data.ano &&
            eventoAtual->data.mes == data.mes &&
            eventoAtual->data.dia == data.dia) {
            encontrou = 1;
            mostra_evento(eventoAtual); // Chama a função para mostrar o evento
        }

        atual = atual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado para a data especificada.\n");
    }
}

void mostra_eventos_descricao(Lista *lista, const char *descricao) {
    Elemento *atual = lista->cabeca;
    int encontrou = 0;

    while (atual != NULL) {
        Evento *eventoAtual = (Evento *)atual->info;

        if (strcmp(eventoAtual->descricao, descricao) == 0) {
            encontrou = 1;
            mostra_evento(eventoAtual); // Chama a função para mostrar o evento
        }

        atual = atual->proximo;
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado para a descrição especificada.\n");
    }
}

void remove_eventos_data(Lista *lista, Data data) {
    Elemento *atual = lista->cabeca;
    Elemento *anterior = NULL;
    int encontrou = 0;

    while (atual != NULL) {
        Evento *eventoAtual = (Evento *)atual->info;

        if (eventoAtual->data.ano == data.ano &&
            eventoAtual->data.mes == data.mes &&
            eventoAtual->data.dia == data.dia) {
            encontrou = 1;

            if (anterior == NULL) {
                lista->cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            Elemento *temp = atual;
            atual = atual->proximo;
            free(temp->info);
            free(temp);
            lista->qtd--;
        } else {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado para a data especificada.\n");
    }
}

void remove_evento_especifico(Lista *lista, Data data, Hora inicio) {
    Elemento *atual = lista->cabeca;
    Elemento *anterior = NULL;
    int encontrou = 0;

    while (atual != NULL) {
        Evento *eventoAtual = (Evento *)atual->info;

        if (eventoAtual->data.ano == data.ano &&
            eventoAtual->data.mes == data.mes &&
            eventoAtual->data.dia == data.dia &&
            eventoAtual->inicio.hora == inicio.hora &&
            eventoAtual->inicio.minuto == inicio.minuto) {
            encontrou = 1;

            if (anterior == NULL) {
                lista->cabeca = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            Elemento *temp = atual;
            atual = atual->proximo;
            free(temp->info);
            free(temp);
            lista->qtd--;
            break;
        } else {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    if (!encontrou) {
        printf("Nenhum evento encontrado para a data e horário de início especificados.\n");
    }
}
