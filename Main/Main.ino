#include <LiquidCrystal.h>

LiquidCrystal lcd(7,6,5,4,3,2);
void setup() {
  // INITIAL PARAMETERS
  // LCD sizing
  lcd.begin(16,2);

}

void loop() {
  // 
  lcd.setCursor(0,0);
  lcd.print("Ativado");
}
