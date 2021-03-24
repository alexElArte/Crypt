void encodeC(byte *_msg, byte _ckey[36]) {
  for (byte i = 0; i < keylen; i++) {
    // Test if it's a char or a number or another
    if ((_msg[i] >= 0x61) && (_msg[i] <= 0x7A)) {//a-z
      _msg[i] -= 97;
      _msg[i] = _ckey[_msg[i]];
    }
    else if ((_msg[i] >= 0x30) && (_msg[i] <= 0x39)) {//0-9
      _msg[i] -= 22;
      _msg[i] = _ckey[_msg[i]];
    } else {
      // If it's other change it to a random number
      bool test = false;
      byte key;
      // Test if the number is not a key
      while (test == false) {
        key = random(256);
        test = true;
        for (byte j = 0; j < 36; j++) {
          if (_ckey[j] == key) {
            test = false;
            break;
          }
        }
      }
      _msg[i] = key;
    }
  }
}
void decodeC(byte *_msg, byte _ckey[36]) {
  // Decode for each byte of the message
  for (byte i = 0; i < keylen; i++) {
    bool test = false;
    // Search the number in the key
    for (byte j = 0; j < 36; j++) {
      if (_ckey[j] == _msg[i]) {
        test = true;
        _msg[i] = j;
        break;
      }
    }
    if (test == true) {
      // Change the number into an ascii char
      // For more information look at the values of the char in the ascii table
      if (_msg[i] <= 25) {
        _msg[i] += 75;
      }
      if (_msg[i] >= 26) {
        _msg[i] += 22;
      }
    } else {
      // If it's an other number change it to a space
      _msg[i] = 0x20;
    }
  }
}

void encodeM(byte *_msg, byte _mkey[32]) {
  byte _msg1[32];
  // Put the datas in a temporary variable
  for (byte i = 0; i < keylen; i++) {
    _msg1[i] = _msg[i];
  }
  // Change the place of each data
  // For more information see the README file
  for (byte i = 0; i < keylen; i++) {
    _msg[_mkey[i]] = _msg1[i];
  }
}
void decodeM(byte *_msg, byte _mkey[keylen]) {
  byte _msg1[32];
  // Put the datas in a temporary variable
  for (byte i = 0; i < 32; i++) {
    _msg1[i] = _msg[i];
  }
  // Do the same thing in reverse
  // See above to compare
  for (byte i = 0; i < 32; i++) {
    _msg[i] = _msg1[_mkey[i]];
  }
}

// Use mask to change data
void encodeB(byte *_msg) {
  // For more information see the README file
  for (byte i = 1; i < keylen; i++) {
    _msg[i] ^= _msg[i-1];
  }
  _msg[0] ^= _msg[31];
}
void decodeB(byte *_msg) {
  // Do the same thing as above in reverse
  _msg[0] ^= _msg[keylen-1];
  for (byte i = keylen-1; i > 0; i--) {
    _msg[i] ^= _msg[i-1];
  }
}
