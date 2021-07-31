#include "keypasswordtyper.h"

bool done = false;
void type(char *);
void enter();

void setup() {
  Serial.begin(9600);
  delay(200);
}

void loop() {

  if (!done) {
    type("YOUR BIG PASSWORD GOES HERE");
    enter();
    done = true;
  }
  delay(5000);
}

void type(char *txt) {
  while (*txt) {
    if (*txt >= 'a' && *txt <= 'z') {
      buf[2] = *txt - 'a' + 4;
    }
    else if (*txt >= 'A' && *txt <= 'Z') {
      buf[0] = KEY_LEFT_SHIFT;

      buf[2] = *txt - 'A' + 4;
    }
    else if (*txt >= '0' && *txt <= '9') {
      if (*txt == '0') {
        buf[2] = *txt - 9;
      }
      else {
        buf[2] = *txt - 19;
      }
    }
    else if (*txt == ' ') {
      buf[2] = KEY_SPC;
    }
    else if (*txt == '&') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = 0x24;
    }
    else if (*txt == '>') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = KEY_NONE;
    }
    else if (*txt == '<') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = 0x36;
    }
    else if (*txt == '|') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = 0x64;
    }
    else if (*txt == '/') {
      buf[0] = KEY_RIGHT_ALT;
      buf[2] = 0x14;
    }
    else if (*txt == '\\') {
      buf[2] = 0x34;
    }
    else if (*txt == ';') {
      buf[2] = 0x38;
    }
    else if (*txt == '(') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = 0x26;
    }
    else if (*txt == ')') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = 0x27;
    }
    else if (*txt == '{') {
      buf[0] = KEY_RIGHT_ALT;
      buf[2] = 0x24;
    }
    else if (*txt == '}') {
      buf[0] = KEY_RIGHT_ALT;
      buf[2] = 0x27;
    }
    else if (*txt == '[') {
      buf[0] = KEY_RIGHT_ALT;
      buf[2] = 0x25;
    }
    else if (*txt == ']') {
      buf[0] = KEY_RIGHT_ALT;
      buf[2] = 0x26;
    }
    else if (*txt == '-') {
      buf[2] = 0x2D;
    }
    else if (*txt == '=') {
      buf[2] = 0x2E;
    }
    else if (*txt == '.') {
      buf[2] = 0x37;
    }
    else if (*txt == ',') {
      buf[2] = 0x36;
    }
    else if (*txt == '_') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = KEY_UNDERLINE;
    }
    else if (*txt == '+') {
      buf[0] = KEY_LEFT_SHIFT;
      buf[2] = KEY_PLUS;
    }
    else {
      buf[2] = KEY_NONE;
    }

    Serial.write(buf, 8);   // Send keypress
    buf[0] = 0;
    buf[2] = 0;
    Serial.write(buf, 8);   // Release key
    txt++;
  }
}

void enter() {
  buf[2] = KEY_ENTER;

  Serial.write(buf, 8);       // Send keypress
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8);
}
