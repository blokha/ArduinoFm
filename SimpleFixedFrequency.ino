                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   #include <Bounce2.h>
#include <Wire.h>
#include <TEA5767Radio.h>
#include <LiquidCrystal_I2C.h>

#define PIN_RS_UP 2
#define PIN_RS_DOWN 3
// A4 (SDA) и A5 (SCL).
TEA5767Radio radio = TEA5767Radio();
LiquidCrystal_I2C lcd(0x27, 16, 2);
Bounce2::Button button_up = Bounce2::Button();
Bounce2::Button button_down = Bounce2::Button();

float frequency[] = {87.50, 88.10, 88.50, 89.70, 90.10, 90.50, 90.90, 91.40, 100.50, 101.10, 101.50, 102.00, 102.50, 102.90, 103.30, 104.00, 104.40, 104.80, 105.30, 105.80, 106.40, 106.80, 107.30, 107.70};
char* radiostation[] = {"1 chanal",
                        "Culture",
                        "Relax",
                        "Retro FM",
                        "Melodija FM",
                        "Radio ROKS",
                        "Avtoradio",
                        "Radio NV",
                        "Luks FM",
                        "Russkoe Radio",
                        "Radio Friday",
                        "Hit FM",
                        "Europe Plus",
                        "Nashe Radio",
                        "DJ FM",
                        "Power FM",
                        "Top Radio",
                        "Radio Promin",
                        "Shanson",
                        "Prosto Radio",
                        "Kraina FM",
                        "Kiss FM",
                        "Informator FM",
                        "Maksimum"
                       };
int fr = 6;
int frequency_size = sizeof(frequency) / sizeof(frequency[0]);
void setup()
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  button_up.attach( PIN_RS_UP, INPUT);
  button_down.attach( PIN_RS_DOWN, INPUT);
button_up.interval(5); 
button_down.interval(5);
button_up.setPressedState(LOW); 
button_down.setPressedState(LOW); 
 radio_set();
}
                                                                            
void loop()
{  
 button_up.update();
  button_down.update();
  if ( button_up.pressed() ) {
    fr++;
    if (fr>frequency_size-1) fr=0;
    radio_set();
}

  if ( button_down.pressed() ) {
    fr--;
    if (fr<0) fr=frequency_size-1;
    radio_set();
}
}

void radio_set() {
  radio.setFrequency(frequency[fr]);
  lcd.clear();
  lcd.print(radiostation[fr]);
  lcd.setCursor(0, 1);
  lcd.print(fr); lcd.print(" - ");
  lcd.print(frequency[fr]);lcd.print(" MHz");
}
