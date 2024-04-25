#ifndef TENIS_H
#define TENIS_H

typedef struct Usuario usuario;
typedef struct Tenis tenis;
typedef struct UsuarioNode usuarionode;
typedef struct ListaUsuario listausuario;
typedef struct TenisNode tenisnode;
typedef struct ListaTenis lista tenis;

int loginValido(const char *usuario, const char *senha);
void boasVindas(const char *usuario);
void listarTenis(ListaTenis *listaTenis);
void buscarTenisPorCodigo(int codigo);
void buscarTenisPorNome(const char *nome); 
void cadastrarTenis(ListaTenis *listaTenis, Tenis t);
void tenisComMenorPreco();
void cadastrarUsuario(ListaUsuario *listaUsuarios, Usuario u);
void excluirTenis(ListaTenis *listaTenis, int codigo);
void editarTenis(ListaTenis *listaTenis, int codigo, Tenis novoTenis);
void excluirUsuario(ListaUsuario *listaUsuarios, const char *id);
void alterarSenha(const char *usuario, const char *novaSenha);

#endif
