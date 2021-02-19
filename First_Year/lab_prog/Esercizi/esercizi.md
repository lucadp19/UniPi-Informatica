# Esercizi di programmazione in C


## Cicli

### Esercizio 0

Scrivere un programma in C che legga da tastiera un intero $n$. 

Il programma a questo punto deve chiamare una funzione che prenda in input l'intero $n$. La procedura legge un altro intero $m$ e stampa 
\begin{itemize}
   \item "1" se l'intero letto è dispari
   \item "0" se è pari.
\end{itemize}

### Esercizio 1 

Scrivere un programma in C che legga da tastiera un intero $n$. 

Il programma a questo punto deve chiamare una funzione che prenda in input l'intero $n$. La procedura legge per $n$ volte un altro intero, e per ogni lettura stampa 
\begin{itemize}
   \item "1" se l'intero letto è dispari
   \item "0" se è pari.
\end{itemize}

### Esercizio 2 

Scrivere un programma in C che legga da tastiera un intero $n$. 

Il programma a questo punto deve chiamare una procedura che prenda in input l'intero $n$. La procedura legge per $n$ volte un altro intero, e per ogni lettura stampa 
\begin{itemize}
   \item "positivo" se l'intero letto è positivo 
   \item "negativo" se è negativo
   \item "0" se è nullo.
\end{itemize}

### Esercizio 3 

Scrivere un programma in C che legga da tastiera un intero $n$. 
Il programma a questo punto deve chiamare una procedura che prenda in input l'intero $n$. La procedura legge per $n$ volte due altri interi $a$ e $b$, e per ogni lettura stampa 
\begin{itemize}
   \item "maggiore" se $a$ > $b$ 
   \item "minore" se $a$ < $b$
   \item "uguale" se $a$ = $b$.
\end{itemize}

### Esercizio 4

Scrivere un programma in C che legga da tastiera un intero $n$. 

Il programma a questo punto deve chiamare una funzione che prenda in input l'intero $n$. La funzione legge per $n$ volte un altro intero e restituisce quante volte l'intero letto è divisibile per 4. 

La funzione chiamante (cioè il main) stampa il risultato della funzione.

### Esercizio 5

Scrivere un programma in C che legga da tastiera un intero $n$. 

Il programma a questo punto deve chiamare una funzione che prenda in input l'intero $n$. La funzione legge per $n$ volte un altro intero e restituisce la somma di tutti gli interi letti. 

La funzione chiamante (cioè il main) stampa il risultato della funzione.

### Esercizio 6

Scrivere un programma in C che legga da tastiera un intero $n$.

Il programma a questo punto deve chiamare una procedura che prenda in input l'intero $n$. La procedura legge per $n$ volte un altro intero e, per ogni intero letto, stampa il suo valore assoluto.

Bonus: calcolare il valore assoluto scrivendo un'altra funzione *abs* che prende in input un intero e restituisce il suo valore assoluto.

### Esercizio 7

Scrivere un programma in C che legga dalla tastiera degli interi **finché** il numero letto è diverso da 0.

Il programma deve contare quanti numeri (che non siano 0) vengono letti e stampare questo contatore.

### Esercizio 8

Scrivere un programma in C che legga dalla tastiera degli interi **finché** il numero letto è diverso da 0. 

Il programma deve stampare la somma di tutti i numeri letti (escluso lo 0 anche se vabbè non cambia niente).

### Esercizio 9

Scrivere un programma in C che legga dalla tastiera degli interi **finché** il numero letto è diverso da 0. 

Il programma deve stampare la media con 2 cifre decimali di tutti i numeri letti (escluso lo 0).

Hint: bisogna contare quanti numeri vengono letti e tenere traccia della loro somma, quindi puoi sfruttare le cose usate per i due esercizi precedenti.

**Ricorda!** Per fare la media devi stare attenta ai tipi: la media è float, mentre la somma e il contatore sono interi, quindi bisogna fare un casting.

### Esercizio 10

Scrivere un programma in C che legga dalla tastiera un intero $n$ e chiami una procedura che prende in input un intero, passando $n$.

La procedura prende $n$ in input ed effettua le seguenti operazioni: **finché** $n$ è diverso da $1$
\begin{enumerate}
   \item stampa $n$
   \item se $n$ è pari, allora assegna ad $n$ il valore $n/2$
   \item se $n$ è dispari, allora assegna ad $n$ il valore $3n + 1$.
\end{enumerate}

Infine stampare 1.

### Esercizio 11

Scrivere un programma in C che legga da tastiera due numeri $a$ e $b$. 

Scrivere poi una funzione che prenda in input due interi e ne calcoli il Massimo Comun Divisore seguendo l'algoritmo di Euclide:
\begin{itemize}
   \item se uno dei due numeri è 0, allora si ferma e restituisce l'altro;
   \item se $a > b$ allora sostituisce $a$ con il resto di $a$ modulo $b$ e continua il processo;
   \item se $a < b$ allora sostituisce $b$ con il resto di $b$ modulo $a$ e continua il processo.
\end{itemize}

Chiamare la funzione sui due numeri $a$ e $b$ e stamparne l'output.

### Esercizio 12

Scrivere un programma in C che legga da tastiera un numero intero $n$. 

Scrivere poi una procedura che prenda in input $n$ e stampi in ordine tutti i numeri di Fibonacci più piccoli di $n$.

Ricordiamo che la successione di Fibonacci è definita come segue:
$$F(n) = \begin{cases}
   0 &\text{se } n = 0\\
   1 &\text{se } n = 1\\
   F(n-1) + F(n-2) &\text{altrimenti}
\end{cases}$$

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
\begin{itemize}
   \item il valore è maggiore o uguale a 0 e pari
   \item il valore è negativo, ma l'elemento successivo dell'array è positivo.
\end{itemize}

Chiamare la procedura sull'array letto da tastiera.

### Esercizio 7

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. Leggere inoltre un intero. 

Scrivere poi una funzione che prenda in input un array $a$, la sua dimensione e un intero $n$. Questa funzione deve restituire:
\begin{itemize}
   \item 1 se $n$ è in $a$ (cioè c'è un indice $i$ per cui $a[i] = n$)
   \item 0 se $n$ non è in $a$ (cioè per nessun indice $i$ vale $a[i] = n$).
\end{itemize}

Stampare il risultato della funzione con parametri in input l'array di dimensione 10 e l'intero letto da tastiera.

### Esercizio 8

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi. Leggere inoltre un intero. 

Scrivere poi una procedura che prenda in input un array $a$, la sua dimensione e un intero $n$. Questa procedura deve stampare tutti i numeri dell'array che sono strettamente maggiori dell'intero $n$.

Chiamare la procedura sull'array e l'intero letto da tastiera.

### Esercizio 9

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca in un array di 10 elementi.

Scrivere poi una funzione che prenda in input un array e la sua dimensione. Questa funzione deve restituire la media di tutti gli elementi della sequenza diversi da 0 e di segno uguale all'ultimo elemento della sequenza.

Chiamare la funzione sull'array e stamparne il risultato.

NB: la funzione deve essere restituire la media, fai attenzione ai tipi.

### Esercizio 10

Scrivere un programma in C che legga da tastiera interi positivi e li inserisca ciclicamente in un array di 10 elementi: il primo elemento va inserito in posizione $0$, il secondo in posizione $1$,..., il decimo in posizione $9$, l'undicesimo in posizione $0$, il dodicesimo in posizione $1$ eccetera.

Il programma smette di leggere interi da tastiera quando legge uno $0$.

Stampare il risultato del programma.

Hint: usa l'operatore modulo.

### Esercizio 11

Scrivere un programma in C che legga da tastiera 10 interi e inserisca i primi 5 nell'array $a$ e gli altri nell'array $b$.

Scrivere poi una funzione che controlla se esiste un elemento dell'array $a$ minore di tutti gli elementi dell'array $b$; se esiste restituisce l'indice dell'elemento, altrimenti restituisce -1.

Stampare il risultato della funzione.

### Esercizio 12

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca nell'array $a$.

Scrivere poi una funzione che calcola il massimo dell'array $a$ e restituisce la sua **posizione**.

Stampare il risultato della funzione (la posizione del massimo) e il valore del massimo (ad esempio, se il massimo è 3 ed è in posizione 5, allora l'output deve essere "5 3").

### Esercizio 13

Scrivere un programma in C che legga da tastiera 10 interi e inserisca i primi 5 nell'array $a$ e gli altri nell'array $b$. Dichiarare inoltre un terzo array $c$, sempre di $5$ elementi.

Scrivere poi una procedura che per ogni indice $0 \leq i < 5$ calcola il massimo tra $a[i]$ e $b[i]$ e lo inserisce in $c[i]$.

Stampare l'array $c$ al termine del processo.

### Esercizio 14\

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca nell'array $a$. Dichiarare inoltre un secondo array $b$, sempre di $10$ elementi.

Scrivere poi una procedura che per ogni indice $0 \leq i < 10$ calcola il massimo tra gli elementi $a[0]$, $a[1]$,... fino ad $a[i]$ compreso e lo inserise in $b[i]$.

Scrivere inoltre una funzione che calcoli la media degli elementi di un array.

Stampare l'array $b$ al termine del processo e la media dei suoi elementi con 2 cifre decimali.

### Esercizio 15

Scrivere un programma in C che legga da tastiera 12 interi e inserisca i primi 6 nell'array $a$ e gli altri nell'array $b$. Dichiarare inoltre un terzo array $c$ di $3$ elementi.

Scrivere poi una procedura che calcoli il prodotti tra gli elementi pari dell'array $a$ e gli elementi dispari dell'array $b$ e li inserisca in ordine nell'array $c$ (ovvero, $c[0] = a[0]*b[1]$, $c[1] = a[2]*b[3]$, $c[2] = a[4]*b[5]$, ecc se gli array fossero più lunghi).

Scrivere un'altra funzione che calcoli il minimo di un array.

Stampare il minimo dell'array $c$.

### Esercizio 16

Scrivere un programma in C che legga da tastiera 10 interi e li inserisca nell'array $a$. 

Scrivere una funzione che prenda in input un array e la sua dimensione, calcoli la somma di tutti gli elementi di posto pari, la somma di tutti gli elementi di posto dispari, faccia la media tra i due risultati e la restituisca in output.

Stampare la media con due cifre decimali e arrotondata all'intero inferiore.

Hint: per arrotondare un float all'intero inferiore basta fare un cast ad int.

## Puntatori

### Esercizio 1
Scrivere un programma in C che legga da tastiera due numeri $a$, $b$. Dichiarare inoltre due variabili intere sum, prod.

Scrivere una procedura che modifica il valore di sum e prod nel seguente modo:
\begin{itemize}
   \item sum deve contenere la somma di $a$ e $b$, 
   \item prod deve contenere il prodotto di $a$ e $b$.
\end{itemize}

Stampare infine il valore di sum e prod.

### Esercizio 2
Scrivere un programma in C che legga da tastiera un numero $n$. Scrivere una procedura che modifichi il valore di $n$ nel seguente modo:
\begin{itemize}
   \item se $n$ è pari allora $n = n/2$, 
   \item se $n$ è dispari allora $n = (n+1)/2$.
\end{itemize}

Stampare il nuovo valore di $n$.

### Esercizio 3
Scrivere un programma in C che legga da tastiera un array di 10 elementi. Dichiarare inoltre due variabili pos_max e pos_min, di tipo intero.

Scrivere una procedura che modifica i valori di pos_max e pos_min inserendovi dentro la posizione del massimo e del minimo dell'array che viene passato come argomento.

Stampare i valori contenuti in pos_max e pos_min.

### Esercizio 4
Scrivere un programma in C che legga da tastiera un array di 5 elementi. Dichiarare inoltre due variabili intere (first_even, last_odd).

Scrivere una procedura che dato l'array e la sua dimensione modifichi il contenuto di first_even e last_odd, inserendovi rispettivamente
\begin{itemize}
   \item la posizione del primo numero pari contenuto nell'array, 
   \item la posizione dell'ultimo numero dispari contenuto nell'array.
\end{itemize}

Stampare infine il contenuto di first_even e last_odd.

### Esercizio 5
Scrivere un programma in C che legga da tastiera due interi $a$ e $b$. Dichiarare inoltre due puntatori $p_1$ e $p_2$ e fare in modo che $p_1$ punti ad $a$, $p_2$ punti a $b$.

Scrivere una procedura che modifichi il valore dei puntatori (non degli oggetti puntati) e scambi tra di loro i puntatori (ovvero, alla fine dell'esecuzione della procedura, $p_1$ deve puntare a $b$ e $p_2$ deve puntare ad $a$).

Stampare su una riga l'indirizzo di $a$ e di $b$ e su un'altra riga il contenuto di $p_1$ e $p_2$ (devono venire fuori gli stessi indirizzi, ma in ordine inverso).

Hint: per modificare una variabile di tipo int in una procedura abbiamo bisogno di un puntatore a intero, per modificare una variabile di tipo float abbiamo bisogno di un puntatore a float, per modificare una variabile di tipo *puntatore a intero* abbiamo bisogno di...?