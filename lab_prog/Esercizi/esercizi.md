# Esercizi di programmazione in C


## Cicli

### Esercizio 0

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una funzione che prenda in input l'intero **n**. La procedura legge un altro intero **m** e stampa 
- "1" se l'intero letto è dispari
- "0" se è pari.

### Esercizio 1 

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una funzione che prenda in input l'intero **n**. La procedura legge per **n** volte un altro intero, e per ogni lettura stampa 
- "1" se l'intero letto è dispari
- "0" se è pari.

### Esercizio 2 

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una procedura che prenda in input l'intero **n**. La procedura legge per **n** volte un altro intero, e per ogni lettura stampa 
- "positivo" se l'intero letto è positivo 
- "negativo" se è negativo
- "0" se è nullo.

### Esercizio 3 

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una procedura che prenda in input l'intero **n**. La procedura legge per **n** volte due altri interi **a** e **b**, e per ogni lettura stampa 
- "maggiore" se **a** > **b** 
- "minore" se **a** < **b**
- "uguale" se **a** = **b**.

### Esercizio 4

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una funzione che prenda in input l'intero **n**. La funzione legge per **n** volte un altro intero e restituisce quante volte l'intero letto è divisibile per 4. La funzione chiamante (cioè il main) stampa il risultato della funzione.

### Esercizio 5

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una funzione che prenda in input l'intero **n**. La funzione legge per **n** volte un altro intero e restituisce la somma di tutti gli interi letti. La funzione chiamante (cioè il main) stampa il risultato della funzione.

### Esercizio 6

Scrivere un programma in C che legga da tastiera un intero **n**. Il programma a questo punto deve chiamare una procedura che prenda in input l'intero **n**. La procedura legge per **n** volte un altro intero e, per ogni intero letto, stampa il suo valore assoluto.

Bonus: calcolare il valore assoluto scrivendo un'altra funzione *abs* che prende in input un intero e restituisce il suo valore assoluto.

### Esercizio 7

Scrivere un programma in C che legga dalla tastiera degli interi **finché** il numero letto è diverso da 0. Il programma deve contare quanti numeri (che non siano 0) vengono letti e stampare questo contatore.

### Esercizio 8

Scrivere un programma in C che legga dalla tastiera degli interi **finché** il numero letto è diverso da 0. Il programma deve stampare la somma di tutti i numeri letti (escluso lo 0 anche se vabbè non cambia niente).

### Esercizio 9

Scrivere un programma in C che legga dalla tastiera degli interi **finché** il numero letto è diverso da 0. Il programma deve stampare la media con 2 cifre decimali di tutti i numeri letti (escluso lo 0).

Hint: bisogna contare quanti numeri vengono letti e tenere traccia della loro somma, quindi puoi sfruttare le cose usate per i due esercizi precedenti.

**Ricorda!** Per fare la media devi stare attenta ai tipi: la media è float, mentre la somma e il contatore sono interi, quindi bisogna fare un casting.

### Esercizio 10

Scrivere un programma in C che legga dalla tastiera un intero **n** e chiami una procedura che prende in input un intero, passando **n**.

La procedura prende **n** in input ed effettua le seguenti operazioni **finché** **n** è diverso da 1$:
- stampa **n**
- se **n** è pari, allora assegna ad **n** il valore **n/2**
- se **n** è dispari, allora assegna ad **n** il valore **3n + 1**.

Infine stampare 1.

## Array
### Esercizio 1

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. 

Scrivere poi una procedura che prenda in input un array e la sua dimensione e stampi il contenuto dell'array, scrivendo un intero per riga.

### Esercizio 2

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. 

Scrivere poi una procedura che prenda in input un array e la sua dimensione e stampi i numeri pari contenuti nell'array, scrivendo un intero per riga.

### Esercizio 3

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. 

Scrivere poi una funzione che prenda in input un array e la sua dimensione e calcoli la somma degli interi contenuti nell'array. Il risultato deve essere restituito alla funzione chiamante (il main), che deve provvedere a stamparlo.

### Esercizio 4

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. 

Scrivere poi una funzione che prenda in input un array e la sua dimensione e calcoli la media dei numeri positivi (maggiori di 0) contenuti nell'array. Il risultato deve essere restituito alla funzione chiamante (il main), che deve provvedere a stamparlo.

Hint: basta contare il numero di elementi positivi e contemporaneamente calcolarne la somma.

### Esercizio 5

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. 

Scrivere poi una procedura che prenda in input un array e la sua dimensione e stampi il contenuto dell'array **in ordine inverso**, scrivendo un intero per riga.

Chiamare la procedura sull'array letto da tastiera.

### Esercizio 6

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. 

Scrivere poi una procedura che prenda in input un array e la sua dimensione e stampi i valori dell'array per cui valga una di queste condizioni:
- il valore è maggiore o uguale a 0 e pari
- il valore è negativo, ma l'elemento successivo dell'array è positivo.

Chiamare la procedura sull'array letto da tastiera.

### Esercizio 7

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. Leggere inoltre un intero. 

Scrivere poi una funzione che prenda in input un array **a**, la sua dimensione e un intero **n**. Questa funzione deve restituire:
- 1 se **n** è in **a** (cioè c'è un indice **i** per cui **a[i] = n**)
- 0 se **n** non è in **a** (cioè per nessun indice **i** vale **a[i] = n**).

Stampare il risultato della funzione con parametri in input l'array di dimensione 10 e l'intero letto da tastiera.

### Esercizio 8

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. Leggere inoltre un intero. 

Scrivere poi una procedura che prenda in input un array **a**, la sua dimensione e un intero **n**. Questa procedura deve stampare tutti i numeri dell'array che sono strettamente maggiori dell'intero **n**.

Chiamare la procedura sull'array e l'intero letto da tastiera.