#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tenis.h"

void menuPrincipal() {
    printf("\nALL IMPORTS\n");
    printf("\nMenu Principal:\n");
    printf("1. Login\n");
    printf("2. Cadastrar novo usuario\n");
    printf("3. Listar tenis disponiveis\n");
    printf("4. Buscar tenis por codigo\n");
    printf("5. Buscar tenis por nome\n");
    printf("6. Cadastrar novo tenis\n");
    printf("7. Mostrar tenis com menor preço\n");
    printf("8. Excluir tênis\n");
    printf("9. Editar tênis\n");
    printf("10. Excluir usuário\n");
    printf("11. Alterar senha\n");
    printf("12. Logout\n");
    printf("0. Sair\n");
    printf("\nEscolha uma opcao: ");
}

int main() {
    ListaUsuario listaUsuarios = { .inicio = NULL, .tamanho = 0 };
    ListaTenis listaTenis = { .inicio = NULL, .tamanho = 0 };
    int opcao;
    char usuario[50], senha[50];
    do {
        menuPrincipal();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nInforme o seu ID:\n");
                scanf("%s", usuario);
                printf("\nInforme a senha:\n");
                scanf("%s", senha);

                if (loginValido(usuario, senha)) {
                    boasVindas(usuario);
                } else {
                    printf("Usuario ou senha invalidos.\n");
                }
                break;
            case 2: {
                Usuario novoUsuario;
                printf("\nInforme o ID do novo usuário: ");
                scanf("%s", novoUsuario.id);
                printf("Informe a senha do novo usuário: ");
                scanf("%s", novoUsuario.senha);

                do {
                    printf("Informe o email do novo usuário: ");
                    scanf("%s", novoUsuario.email);
                    if (strlen(novoUsuario.email) > 80 || !strstr(novoUsuario.email, "@")) {
                        printf("Email inválido. O email deve conter '@' e ter no máximo 80 caracteres.\n");
                    }
                } while (strlen(novoUsuario.email) > 80 || !strstr(novoUsuario.email, "@"));

                cadastrarUsuario(&listaUsuarios, novoUsuario);
                break;
            }
            case 3:
    			listarTenis(&listaTenis);
   				 break;
            case 4:
                printf("\nInforme o codigo do tenis que deseja buscar: ");
                int codigo;
                scanf("%d", &codigo);
                buscarTenisPorCodigo(codigo);
                break;
            case 5:
                printf("\nInforme o nome do tenis que deseja buscar: ");
                char nome[50];
                scanf("%s", nome);
                buscarTenisPorNome(nome);
                break;
            case 6: {
                Tenis novoTenis;
                printf("\nInforme o código do novo tênis: ");
                scanf("%d", &novoTenis.codigo);
                printf("Informe o nome do novo tênis: ");
                scanf("%s", novoTenis.nome);
                printf("Informe o preço do novo tênis: ");
                scanf("%f", &novoTenis.preco);
                printf("Informe o estoque do novo tênis: ");
                scanf("%d", &novoTenis.estoque);
                printf("Informe a marca do novo tênis: ");
                scanf("%s", novoTenis.marca);

                cadastrarTenis(&listaTenis, novoTenis);
                break;
            }
            case 7:
                tenisComMenorPreco();
                break;
            case 8:
                printf("\nInforme o codigo do tenis que deseja excluir: ");
                scanf("%d", &codigo);
                excluirTenis(&listaTenis, codigo);
                break;
            case 9:
    			printf("\nInforme o codigo do tenis que deseja editar: ");
    			scanf("%d", &codigo);
    			Tenis novoTenis;
			    printf("Informe o novo nome do tenis: ");
			    scanf("%s", novoTenis.nome);
			    printf("Informe o novo preço do tenis: ");
			    scanf("%f", &novoTenis.preco);
			    printf("Informe o novo estoque do tenis: ");
			    scanf("%d", &novoTenis.estoque);
			    printf("Informe a nova marca do tenis: ");
			    scanf("%s", novoTenis.marca);
			    editarTenis(&listaTenis, codigo, novoTenis);
			    break;
            case 10:
                printf("\nInforme o ID do usuário que deseja excluir: ");
                scanf("%s", usuario);
                excluirUsuario(&listaUsuarios, usuario);
                break;
            case 11:
                printf("\nInforme o seu ID:\n");
                scanf("%s", usuario);
                printf("\nInforme a nova senha:\n");
                scanf("%s", senha);
                alterarSenha(usuario, senha);
                break;
            case 12:
                printf("\nLogout realizado com sucesso.\n");
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
