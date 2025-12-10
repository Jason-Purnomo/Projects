int main(void){
  init();
  Serial.begin(9600);

  //Konfiguration
  DDRC &= ~(1 << DDC0);

  //AD-Wandler
  ADCSRA = (1 << ADEN) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  ADCSRB = 0;
  ADMUX = (1 << REFS0) | 0;

  //ADC-Wandler starten
  ADCSRA |= (1 << ADSC);

  uint32_t time_read = 0;
  uint32_t time_print = 0;
  uint32_t Ringpuffer[100];
  int i = 0;
  uint32_t Wert = 0;
  uint32_t Mittelwert = 0;

  while(1){
    if(millis() >= time_read + 10){   
      Ringpuffer[i] = ADC;
      i++;
      time_read = millis();
      if(i >= 100){
        i = 0;
      }
    }
    
    if(millis() >= time_print + 1500){
      for(int j = 0; j<100; j++){
        Wert += Ringpuffer[j];
      }
      Mittelwert = Wert/100;
      Serial.print("Gesamtwert: ");
      Serial.println(Wert);
      Serial.print("Mittelwert: ");
      Serial.println(Mittelwert);
      time_print = millis();
      Wert = 0;
      Mittelwert = 0;
    }
  }
}