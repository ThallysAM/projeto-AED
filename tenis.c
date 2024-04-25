#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tenis.h"

struct UsuarioNode {
    Usuario usuario;
    struct UsuarioNode *prox;
} UsuarioNode;

struct {
    UsuarioNode *inicio;
    int tamanho;
} ListaUsuario;

struct TenisNode {
    Tenis tenis;
    struct TenisNode *prox;
} TenisNode;

struct {
    TenisNode *inicio;
    int tamanho;
} ListaTenis;

int loginValido(const char *usuario, const char *senha) {
    FILE *file = fopen("Usuarios.b", "rb");
    Usuario temp;

    while (fread(&temp, sizeof(Usuario), 1, file)) {
        if (strcmp(temp.id, usuario) == 0 && strcmp(temp.senha, senha) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void boasVindas(const char *usuario) {
    printf("\nBem-vindo a ALL IMPORTS, %s!\n", usuario);
}
void listarTenis(ListaTenis *listaTenis) {
    TenisNode *atual = listaTenis->inicio;

    if (atual == NULL) {
        printf("Nenhum tenis disponivel.\n");
        return;
    }

    printf("Lista de Tenis Disponiveis:\n");
    while (atual != NULL) {
        printf("Código: %d, Nome: %s, Preço: R$ %.2f, Estoque: %d\n", atual->tenis.codigo, atual->tenis.nome, atual->tenis.preco, atual->tenis.estoque);
        atual = atual->prox;
    }
}
void buscarTenisPorCodigo(int codigo) {
    FILE *file = fopen("Tenis.b", "rb");
    Tenis temp;
    int encontrado = 0;

    while (fread(&temp, sizeof(Tenis), 1, file)) {
        if (temp.codigo == codigo) {
            printf("Codigo: %d, Nome: %s, Preço: R$ %.2f, Estoque: %d\n", temp.codigo, temp.nome, temp.preco, temp.estoque);
            encontrado = 1;
            break;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Tenis com codigo %d nao encontrado.\n", codigo);
    }
}

void buscarTenisPorNome(const char *nome) {
    FILE *file = fopen("Tenis.b", "rb");
    Tenis temp;
    int encontrado = 0;

    while (fread(&temp, sizeof(Tenis), 1, file)) {
        if (strcmp(temp.nome, nome) == 0) {
            printf("Codigo: %d, Nome: %s, Preço: R$ %.2f, Estoque: %d, Marca: %s\n", temp.codigo, temp.nome, temp.preco, temp.estoque, temp.marca);
            encontrado = 1;
        }
    }

    fclose(file);

    if (!encontrado) {
        printf("Tenis com nome '%s' nao encontrado.\n", nome);
    }
}
void cadastrarTenis(ListaTenis *listaTenis, Tenis t) {
    TenisNode *novoNo = (TenisNode *)malloc(sizeof(TenisNode));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para novo tênis.\n");
        return;
    }

    novoNo->tenis = t;
    novoNo->prox = listaTenis->inicio;
    listaTenis->inicio = novoNo;
    listaTenis->tamanho++;
}
void tenisComMenorPreco() {
    FILE *file = fopen("Tenis.b", "rb");
    Tenis temp, menorPreco;
    int primeiro = 1;

    if (!file) {
        printf("Nenhum tenis disponível.\n");
        return;
    }

    while (fread(&temp, sizeof(Tenis), 1, file)) {
        if (primeiro || temp.preco < menorPreco.preco) {
            menorPreco = temp;
            primeiro = 0;
        }
    }

    fclose(file);

    if (!primeiro) {
        printf("Tenis com menor preço: Codigo: %d, Nome: %s, Preço: R$ %.2f, Estoque: %d\n", menorPreco.codigo, menorPreco.nome, menorPreco.preco, menorPreco.estoque);
    } else {
        printf("Nenhum tenis disponível.\n");
    }
}
void cadastrarUsuario(ListaUsuario *listaUsuarios, Usuario u) {
    UsuarioNode *novoNo = (UsuarioNode *)malloc(sizeof(UsuarioNode));
    if (novoNo == NULL) {
        printf("Erro ao alocar memória para novo usuário.\n");
        return;
    }

    novoNo->usuario = u;
    novoNo->prox = listaUsuarios->inicio;
    listaUsuarios->inicio = novoNo;
    listaUsuarios->tamanho++;
}
void excluirTenis(ListaTenis *listaTenis, int codigo) {
    TenisNode *atual = listaTenis->inicio;
    TenisNode *anterior = NULL;

    while (atual != NULL) {
        if (atual->tenis.codigo == codigo) {
            if (anterior == NULL) {
                listaTenis->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            listaTenis->tamanho--;
            printf("Tênis com código %d excluído com sucesso.\n", codigo);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Tênis com código %d não encontrado.\n", codigo);
}
void editarTenis(ListaTenis *listaTenis, int codigo, Tenis novoTenis) {
    TenisNode *atual = listaTenis->inicio;

    while (atual != NULL) {
        if (atual->tenis.codigo == codigo) {
            atual->tenis = novoTenis;
            printf("Tênis com código %d editado com sucesso.\n", codigo);
            return;
        }
        atual = atual->prox;
    }

    printf("Tênis com código %d não encontrado.\n", codigo);
}
void excluirUsuario(ListaUsuario *listaUsuarios, const char *id) {
    UsuarioNode *atual = listaUsuarios->inicio;
    UsuarioNode *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->usuario.id, id) == 0) {
            if (anterior == NULL) {
                listaUsuarios->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            listaUsuarios->tamanho--;
            printf("Usuário '%s' excluído com sucesso.\n", id);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Usuário '%s' não encontrado.\n", id);
}
void alterarSenha(const char *usuario, const char *novaSenha) {
    FILE *file = fopen("Usuarios.b", "rb+");
    Usuario temp;

    if (!file) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    while (fread(&temp, sizeof(Usuario), 1, file)) {
        if (strcmp(temp.id, usuario) == 0) {
            strcpy(temp.senha, novaSenha);
            fseek(file, -sizeof(Usuario), SEEK_CUR);
            fwrite(&temp, sizeof(Usuario), 1, file);
            fclose(file);
            printf("Senha alterada com sucesso para o usuário '%s'.\n", usuario);
            return;
        }
    }

    fclose(file);
    printf("Usuário '%s' não encontrado.\n", usuario);
}
