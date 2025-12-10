int main(void){
  init();
  Serial.begin(9600);

  //Konfiguration
  DDRB |= (1 << DDB2);      //LED pin 10 ~ PWM

  //TIMER
  TCCR1A = (1 << COM1B1) | (1 << WGM11) | (1 << WGM10);
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);

  while(1){
    //OCR1B = 128 * sin(2*M_PI*0.5*(millis()/1000.0)) + 128;   //millis()/1000 --> t in sekunden
    //da 10-Bit bis 1023 Bereich arbeitet, müssen wir das umwandeln, indem wir *2^2
    OCR1B = 512 * sin(2*M_PI*0.5*(millis()/1000.0)) + 512;   //millis()/1000 --> t in sekunden
  }
}