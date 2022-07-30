#define SIZE_OF_BUFFER 35

int DS_pin_1 = 4;
int STCP_pin_1 = 3;
int SHCP_pin_1 = 2;
int DS_pin_2 = 6;
int STCP_pin_2 = 7;
int SHCP_pin_2 = 9;
int button_1 = 10;

int buffer_1 [SIZE_OF_BUFFER] = {};
int check = false;
int counter1 = 0;

int segment_1_digit_1 = 0;
int segment_1_digit_2 = 0;
int segment_2_digit_1 = 0;
int segment_2_digit_2 = 0;

int digits[10][8] = { {0, 1, 1, 1, 1, 1, 1, 0},
                      {1, 0, 1, 1, 0, 0, 0, 0},
                      {0, 1, 1, 0, 1, 1, 0, 1},
                      {0, 1, 1, 1, 1, 0, 0, 1},
                      {0, 0, 1, 1, 0, 0, 1, 1},
                      {0, 1, 0, 1, 1, 0, 1, 1},
                      {0, 1, 0, 1, 1, 1, 1, 1},
                      {0, 1, 1, 1, 0, 0, 0, 0},
                      {0, 1, 1, 1, 1, 1, 1, 1},
                      {0, 1, 1, 1, 1, 0, 1, 1},
                  };
//int dec_digits[10] = {1, 79, 18, 6, 76, 36, 32, 15, 0, 4};
int dec_digits[10] = {3, 159, 37, 13, 153, 73, 65, 31, 1, 9};

void setup() {
  // put your setup code here, to run once:
  pinMode(DS_pin_1, OUTPUT);
  pinMode(STCP_pin_1, OUTPUT);
  pinMode(SHCP_pin_1, OUTPUT);

  pinMode(DS_pin_2, OUTPUT);
  pinMode(STCP_pin_2, OUTPUT);
  pinMode(SHCP_pin_2, OUTPUT);

  pinMode(button_1, INPUT);

 //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

int value_btn_1 = digitalRead(button_1);

counter1, check = get_count(value_btn_1, check);

counter1 = counter1 % 100;

segment_1_digit_2 = counter1 % 10;
segment_1_digit_1 = int(counter1 / 10);

//Serial.println("Logic: " + String(value_btn_1) + "\tCounter: " + String(counter));
//Serial.println(String(segment_1_digit_1) + " " + String(segment_1_digit_2));

Display_2_Digit(DS_pin_1, STCP_pin_1, SHCP_pin_1, dec_digits[segment_1_digit_1], dec_digits[segment_1_digit_2]);
//Display_2_Digit(DS_pin_2, STCP_pin_2, SHCP_pin_2, dec_digits[5], dec_digits[2]);
  
}

int get_count(int logic_val, int check) {
  if (logic_val == 1) {
    if (!check) {
      counter1 ++;
      check = true;  
    }
  } else {
      check = false;
    }
  return counter1, check;
}

void Display_2_Digit(int DS_pin, int STCP_pin, int SHCP_pin, int digit1, int digit2) {
  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin, SHCP_pin, MSBFIRST, 0b00000010);
  shiftOut(DS_pin, SHCP_pin, LSBFIRST, digit1);
  digitalWrite(STCP_pin, HIGH);

  digitalWrite(STCP_pin, LOW);
  shiftOut(DS_pin, SHCP_pin, MSBFIRST, 0b00000001);
  shiftOut(DS_pin, SHCP_pin, LSBFIRST, digit2);
  digitalWrite(STCP_pin, HIGH);
}

/*
void DisplayDigit(int Digit) {
  digitalWrite(STCP_pin, LOW);
  for(int i=7; i>=0; i--) {
    digitalWrite(SHCP_pin, LOW);
    if (digits[Digit][i]==1) digitalWrite(DS_pin, LOW); 
    if (digits[Digit][i]==0) digitalWrite(DS_pin, HIGH);
    digitalWrite(SHCP_pin, HIGH);  
  } 
  digitalWrite(STCP_pin, HIGH); 
}
*/
