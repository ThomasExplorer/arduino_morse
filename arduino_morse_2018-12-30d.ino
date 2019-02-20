int dotDelay = 100;
int dashDelay = dotDelay*8;
int BetweenFlashDelay = dotDelay * 3;
int BetweenLetterDelay = dotDelay * 10;
int BetweenWordDelay = dotDelay * 16;
int EndOfMessageDelay = dotDelay * 10;
int FlickerDelay = dotDelay * 10;

int MorseFlashLedPin = 13;
int MessageEndLedPin = 12;
int LetterEndLedPin = 11;

int RotatingSwitchBit0 = 2;
int RotatingSwitchBit1 = 3;
int RotatingSwitchBit2 = 4;
int RotatingSwitchBit3 = 5;

#define MAX_MESSAGES 16

char* letters[] = {
".-",   // A
"-...", // B
"-.-.", // C
"-..",  // D
".",  // E
"..-.", // F 
"--.",  // G
"....", // H
"..",   // I
".---", // J
"-.-",  // K
".-..", // L
"--",   // M
"-.",   // N
"---",  // O
".--.", // P
"--.-", // Q
".-.",  // R 
"...",  // S
"-",  // T
"..-",  // U
"...-", // V 
".--",  // W
"-..-", // X
"-.--", // Y
"--.."  // Z
};
char* numbers[] = {
  "-----", // 0
  ".----", // 1
  "..---", // 2
  "...--", // 3
  "....-", // 4
  ".....", // 5
  "-....", // 6
  "--...", // 7
  "---..", // 8
  "----."};// 9

char* Message[MAX_MESSAGES] = {
  "SOS",        // 0
  "upstairs",   // 1 
  "scout",      // 2
  "hut",        // 3
  "bomb",       // 4
  "add numbers to defuse",// 5
  "123456",     // 6
  "766236",     // 7
  "E",          // 8
  "E",          // 9 
  "E",          // A
  "E",          // B
  "E",          // C
  "E",          // D
  "E",          // E
  "E"           // F
};

void end_of_message()
{
  digitalWrite(MessageEndLedPin, HIGH);
  delay(FlickerDelay);
  digitalWrite(MessageEndLedPin, LOW);
  delay(EndOfMessageDelay);
 }

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(MorseFlashLedPin, HIGH);
  if (dotOrDash == '.')
  {
    delay(dotDelay);
  }
  else 
  {
    delay(dashDelay);
  }
  digitalWrite(MorseFlashLedPin, LOW);
  delay(BetweenFlashDelay); // gap between flashes
}
  
void flashSequence(char* sequence)
{
  int i = 0;
  while (sequence[i] != '\0')
  {
    flashDotOrDash(sequence[i]);
    i++;
  }
  
  delay(BetweenFlashDelay); // gap between flashes
  digitalWrite(LetterEndLedPin, HIGH);
  delay(BetweenFlashDelay); // gap between flashes
  digitalWrite(LetterEndLedPin, LOW);
  delay(BetweenLetterDelay); // gap between letters
  }

void flashMessage(char* message)
{  
  int i = 0;
  while (message[i] != '\0')
  {
    char ch = message[i++];   
    if (ch >= 'a' && ch <= 'z')
    {
      flashSequence(letters[ch - 'a']);
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
      flashSequence(letters[ch - 'A']);
    }
    else if (ch >= '0' && ch <= '9')
    {
      flashSequence(numbers[ch - '0']);
    }
    else if (ch == ' ')
    {
      delay(BetweenWordDelay); // gap between words in message
    }
  }
 end_of_message();  // indicate end of message
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(MorseFlashLedPin, OUTPUT);
  pinMode(MessageEndLedPin, OUTPUT);
  pinMode(LetterEndLedPin, OUTPUT);
  
  pinMode(RotatingSwitchBit0, INPUT_PULLUP);  
  pinMode(RotatingSwitchBit1, INPUT_PULLUP);  
  pinMode(RotatingSwitchBit2, INPUT_PULLUP);  
  pinMode(RotatingSwitchBit3, INPUT_PULLUP);  
}

// the loop function runs over and over again forever
void loop() {
  int i = 0xF & ~ (digitalRead(RotatingSwitchBit0)+
                  (digitalRead(RotatingSwitchBit1)<<1) +
                  (digitalRead(RotatingSwitchBit2)<<2) +
                  (digitalRead(RotatingSwitchBit3)<<3) );
  Serial.println(i);
  Serial.println(" ");
  Serial.println(Message[i]);
  flashMessage(Message[i]);   
}
