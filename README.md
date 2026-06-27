Trabalho Final de Estruturas de Dados

Repositório destinado à entrega do Trabalho Final da disciplina de Estruturas de Dados.

O projeto foi dividido em três partes, conforme solicitado:

Trabalho A — Listas Simples
Trabalho B — Pilhas Simples
Trabalho C — Filas Simples

Cada trabalho possui um programa separado em linguagem C, utilizando struct, vetor de struct, menu interativo e arquivo CSV para salvar e carregar os dados.

Integrantes:
Andrei Rodrigues
Saulo Freitas
Eduardo Victor
Turma: A

Temas escolhidos
Trabalho A — Listas Simples

Responsável: Eduardo Victor

Tema: A definir

Observação: o tema do Trabalho A ainda será confirmado.

Trabalho B — Pilhas Simples
Responsável: Andrei Rodrigues

Tema escolhido: Chamadas de Emergência

O Trabalho B simula uma pilha de chamadas de emergência. Cada chamada possui protocolo, local da ocorrência, tipo da ocorrência e horário.
A estrutura utilizada foi uma pilha simples com vetor de struct e uma variável de controle chamada topo.
A lógica principal usada foi LIFO, ou seja, o último elemento inserido é o primeiro a ser removido.

No programa:
registrar chamada corresponde a empilhar;
atender chamada corresponde a desempilhar;
consultar última chamada corresponde a verificar o topo da pilha;
buscar chamada permite localizar uma chamada pelo protocolo;
listar chamadas mostra os registros da pilha;
salvar e carregar CSV permitem manter os dados armazenados.

Trabalho C — Filas Simples
Responsável: Saulo Freitas

Tema: A confirmar

Organização do repositório
Trabalho_Final_Estruturas_Dados/
│
├── README.md
│
├── Trabalho_A/
│   ├── trabalho_a.c
│   └── dados_a.csv
│
├── Trabalho_B/
│   ├── trabalho_b_estruturas.c
│   └── dados_b.csv
│
└── Trabalho_C/
    ├── trabalho_c.c
    └── dados_c.csv
