#include <time.h>

#include "lcd_wrapper.h"
#include "mastermind.h"

void setup() {
  srand(time(NULL));
  // Serial.begin(9600);
  lcd_init();
}

void loop() {
  char* code = generate_code(false, 4);
  play_game(code);
  free(code);
}