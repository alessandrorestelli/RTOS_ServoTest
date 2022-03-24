# RTOS_ServoTest

![Servo motore immagine](https://arduinoproject.altervista.org/wp-content/uploads/2020/04/Servo-Motor_Internal.jpg)

Un servomotore è un particolare tipo di motore, generalmente di piccola potenza, che si differenzia dai motori tradizionali. Quello da noi utilizzato ha un'ampiezza di 180°.
Il servomotore viene alimentato con un tensione di 5V e per essere pilotato è collegato a un pin(PE11) della scheda STM32L476VGTX che genera un segale PVM.

## Schema elettrico:
Nell'immagine che segue si potrà vedere lo schema elettrico del servomotore:
![Immagine schema elettrico](https://github.com/alessandrorestelli/RTOS_ServoTest/blob/main/Schema%20elettrico%20servo.PNG)

Il servomotre presenta 3 ingressi: uno per l'alimentazione, uno per il collegamento alla messa a terra e uno collegato al pin della scheda per ricevere il seganle che gli permetterà di muoversi.

## Duty cycle:
Nell'immagine che segue si potrà vedere il duty cycle del servomotore, ovvero il rapporto tra il tempo durante il quale un carico o un circuito è attivo (ON) e il tempo durante il quale è inattivo (OFF):
![Immagine del duty cicle](https://arduinoproject.altervista.org/wp-content/uploads/2020/04/Servo_Pulse_Control.png)

## Schema di montaggio: 
Abbiamo collegato il servomotore al pin PE11 del microcontrollore, oltre che a massa(GND) e all'alimetazione(VCC=5V). In questo modo
gli arriverà un seganle che gli permetterà di eseguire il giusto movimento per smistare il pacco che arriva.

## Funzionamento: 
Il servomote servirà a smistare i pacchi che verranno rilevati e di cui viene rilevato il colore. In base a questo, dovrà muoversi verso sinistra o verso destra. Per farlo abbiamo creato 2 task: TaskSmistaDX e TaskSmistaSX.

Questi task sono stati implementati per smistare i pacchi in base al colore. Pilotano il servomotore verso destra o sinistra in base al pacco che è stato rilevato.
Per prima cosa, entrano in funzione una volta ricevuto il “segnale” tramite event group dal task che rileva il colore dell’oggetto. Se il pacco è bianco, il servomotore si muoverà a destra e poi a sinistra (TaskSmistaSX). Quando invece è nero, verrà pilotato prima a sinistra e poi a destra (TaskSmistaDX).
Dopo che un pacco viene smistato, il servomotore viene riportato alla posizione di partenza, ovvero al centro. In questo modo è pronto per smistare il pacco seguente.
