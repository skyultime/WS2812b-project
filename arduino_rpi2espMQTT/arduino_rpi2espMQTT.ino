// Loading the ESP8266WiFi library and the PubSubClient library
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

// An IR detector/demodulator is connected to GPIO pin 14(D5 on a NodeMCU
// board).
const uint16_t kRecvPin = 14;

IRrecv irrecv(kRecvPin);
 
decode_results results;

// Change the credentials below, so your ESP8266 connects to your router
const char* ssid = "gs7_al";
const char* password = "morphisme";

// Change the variable to your Raspberry Pi IP address, so it connects to your MQTT broker
const char* mqtt_server = "192.168.43.68";

// Initializes the espClient
WiFiClient espClient;
PubSubClient client(espClient);

// Connect an LED to each GPIO of your ESP8266
const int ledGPIO4 = 4;

boolean entrance = true;

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions is executed when some device publishes a message to a topic that your ESP8266 is subscribed to
// Change the function below to add logic to your program, so when a device publishes a message to a topic that 
// your ESP8266 is subscribed you can actually do something
void callback(String topic, byte* message, unsigned int length) {
   Serial.println();
  //Serial.print("Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT
  // If a message is received on the topic home/office/esp1/gpio2, you check if the message is either 1 or 0. Turns the ESP GPIO according to the message
  if(topic=="esp8266/ws2812b"){
      Serial.print(messageTemp);
      digitalWrite(ledGPIO4, HIGH);
  }
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
     /*
     YOU  NEED TO CHANGE THIS NEXT LINE, IF YOU'RE HAVING PROBLEMS WITH MQTT MULTIPLE CONNECTIONS
     To change the ESP device ID, you will have to give a unique name to the ESP8266.
     Here's how it looks like now:
       if (client.connect("ESP8266Client")) {
     If you want more devices connected to the MQTT broker, you can do it like this:
       if (client.connect("ESPOffice")) {
     Then, for the other ESP:
       if (client.connect("ESPGarage")) {
      That should solve your MQTT multiple connections problem

     THE SECTION IN loop() function should match your device name
    */
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
      // Subscribe or resubscribe to a topic
      // You can subscribe to more topics (to control more LEDs in this example)
      client.subscribe("esp8266/ws2812b");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void receiveRemoteCmd(){
  switch(results.value){
    case 0xF7C03F:
      Serial.println("A=101");
      break;
    case 0xF740BF:
      Serial.println("A=102");
      break;
    case 0xF700FF:
      Serial.println("L=100");
      break;
    case 0xF7807F:
      Serial.println("L=000");
      break;
    case 0xF720DF:
      Serial.println("C=0xff0000");
      break;    
    case 0xF7A05F :
      Serial.println("C=0x00ff00");
      break;     
    case 0xF7609F :
      Serial.println("C=0x0000ff");
      break;
   case 0xF7E01F :
      Serial.println("C=0xffffff");
      break;
   case 0xF7D02F :
      Serial.println("A=103");
      break;
   case 0xF7F00F :
      Serial.println("A=107");
      break;
   case 0xF7C837 :
      Serial.println("A=353");
      break;            
   case 0xF7E817 :
      Serial.println("A=211");
      break;
   default:
      break;
  }
}

// The setup function sets your ESP GPIOs to Outputs, starts the serial communication at a baud rate of 115200
// Sets your mqtt broker and sets the callback function
// The callback function is what receives messages and actually controls the LEDs
void setup() {
  Serial.begin(115200);
  //pinMode(ledGPIO4, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
   while (!Serial)  // Wait for the serial connection to be establised.
    delay(50);
  Serial.println();
  Serial.print("IRrecvDemo is now running and waiting for IR message on Pin ");
  Serial.println(kRecvPin);
 /* setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  */
}

// For this project, you don't need to change anything in the loop function. 
// Basically it ensures that you ESP is connected to your broker
void loop() {
   if (irrecv.decode(&results)) {
    //serialPrintUint64(results.value, HEX);
    //Serial.println("");
    irrecv.resume();  // Receive the next value
    receiveRemoteCmd();
  }
  delay(200);
  
  /*
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    
    client.connect("ESP8266Client");*/
}
