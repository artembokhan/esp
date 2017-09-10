/*********************************************************************
DF ROBOT LCD Keypad Shield �p �t�����L�[�p�b�h�h���C�o

Arduino �W�����C�u������LiquidCrystal��DF ROBOT��Keypad�p�֐���
�ǉ����܂����B

�֘A���
	http://www.geocities.jp/bokunimowakaru/diy/arduino/lcds.html

�{�\�[�X���X�g����у\�t�g�E�F�A��GPL V2�Ɋ�Â����C�Z���X��L���܂��B
���p�A�ҏW�A�Ĕz�z�������R�ɍs���܂����A���쌠�\���̉��ς͋֎~���܂��B

                               Copyright (c) 2012-2017 Wataru KUNINO
                               http://www.geocities.jp/bokunimowakaru/
*********************************************************************/

/*
	�t�@�C���F
		LiquidCrystal.h
		LiquidCrystal.cpp

	�ꏊ(��)�F
		C:\arduino\libraries\LiquidCrystal

*/

/*
LCD��
	Arduino UNO   13 12 11 10  9  8 | 7  6  5  4  3  2  1  0
	DOIT ESPduino NC  1  3 16 15 14 |13 12  5  4  2  0 TX RX

	Arduino�p	LiquidCrystal lcd( 8, 9, 4, 5, 6, 7);  
	ESPduino�p	LiquidCrystal lcd(14,15, 4, 5,12,13);  

	lcd.begin(16, 2);
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("Hello!");

KEY��

	Arduino		int adc_key_in = analogRead(0);
	ESPduino	int adc_key_in = system_adc_read();

	ESPduino���̕�����R�A100k / (100k + 400k)�ŁA
	0�`5V�̓��͂�0�`1V�֕ϊ����Ă���̂ŁA���̂܂ܐڑ��\

	uint8_t buttons = lcd.readButtons();
	
*/

/******************************************************************************/

/*******************************************************************************
�\���E�L�[�p�b�h���͗p�T���v��
*******************************************************************************/

#include "LiquidCrystalDFR.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  // Debugging output
  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  int time = millis();
  lcd.print("Hello, world!");
  time = millis() - time;
  Serial.print("Took "); Serial.print(time); Serial.println(" ms");
}

uint8_t i=0;
void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000);

  uint8_t buttons = lcd.readButtons();

  if (buttons) {
    lcd.clear();
    lcd.setCursor(0,0);
    if (buttons & BUTTON_UP) {
      lcd.print("UP ");
    }
    if (buttons & BUTTON_DOWN) {
      lcd.print("DOWN ");
    }
    if (buttons & BUTTON_LEFT) {
      lcd.print("LEFT ");
    }
    if (buttons & BUTTON_RIGHT) {
      lcd.print("RIGHT ");
    }
    if (buttons & BUTTON_SELECT) {
      lcd.print("SELECT ");
    }
  }
}


/*******************************************************************************
Arduino �p �ύX�_
*******************************************************************************/

/***************************************
LiquidCrystal.h		60�s��
****************************************/

// for button by Wataru
#define BUTTON_UP 0x08
#define BUTTON_DOWN 0x04
#define BUTTON_LEFT 0x10
#define BUTTON_RIGHT 0x02
#define BUTTON_SELECT 0x01

/***************************************
LiquidCrystal.h		106�s��
****************************************/

  uint8_t readButtons();	// Wataru

/***************************************
LiquidCrystal.cpp	327�s�ڂ���
****************************************/

	// Wataru
	/******************************************************

	This program will test the LCD panel and the buttons
	Mark Bramwell, July 2010 

	********************************************************/

	uint8_t LiquidCrystal::readButtons(void) {
	  int adc_key_in = analogRead(0);      // read the value from the sensor
	  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741 
	  // we add approx 50 to those values and check to see if we are close 
	  if (adc_key_in > 1000) return 0x00; // We make this the 1st option for speed reasons since it will be the most likely result 
	  if (adc_key_in < 50)   return BUTTON_RIGHT;
	  if (adc_key_in < 195)  return BUTTON_UP;
	  if (adc_key_in < 380)  return BUTTON_DOWN;
	  if (adc_key_in < 555)  return BUTTON_LEFT;
	  if (adc_key_in < 790)  return BUTTON_SELECT;
	  return 0x1F;  // when all others fail, return this...
	}

/******************************************************************************/
