# Concorda

Concorda é um sistema de mensagens em grupo que permite aos usuários criar servidores e canais para interagir com outros participantes. Os usuários podem trocar mensagens de texto e voz, criar servidores, convidar membros e muito mais.

## Funcionalidades

- Criação de usuário
- Login e logout
- Criação e remoção de servidores
- Configuração de descrição e código de convite para servidores
- Criação e remoção de canais de texto e voz
- Troca de mensagens de texto e voz em canais
- Listagem de servidores e participantes
- Entrada e saída de servidores

## Pré-requisitos

- C++11 ou superior
- CMake

## Como compilar


1. Clone o repositório para o seu ambiente local.
2. Certifique-se de ter o CMake instalado em seu sistema.
3. Navegue até o diretório raiz do projeto.
4. Execute os seguintes comandos:

cmake . -B build
cd build
make

## Como executar

Execute o seguinte comando no terminal para executar o programa: ./concordo

## Como usar

Ao iniciar o sistema Concorda, você será solicitado a criar um usuário ou fazer login caso já tenha uma conta.

### Comandos disponíveis

A seguir estão os comandos disponíveis no sistema:

- `create-user <email> <senha> <nome>`: Cria um novo usuário com o email, senha e nome fornecidos.
- `login <email> <senha>`: Realiza o login com o email e senha fornecidos.
- `quit`: Sai do sistema.
- `disconnect`: Desconecta o usuário atual.
- `create-server <nome>`: Cria um novo servidor com o nome fornecido.
- `set-server-desc <nome> "<descrição>"`: Define a descrição do servidor especificado.
- `set-server-invitecode <nome> <código>`: Define o código de convite do servidor especificado.
- `list-servers`: Lista os servidores disponíveis.
- `remove-server <nome>`: Remove o servidor especificado.
- `enter-server <nome>`: Entra no servidor especificado.
- `leave-server`: Sai do servidor atual.
- `list-participants`: Lista os participantes do servidor atual.

## Autore

- [ João Vitor Cafalange de Carvalho Lopes](https://github.com/Jcalafange)