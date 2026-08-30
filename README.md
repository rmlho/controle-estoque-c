# CRUD - Sistema de Estoque em C

Sistema de estoque usando linguagem C para armazenar, atualizar, consultar e remover itens.

---
## Funcionalidades

- Cadastro, alteração e exclusão de produtos
- Registro de entrada e saída de estoque
- Consultas por código, nome, categoria e situação
- Ordenação por nome, quantidade e valor
- 11 relatórios (geral, por categoria, produtos abaixo do mínimo, etc)
- Persistência de dados em arquivo

---
## Conceitos aplicados

- Structs e manipulação de vetores
- Ponteiros (passagem por referência)
- Validação de dados
- Algoritmos de ordenação (bubble sort)
- Manipulação de arquivos (persistência)

---
![Demonstração do sistema](caminho/para/seu.gif)
---
## Dependências

| Biblioteca | Usada para                                                                               |
| ---------- | ---------------------------------------------------------------------------------------- |
| `stdio.h`  | Entrada/saída (printf, scanf) e manipulação de arquivos (fopen, fprintf, fscanf, fclose) |
| `stdlib.h` | Funções utilitárias gerais (ex: exit)                                                    |
| `string.h` | Manipulação de strings (strcpy, strcmp, strlen)                                          |
| `ctype.h`  | Classificação/verificação de caracteres                                                  |

---
## Como compilar e rodar

### Requisitos:
- Compilador GCC (ou compatível)
- Testado em: Linux (Fedora)

**Linux/Mac:**
```bash
gcc main.c -o main
./main
```

**Windows (com GCC/MinGW instalado):**
```bash
gcc main.c -o main.exe
main.exe
```
---
## Desenvolvimento

Projeto acadêmico desenvolvido em equipe de 3 integrantes para a disciplina 
de Laboratório de Programação I, UEPB (2026.1).
