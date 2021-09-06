# Fantapippa
* Questo sito descrive il concetto di Fantapippa
** Princìpi di base :
  Fantapippa consiste in una classifica alternativa al gioco del fantacalcio
  Con il termine di Fantapippa si indicano rispettivamente
  a) Il nome del concetto
  b) Il nome della classifica alternativa, che sarà conosciuta come classifica Fantapippa
  c) L'algoritmo che consente il calcolo dei punti
** Il concetto di Fantapippa
  Il Fantapippa intende premiare il fantallenatore che sbaglia di più nella messa in campo della propria squadra.
  Per ogni giornata si calcola il contributo relativo ad ogni fantasquadra, con questo contributo viene aggiornata la classifica Fantapippa.
  Al termine della stagione, il fantallenatore responsabile della squadra con maggior punteggio verrà nominato vincitore della classifica Fantapippa, di conseguenza verrà indicato come l'allenatore Fantapippa
** La classifica Fantapippa
  Diversamente dalla classifica di fantalega, che si limita a confrontare le squadre che giocano nell'ambito della stessa lega, la classifica Fantapippa può raccogliere il contributo di diverse leghe anche appartenenti ad ambiti diversi.
  I punti attribuiti nella classifica Fantapippa sono i punti potenzialmente persi dal fantallenatore qualora avesse schierato una formazione diversa.
** Algoritmo di Fantapippa
  - Si chiami squadra locale la squadra per cui si vuole calcolare il punteggio Fantapippa e squadra avversaria la squadra contro cui la squadra locale ha giocato la partita di Lega.
  - Per la sola squadra locale si calcoli il risultato ottenuto nella partita secondo le regole della Lega in cui la squadra gioca
  - Per la stessa squadra, si riarrangi la formazione seguendo le regole definite nella Lega in cui la squadra gioca per ottenere il punteggio massimo, ruotando giocatori e cambiando il modulo sempre secondo le regole della Lega in cui la squadra gioca
  - Una volta ottenuto il nuovo punteggio di squadra, lo si compari con il valore ottenuto dalla squadra avversaria.
  - Se la squadra locale aveva predecentemente perso, ma con il nuovo punteggio essa avrebbe pareggiato, si assegnarà ad essa il valore 1
  - Se la squadra locale aveva precedentemente pareggiato, ma con il nuovo punteggio essa avrebbe vinto, si assegnerà ad essa il valore 2
  - Se la squadra locale aveva precedentemente perso, ma con il nuovo punteggio essa avrebbe vinto, si assegnerà ad essa il valore 3
  - Altrimenti la squadra locale vedrà assegnato il valore 0 (zero)
 
