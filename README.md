# Classroom Manager

Classroom Manager è un progetto in C++ che gestisce gli studenti all'interno di una classe. Consente di memorizzare e gestire le informazioni degli studenti, come nome e cognome, e offre funzionalità di gestione della classe.

## Struttura del Progetto

Il progetto è suddiviso in diverse classi per una migliore organizzazione:

- `Person`: Rappresenta uno studente con nome e cognome.
- `MyRegex`: Classe di utilità per la validazione delle stringhe.
- ...

## Struttura del Codice Sorgente

Il codice sorgente è organizzato nelle seguenti directory:

- `src`: Contiene i file sorgente principali, tra cui `main.cpp`.
- `src/models`: Contiene le implementazioni delle classi.
- `include`: Contiene i file di intestazione.
- `include/models`: Contiene i file di intestazione per le classi.

## Compilazione del Progetto

Il progetto utilizza CMake per semplificare la compilazione. Segui questi passaggi:

1. Assicurati di avere CMake installato nel tuo sistema.
2. Crea una directory `build` nella radice del progetto.
3. Da un terminale, posizionati nella directory `build`.
4. Esegui `cmake ..` per configurare il progetto.
5. Esegui `cmake --build .` per compilare il progetto.

Il file eseguibile `main` verrà creato nella directory `build/debug`.

## Utilizzo del Progetto

Puoi eseguire il programma risultante per gestire gli studenti nella classe. Assicurati di seguire le istruzioni fornite dal programma.
