/*  Code created by alexELArte github.com
 *  
 *  You can easily change your crypo method in
 *  encode() but you need to change it already in
 *  decode() in the reverse way.
 */


// Length of the message
const byte keylen = 32;

// Random number create with 'randomKey'
// Key for char
const byte Ckey[36] = {162, 226, 138, 2, 240, 71, 242,
                       56, 42, 232, 244, 105, 95, 52, 205, 113,
                       178, 184, 127, 224, 32, 183, 126, 21, 249,
                       72, 43, 88, 92, 128, 144, 197, 99, 151, 20
                       , 39
                      };
// Key for the message
const byte Mkey[keylen] = {13, 27, 25, 10, 3, 26, 8, 19,
                       15, 12, 22, 29, 6, 30, 9, 21, 20, 14, 23,
                       4, 17, 1, 16, 24, 28, 31, 7, 11, 2, 0, 5,
                       18
                      };
byte msg1[keylen];

byte state = 0;
#include "function.h"
void setup() {
  // Initialize serial and random
  Serial.begin(115200);
  randomSeed(analogRead(A0));
  
}

void loop() {
  if (Serial.available() && state < keylen) {
    msg1[state] = Serial.read();
    state++;
    if(msg1[state] == '\n') state = keylen;
  }
  // If the message is full or it is the end:
  if (state == keylen) {
    state = 0;
    Serial.println("Encoding string");
    // Encode
    encode();
    // Print the encoded message
    for (byte i = 0; i < keylen; i++) {
      Serial.print(msg1[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println("Decoding string");
    // Decode
    decode();
    // Print the decoded message
    for (byte i = 0; i < keylen; i++) {
      Serial.print(char(msg1[i]));
    }
    Serial.println();
  }
}

void encode() {
  // Encode char 
  encodeC(&msg1[0], Ckey);
  // Add a mask to add a security
  encodeB(&msg1[0]);
  // Move each number
  encodeM(&msg1[0], Mkey);
  encodeB(&msg1[0]);
}
void decode() {
  // Do the same thing in reverse
  decodeB(&msg1[0]);
  decodeM(&msg1[0], Mkey);
  decodeB(&msg1[0]);
  decodeC(&msg1[0], Ckey);
  
}
