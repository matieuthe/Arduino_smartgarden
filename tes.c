int relay = 10;  //Pin 10
const int pinHumidity = A0;
int LED = 13;

int sensorValue = 0;
int outputValue = 0;

int mesure = 0;

void setup(){
    Serial.begin(9600);
    pinMode(relay,OUTPUT);    // Define the port attribute as output 
}

void mesureHumidity(){ 
  if(mesure == 0){
    //read the value on the sensor
    sensorValue = analogRead(pinHumidity);
    //adapt the value to send in %
    outputValue = map(sensorValue, 0, 1023, 0, 100);
    Serial.println(outputValue);
    mesure++;
  }else{
    if(mesure < 10) mesure++;
    else mesure = 0;
  }
}

void startTap(){
  digitalWrite(relay,HIGH);   // turn the relay ON

}

void stopTap(){
  digitalWrite(relay,LOW);   // turn the relay ON
}

void checkOrder(){
  if(Serial.available() > 0) {
    char data = Serial.read();
    if(data == '1'){
      startTap();
    }else{
      stopTap();
    }
  }
}

void loop(){
  delay(1000);
  mesureHumidity();
  checkOrder();
}