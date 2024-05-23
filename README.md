# Shell

## Requisitos:

### - Virtual Machine com Sistema Operacional Linux

### - Instalar o readline dentro da VM
Para instalar use esse código:
```sh
sudo apt-get install libreadline-dev
```

## Como Compilar:

### Compartilhe a pasta onde colocou o projeto com a VM
Comando para montar a pasta compartilhada (Troque PastaVM e PastaPC por suas respectivas pastas):
```sh
sudo mount -t vboxsf PastaVM PastaPC
```

### Navegue até a pasta onde está o projeto
Troque PastaVM pelo nome da pasta onde você deu mount
```sh
cd PastaVM
```

### Para compilar o projeto use o seguinte comando:
```sh
make all
```

### Para Executar o Programa:
```sh
./bin/shell
```

### Quando dentro do programa lembre-se de inicializar a váriavel PATH usando o comando path
```sh
path ./bin
path /path/to/bin
```
Troque "/path/to/bin" para o caminho dos binários que deseje executar

## Comandos
### cd
Alterna para o diretório específicado

```sh
cd <caminho>
```

### ls
Lista arquivos e diretórios dentro de um diretório

```sh
ls [FLAGS] <caminho>
```
- `-l` - mostra todas as informações
- `-a`- mostra todos os arquivos e diretórios
- `-R`- mostra recursivamente todos os aquivos e diretórios

### cat
Imprime o conteúdo de um ou mais arquivos

```sh
cat <arquivo1> <arquivo2>
```

### exit
Encerra o shell

```sh
exit
```
### programas externos
Após ter colocado o caminho para o executável no PATH, chamar o nome do programa

```sh
path /usr/bin
gcc --version
```

### executar comandos por arquivos batch
Crie um arquivo novo .sh com uma shebang na primeira linha(aponta para o executável do nosso shell, com o formato #!/path/to/bin/shell)
```sh
#!/home/aluno/shell/bin/shell
command 1
command 2
```
Se você salvou o arquivo pelo windows rode o comando:
```sh
sed -i -e 's/\r$//' test.sh
```
Fora do programa, rodar:
```sh
./test.sh
```
