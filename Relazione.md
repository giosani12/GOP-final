<h1>Gioco dell'oca pazza</h1>
<b>Giocatori:</b> 2 - &#8734; <br>

  <h3>Funzionalità: </h3>
  A inizio partita viene generato un tabellone di ampiezza casuale compresa tra 55 e 75 caselle,
  il gioco sfrutta inoltre un mazzo di carte anch'esso
  di dimensione variabile tra 40 e 60 elementi.
  Ogni casella così come ogni carta ha un valore associato a cui corrisponde un effetto.

  <h3>Tipi di caselle:</h3>
  • Avanza di 1 casella (Prob: 12%) <br>
  • Avanza di 2 caselle  (Prob: 8%) <br>
  • Arretra di 1 casella (Prob: 12%) <br>
  • Arretra di 2 caselle (Prob: 8%) <br>
  • Salta il turno (Prob: 8%) <br>
  • Scambia la tua posizione con quella del primo in classifica (Prob: 6%) <br>
  • Pesca una carta (Prob: 10%) <br>
  • Torna alla posizione iniziale (Prob: 6%) <br>
  • Casella vuota (Prob: 16%) <br>
  • Tira di nuovo il dado (Prob: 14%) <br>
  
  <h3>Tipi di carte: </h3>
  • Avanza di 1 casella (Prob: 16%) <br> 
  • Avanza di 2 caselle (Prob: 8%) <br>
  • Arretra di 1 casella (Prob: 16%) <br>
  • Arretra di 2 caselle (Prob: 8%) <br>
  • Tira di nuovo il dado (Prob: 12%) <br>
  • Scambia la tua posizione con quella del primo in classifica (Prob: 4%) <br>
  • Ottieni 50 punti (Prob: 20%) <br>
  • Ottieni 100 punti (Prob: 16%) <br>
  
  <h3>Scelte implementative:</h3>
  Usando la programmazione a oggetti abbiamo creato la classe madre GAME e le sue classi figlie TABLE, PLAYER e CARD.
  I giocatori e il mazzo sono implementati tramite l'uso di liste circolari (ovvero liste nelle quali l'ultimo elemento punta al primo),
  questo facilita l'andamento ciclico del gioco ed è un'implementazione verosimile alla realtà, con la sola differenza che il mazzo,
  una volta finito, non viene rimescolato ma il pattern delle carte è fisso.
  Per la gestione delle probabilità riguardanti i vari effetti di carte e caselle abbiamo utilizzato un array di interi caricato con
  numeri ripetuti e compresi tra 0 e il numero di effetti.
  Le carte e le caselle sono riempite grazie ad un numero casuale e all'operatore resto, questa coppia corrisponde all'indice dell'array 
  (solo in fase di assegnamento) e tramite uno switch case viene scelto l'effetto da attivare.
  Per prendere in input i nomi dei giocatori (da max 20 caratteri) abbiamo usato il cin.getline.<br>
  
  <h3>GAME</h3>
  <b>Numero Giocatori</b> -> Varibile globale che come dice il nome contiene il numero dei giocatori e lo utilizziamo per scorrere la lista.<br>
  <b>Lunghezza deck</b> -> Numero di carte all'interno del deck<br>
  <b>Puntatore a card</b> -> Punta al mazzo di carte.<br>
  <b>Puntatore a player</b> -> Punta al giocatore corrente.<br>
  <b>Puntatore a table</b> -> Punta all'array di interi ovvero alla tabella.<br><br>
  
  <b>addToPosition</b> -> metodo che modifica la posizione del giocatore nella tabella, lo utilizziamo per i vari effetti di spostamento
  e quando tiriamo il dado.<br>
  <b>throwDice</b> -> metodo che simula il lancio del dado chiamando addToPosition.<br>
  <b>tabTypeTranslate</b> -> metodo che legge il tipo della casella e tramite uno switch case attiva uno dei vari effetti.<br>
  <b>cardTypeTranslate</b> -> metodo che legge il tipo della carta e tramite uno switch case attiva uno dei vari effetti.<br>
  <b>GetFirst</b> -> metodo che prende in input una variabile booleana e scorre tutta la tabella a partire dal traguardo, 
  effettuando tipi di controllo diversi in base alla chiamata.
  Per ogni casella scorre la lista dei player e, nel caso in cui il booleano sia falso, se nessun giocatore è lì ripete il controllo
  sulla casella precedente e si ferma quando trova uno o più giocatori; invece nel caso in cui il booleano sia vero,
  si ferma quando trova il giocatore che ha vinto perchè ha raggiunto il numero necessario di punti.
  In ogni caso restituisce il puntatore alla testa di un array di puntatori ai giocatori corrispondenti.
  Viene chiamata in SwapWithFirst e in endGame.<br>
  <b>swapWithFirst</b> -> metodo che scambia la posizione del giocatore che attivo questo effetto con quella del primo giocatore, 
  nel caso in cui ci sia più di un giocatore, vengono spostati anche gli altri. Viene chiamato dagli effetti di caselle e carte.<br>
  <b>createPlayerList</b> -> metodo che crea una lista circolare di giocatori, viene chiamato in firstTurn.<br>
  <b>deletePlayerList</b> -> metodo che cancella la lista dei giocatori, viene chiamato in endGame.<br>
  <b>createDeck</b> -> metodo che crea una lista circolare di carte, viene chiamato in firstTurn.<br>
  <b>deleteDeck</b> -> metodo che cancella la lista di carte, viene chiamato in endGame.<br>
  <b>drawCard</b> -> metodo che chiama cardTypeTranslate e sposta il puntatore della lista di carte all'elemento successivo. Viene chiamato
  in nextTurn e dagli effetti delle caselle.<br>
  <b>printChart</b> -> metodo che stampa la classifica. Viene chiamato in endGame.<br>
  <b>firstTurn</b> -> metodo che inizializza le varie componenti del gioco e stampa le regole.
  <b>nextTurn</b> -> metodo che fa iniziare il gioco con il primo turno e richiama se stesso per far continuare il gioco a meno che non venga
  chiamato endGame. <br>Scorre la lista dei giocatori in modo che ogni giocatore lanci il dado e peschi solo una volta per turno. 
  Offre la possibilità di uscire dalla partita, di stampare le regole o di continuare a giocare alla fine di ogni turno.<br>
  <b>endGame</b> -> metodo che viene chiamato in nextTurn e fa terminare il gioco. Offre anche la possibilità di ricominciare la partita, sia 
  con gli stessi giocatori che con altri.
  
  
  <h3>PLAYER</h3>
  <b>Nome</b> -> nome del giocatore (max 20 caratteri). <br>
  <b>Numero</b> -> numero che viene assegnato durante la creazione dei vari giocatori all'inizio del gioco. <br>
  <b>Posizione</b> -> posizione che il giocatore ha nel tabellone. <br>
  <b>Punti</b> -> punti acquisiti durante il gioco (inizializzati a 0). <br>
  <b>Salta il turno</b> -> variabile booleana che indica se il giocatore deve saltare il prossimo turno. <br>
  <b>Puntatore a PLAYER</b> -> puntatore utilizzato per creare la lista circolare. <br>
  
  <h3>TABLE</h3>
  <b>Puntatore a interi</b> -> <br>
  <b>Bool valid</b> -> <br>
  <b>Lunghezza</b> -> numero di caselle del tabellone. <br>
  
  <b>getType</b> -> metodo che ritorna il tipo della casella, chiamato in tabTypeTranslator. <br>
  <b>printTable</b> -> metodo che stampa la tabella, chiamato in nextTurn. <br>
  
  <h3>CARD</h3>
  <b>Tipo</b> -> intero che viene generato casualmente. <br>
  <b>Puntatore a carta</b> -> Per creare il mazzo di carte. <br>
  
  
  <h3><Organizzazione del gruppo:</h3>
  Abbiamo usato Github per poter lavorare su diversi computer, poter condividere facilmente il codice fatto e avere una cronologia
  di tutte le modifiche apportate.
  Abbiamo usato MS Visual Studio 2017 per scrivere e testare il programma ed è stato molto comodo utilizzare l'estensione di GitHub
  direttamente dall'IDE.<br>
  
  <h2>Membri:</h2>
  Francesco Filippi
  Francesco Santilli
  Giovanni Sani
