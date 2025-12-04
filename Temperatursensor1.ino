int main(void){
  init();
  Serial.begin(9600);

  //Konfiguration
  //PINS SS, MOSI, MISO, SCK
  DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);  
  DDRB &= ~(1 << DDB4);      
  //SPI
  SPCR = (1 << MSTR) | (1 << SPE) | (1 << SPR0);
  //Mode 0,0: SCLK idles low
  //Daten werden bei steigender Flanke übernommen und gelesen

  while(1){
    //SS LOW setzen
    PORTB &= ~(1 << PORTB2);

    //SPI Transfer starten
    SPDR = 0b00000001;          //Din
    //auf Ende von SPI Transfer warten
    while(!(SPSR & (1 << SPIF)));       //warten auf SPIF == 1
    uint8_t Byte1 = SPDR;       //Dout


    SPDR = 0b11100000;          //Din
    //auf Ende von SPI Transfer warten
    while(!(SPSR & (1 << SPIF)));       //warten auf SPIF == 1
    uint8_t Byte2 = SPDR;       //Dout


    SPDR = 0b00000000;          //Din
    //auf Ende von SPI Transfer warten
    while(!(SPSR & (1 << SPIF)));       //warten auf SPIF == 1
    uint8_t Byte3 = SPDR;       //Dout

    uint16_t Wert = ((Byte2 & 0x0F) << 8) | Byte3;        //0x0F = 0b00001111
    float Voltage = (float)Wert * 5 / 4096;
    float Temperatur = Voltage / 0.01;                    //0.01 = 10mV

    //SS HIGH setzen
    PORTB |= (1 << PORTB2);

    Serial.println(Temperatur);
    _delay_ms(500);
  }
}