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
./bin/PROJETO2
```

### Quando dentro do programa lembre-se de usar o comando path
```sh
path /path/to/bin
```
Troque "/path/to/bin" para o caminho dos binários que deseje executar