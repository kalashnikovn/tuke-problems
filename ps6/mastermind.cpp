#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "mastermind.h"
#include "lcd_wrapper.h"

char* generate_code(bool repeat, int length) {
  if(length < 1) {
    return NULL;
  }

  int position = 0;
  char possible_numbers[] = "0123456789";
  char* combination = (char*) malloc(length + 1);

  while (position < length) {
    int random_position = rand() % 10;
    if(possible_numbers[random_position] != ' ') {
      combination[position] = possible_numbers[random_position];
      possible_numbers[random_position] = repeat ? possible_numbers[random_position] : ' ';
      position++;
    }
  }
  
  combination[length] = '\0';
  return combination;  
}

char change_number(char symbol) {
  int number = (int)(symbol - '0');

  if(number == 9) {
    number = 0;
  } else {
    number += 1;
  }

  return (char)(number + '0');
}

void lights_greeting() {
  for(int j = 0; j < 3; j++) {
    for(int i = LED_BLUE_1; i <= LED_RED_4; i++) {
      digitalWrite(i, HIGH);
      delay(150);
      turn_off_leds();
    }
    delay(200);  
  }
}

void turn_off_leds() {
  int first_led = LED_BLUE_1;
  int last_led = LED_RED_4 + 1;
  for(int i = first_led; i < last_led; i++) {
    digitalWrite(i, LOW);
  }
}

void display_win() {
  char* top_text = "Winner Winner";
  char* bottom_text = "Chicken Dinner";

  lcd_clear();
  lcd_print_at(0, 0, top_text);
  lcd_print_at(2, 1, bottom_text);

  for(int i = LED_BLUE_1; i <= LED_RED_4; i++) {
    digitalWrite(i, HIGH);
  }

  delay(5000);
  turn_off_leds();
  lcd_clear();
}

void display_lost() {
  char* top_text = "You lost.";
  char* bottom_text = "Try one more.";

  lcd_clear();
  lcd_print_at(0, 0, top_text);
  lcd_print_at(0, 1, bottom_text);

  delay(5000);
  lcd_clear();
}

void play_game(char* secret) {
  int guesses = 0;
  int delay_time = 250;
  char **guess_history = (char **) calloc(10, sizeof(char *));
  for(int i = 0; i < 10; i++) {
    guess_history[i] = (char *) calloc(4, 1);
  }

  lights_greeting();
  lcd_clear();

  while(guesses < 10) {
    int led_a = 0;
    int led_b = 0;
    char guess[] = "0000";
    int history_position = guesses - 1;

    if(guesses > 0) {
      render_history(secret, guess_history, history_position);
    }

    while(analogRead(BTN_ENTER_PIN) < 1000) {
      if(digitalRead(BTN_1_PIN) == HIGH) {
        unsigned long pressed_time = millis();
        while(digitalRead(BTN_1_PIN) == HIGH) {
          if(guesses == 0) {
            break;
          }
          if (digitalRead(BTN_2_PIN) == HIGH) {
            if (history_position > 0) {
              history_position -= 1;
            }
            render_history(secret, guess_history, history_position);
            delay(200);
          } else if (digitalRead(BTN_3_PIN) == HIGH) {
            if (history_position != guesses - 1) {
              history_position += 1;
            }
            render_history(secret, guess_history, history_position);
            delay(200);
          }
        }
        unsigned long released_time = millis();
        if((released_time - pressed_time) < delay_time) {
          guess[0] = change_number(guess[0]);
          delay(delay_time);
        }
      } else if(digitalRead(BTN_2_PIN) == HIGH) {
        guess[1] = change_number(guess[1]);
        delay(delay_time);
      } else if(digitalRead(BTN_3_PIN) == HIGH) {
        guess[2] = change_number(guess[2]);
        delay(delay_time);
      } else if(digitalRead(BTN_4_PIN) == HIGH) {
        guess[3] = change_number(guess[3]);
        delay(delay_time);
      }

      lcd_print_at(0, 0, "ATTEMPT:");
      lcd_num(guesses + 1);
      lcd_print_at(0, 1, guess);
    }

    delay(delay_time);
    get_score(secret, guess, &led_a, &led_b);

    if(led_a == 4) {
      display_win();
    } else {
      guesses += 1;
      strcpy(guess_history[guesses - 1], guess);
      lcd_clear();
      turn_off_leds();
      render_leds(led_a, led_b);  
    }
  }

  display_lost();
}

void render_leds(const int peg_a, const int peg_b) {
  int red_led = LED_RED_1;
  for(int i = 0; i < peg_a; i++) {
    digitalWrite(red_led, HIGH);
    red_led += 2;
  }

  int blue_led = LED_BLUE_1;
  for(int i = 0; i < peg_b; i++) {
    digitalWrite(blue_led, HIGH);
    blue_led += 2;
  }
}

void render_history(char* secret, char** history, const int entry_nr) {
  int led_a = 0;
  int led_b = 0;
  lcd_set_cursor(10, 1);
  lcd_num(entry_nr + 1);
  lcd_print((char *) ":");
  get_score(secret, history[entry_nr], &led_a, &led_b);
  lcd_num(led_a);
  lcd_print((char *) "A");
  lcd_num(led_b);
  lcd_print((char *) "B");
  turn_off_leds();
  render_leds(led_a, led_b);
}

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b) {
  int secret_length = strlen(secret);
  char* secret_duplicate = (char *) calloc(secret_length + 1, 1);
  strcpy(secret_duplicate, secret);

  for (int i = 0; i < secret_length; i++) {
    if (secret_duplicate[i] == guess[i]) {
      secret_duplicate[i] = ' ';
      *peg_a += 1;
    }
  }

  for (int i = 0; i < secret_length; i++) {
    if (secret_duplicate[i] != ' ') {
      for (int j = 0; j < secret_length; j++) {
        if (i != j && secret_duplicate[i] == guess[j]) {
          secret_duplicate[i] = ' ';
          *peg_b += 1;
          break;
        }
      }
    }
  }
}