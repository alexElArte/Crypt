/*
 * This program create keys for a cryptogram
 * By alex_el.arte
 */

// Length of the sort key
const byte keylen = 32;

// Char encode: a-z and 0-9
byte Ckey[36];

// Variable for the sort key
byte Mkey[keylen];

// A simple variable to know the efficiency of the test
int nb = 0;

void setup() {
  // Initialize serial and random
  Serial.begin(115200);
  randomSeed(analogRead(0));

  // Create a key to replace letters by random numbers
  for (byte i = 0; i < 36; i++) {
    bool test = false;
    byte key;
    // While the key is the same as another repeat the
    // sequence
    while (test == false) {
      // Get a number between 0 and 255
      key = random(256);
      test = true;
      // Test all variable if it is twice in the array
      for (byte j = 0; j < (i+1); j++) {
        if (Ckey[j] == key) {
          test = false;
          break;
        }
      }
      Serial.print(".");
      nb++;
    }
    // Put the tested number into the array
    Ckey[i] = key;
  }
  // Print the efficiency
  Serial.print(nb);
  Serial.println();
  nb = 0;

  // Now do the same thing for the message
  for (byte i = 0; i < keylen; i++) {
    bool test = false;
    byte key;
    while (test == false) {
      key = random(keylen);
      test = true;
      for (byte j = 0; j < i; j++) {
        if (Mkey[j] == key) {
          test = false;
          break;
        }
      }
      Serial.print(".");
      nb++;
    }
    Mkey[i] = key;
  }
  Serial.print(nb);
  Serial.println();


  // Print the keys
  Serial.println("// Random number create with 'randomKey'");
  Serial.print("const byte Ckey[36] = {");
  for (byte i = 0; i < 36; i++) {
    Serial.print(Ckey[i]);
    if(i != 35){ Serial.print(", ");
    } else { Serial.println("};");}
  }
  
  Serial.print("const byte Mkey["+String(keylen)+"] = {");
  for (byte i = 0; i < keylen; i++) {
    Serial.print(Mkey[i]);
    if(i != (keylen-1)){ Serial.print(", ");
    } else { Serial.println("};");}
  }
  Serial.println();
  Serial.println();
}

void loop() {
  // Nothing to do
}
