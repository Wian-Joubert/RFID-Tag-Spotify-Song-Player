// Code by Wian Joubert

#include <SoftwareSerial.h>
#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);
SoftwareSerial ssrfid = SoftwareSerial(6,8); 

const int BUFFER_SIZE = 14; // RFID DATA FRAME FORMAT: 1byte head (value: 2), 10byte data (2byte version + 8byte tag), 2byte checksum, 1byte tail (value: 3)
const int DATA_TAG_SIZE = 8; // 8byte tag

uint8_t buffer[BUFFER_SIZE]; // Used to store an incoming data
byte buffer_index = 0;

void setup() {
  Serial.begin(9600); 
  ssrfid.begin(9600);
  ssrfid.listen(); 
  u8g2.begin();
  Serial.println(F("    === "));
  Serial.println(F(" INIT DONE"));
  Serial.println(F("    === "));
  displayAwaitingTag();
}

void loop() {
  if (ssrfid.available() > 0){
    bool call_extract_tag = false;
    
    byte ssvalue = ssrfid.read(); // read 

    if (ssvalue == 2) { // RDM630/RDM6300 found a tag => tag incoming 
      buffer_index = 0;
    } else if (ssvalue == 3) { // tag has been fully transmitted       
      call_extract_tag = true; // extract tag at the end of the function call
    }

    if (buffer_index >= BUFFER_SIZE) { // checking for a buffer overflow 
      Serial.println(F("Error: Buffer overflow"));
      return;
    }
    
    buffer[buffer_index++] = ssvalue; // no issues => copy current value to buffer

    if (call_extract_tag == true) {
      if (buffer_index == BUFFER_SIZE) {
        char tagStr[DATA_TAG_SIZE + 1]; // used to store the RFID tag ID
        static char lastTagID[DATA_TAG_SIZE + 1] = ""; // stores the last read tag ID
        extract_tag(tagStr);
        if (strcmp(tagStr, lastTagID) != 0) { // check if the tag ID is different from the last one
          displayTagInfo(tagStr);
          strcpy(lastTagID, tagStr); // update the last tag ID
        }
      } else { // issue occured... start again looking for preamble (value: 2)
        buffer_index = 0;
        return;
      }
    }   
  }
}

void displayAwaitingTag() {
  u8g2.firstPage();
  do {
// Draw the border
u8g2.drawFrame(4, 2, u8g2.getDisplayWidth()-4, u8g2.getDisplayHeight()-4);

// Fill the left and right borders with random dots
for (int i = 0; i < u8g2.getDisplayWidth(); i++) {
  for (int j = 0; j < 2; j++) {
    if (random(2)) { // 50% chance to draw a pixel
      u8g2.drawPixel(i, j); // Top border
      u8g2.drawPixel(i, u8g2.getDisplayHeight() - 1 - j); // Bottom border
    }
  }
}

// Fill the top and bottom borders with random dots
for (int j = 0; j < u8g2.getDisplayHeight(); j++) {
  for (int i = 0; i < 2; i++) {
    if (random(2)) { // 50% chance to draw a pixel
      u8g2.drawPixel(i+2, j); // Left border
      u8g2.drawPixel(u8g2.getDisplayWidth() - i, j); // Right border
    }
  }
}

  // Draw the "Awaiting Tag" message in the middle of the screen
  u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a suitable font
  char displayString[] = "== Awaiting Tag ==";
  u8g2.drawStr((u8g2.getDisplayWidth()-u8g2.getStrWidth(displayString))/2, u8g2.getDisplayHeight()/2+3, displayString);

  } while ( u8g2.nextPage() );
}

void displayTagInfo(char* tagStr) {
  u8g2.firstPage();
  do {
// Draw the border
u8g2.drawFrame(4, 2, u8g2.getDisplayWidth()-4, u8g2.getDisplayHeight()-4);

// Fill the left and right borders with random dots
for (int i = 0; i < u8g2.getDisplayWidth(); i++) {
  for (int j = 0; j < 2; j++) {
    if (random(2)) { // 50% chance to draw a pixel
      u8g2.drawPixel(i, j); // Top border
      u8g2.drawPixel(i, u8g2.getDisplayHeight() - 1 - j); // Bottom border
    }
  }
}

// Fill the top and bottom borders with random dots
for (int j = 0; j < u8g2.getDisplayHeight(); j++) {
  for (int i = 0; i < 2; i++) {
    if (random(2)) { // 50% chance to draw a pixel
      u8g2.drawPixel(i+2, j); // Left border
      u8g2.drawPixel(u8g2.getDisplayWidth() - i, j); // Right border
    }
  }
}

  // Draw the RFID tag info in the middle of the screen
  u8g2.setFont(u8g2_font_ncenB08_tr); // Choose a suitable font
  char displayString[20];
  sprintf(displayString, "Tag ID: %s", tagStr);
  u8g2.drawStr((u8g2.getDisplayWidth()-u8g2.getStrWidth(displayString))/2, u8g2.getDisplayHeight()/2+4, displayString);
  } while ( u8g2.nextPage() );
}

void extract_tag(char* tagStr) {
    uint8_t *msg_data_tag = buffer + 3; // Skip the head and version bytes
    for (int i = 0; i < DATA_TAG_SIZE; ++i) {
      tagStr[i] = msg_data_tag[i];
    }
    tagStr[DATA_TAG_SIZE] = '\0'; // Null-terminate the string

    // Write the tag ID to the serial monitor
    Serial.print(F("Tag ID: "));
    Serial.println(tagStr);
}