#include <LiquidCrystal.h>

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

const int LED = 6;
const int PONTO = 7;
const int BARRA = 0;
const int ENTER = 8;

String morseInput = "";
String outputText = "";
char charAtual = ' ';

unsigned long enterPressTime = 0;
bool enterWasHeld = false;

struct MorseCode {
  const char* code;
  char letter;
};

MorseCode morseTable[] = {
  {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
  {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
  {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
  {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
  {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
  {"--..", 'Z'}, {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
  {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'},
  {"---..", '8'}, {"----.", '9'}
};

char morseToChar(String code) {
  for (int i = 0; i < sizeof(morseTable) / sizeof(MorseCode); i++) {
    if (code == morseTable[i].code) return morseTable[i].letter;
  }
  return '?';
}

void setup() {
  pinMode(PONTO, INPUT_PULLUP);
  pinMode(BARRA, INPUT_PULLUP);
  pinMode(ENTER, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED, HIGH);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // Captura ponto
  if (digitalRead(PONTO) == LOW) {
    Serial.println("Apertou ponto");
    morseInput += ".";
    delay(200);
  }

  // Captura traço
  if (digitalRead(BARRA) == LOW) {
    Serial.println("Apertou traço");
    morseInput += "-";
    delay(200);
  }

  // Monitoramento do botão ENTER
  if (digitalRead(ENTER) == LOW){
    Serial.println("Apertou enter");
    if (!enterWasHeld) {
      enterPressTime = millis();
      enterWasHeld = true;
    }
    unsigned long holdDuration = millis() - enterPressTime;

    if (holdDuration > 3000) {
      // Se segurou mais de 3s, LED apaga (enquanto estiver pressionado)
      digitalWrite(LED, HIGH);
    } else if (holdDuration > 1000) {
      // Entre 1 e 3 segundos, LED acende
      digitalWrite(LED, LOW);
    } else {
      // Menos de 1 segundo, LED desligado
      digitalWrite(LED, HIGH);
    }

  } else if (enterWasHeld) {
    // Botão foi solto, tratar ação conforme tempo pressionado
    unsigned long pressDuration = millis() - enterPressTime;

    if (pressDuration > 3000) {
      // Apaga tudo
      outputText = "";
      lcd.clear();
    }
    else if (pressDuration > 1000) {
      // Adiciona espaço
      if (outputText.length() < 32) {
        outputText += ' ';
      }
    } else {
      // Traduz morse atual
      char c = morseToChar(morseInput);
      if (c != '?') {
        outputText += c;
      }
    }

    morseInput = "";
    charAtual = ' ';

    // Apaga LED quando soltar botão
    digitalWrite(LED, HIGH);

    enterWasHeld = false;
    delay(100);
  }

  // Atualiza letra enquanto digita
  if (morseInput.length() > 0) {
    charAtual = morseToChar(morseInput);
  } else {
    charAtual = ' ';
  }

  // Atualiza display
  lcd.setCursor(0, 0);
  int len = outputText.length();
  if (len > 16) {
    lcd.print(outputText.substring(len - 16));
  } else {
    lcd.print(outputText);
    lcd.print("                ");
  }

  lcd.setCursor(0, 1);
  if (morseInput.length() > 0) {
    lcd.print(charAtual);
    lcd.print(" ");
    lcd.print(morseInput);
    lcd.print("                ");
  } else {
    lcd.print("                ");
  }
}
