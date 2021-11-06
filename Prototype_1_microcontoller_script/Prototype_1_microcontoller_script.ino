
//variables for where the transducers are going to be placed
int t_1 = 5;
int t_2 = 6;
unsigned long Start_time_1;
unsigned long End_time_1;
unsigned long elaps_1;

void setup() {
  // put your setup code here, to run once:
  pinMode(t_1, OUTPUT);
  pinMode(t_2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  int pulseLength = 10;
  Start_time_1 = micros();
  tone(t_1,40000,0.00001);

  while(digitalRead(t_2)==LOW){
    //Insert code to do more timing here.
    End_time_1 = micros();
    }

  elaps_1 = Start_time_1 - End_time_1; 

  Serial.println(elaps_1);

  delay(1000);

}
