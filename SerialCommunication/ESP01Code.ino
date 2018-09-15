 
void setup()
{
 Serial.begin(9600);
}
void loop(){
    Serial.write("Hello from ESP");
    delay(2000);
 
 }
