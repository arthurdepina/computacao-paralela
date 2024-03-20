No caso do `lab 02 b`, a execução não é feita com o `make run` e sim tradicionalmente.

`gcc matrix_vector_mult.c -o matrix -pthread`

E em seguida:

`./matrix NumeroDeThreads`

por exemplo:

`./matrix 4`

<br>
1)

![a](https://github.com/arthurdepina/computacao-paralela/assets/84559827/068a36bc-7e9b-487e-b16f-c5afee8bcc8a)

<br>
2)

![b](https://github.com/arthurdepina/computacao-paralela/assets/84559827/46cc0fe8-5b9a-45cc-b5a7-b00c7b193d38)

<br>
3)

Em uma solução nova, eu consideraria alterar a distribuição de linhas por threads, creio que em casos como o de 6 threads, há muito tempo sendo gasto na distribuição. 
