#include <WiFi.h>
#include <FirebaseESP32.h>
#include <NTPClient.h>
#include <WiFiUdp.h>


const int trigPin = 2;
const int echoPin = 15;

const int LED1 = 22;
const int LED2 = 23;

int duration = 0;
int distance = 0;


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

#define FIREBASE_HOST "https://parking-3d8e1-default-rtdb.europe-west1.firebasedatabase.app/"
#define FIREBASE_AUTH "krcgo6nCyLdC4iPMBGi5zIuaWXQqP11NmsetWnnh"
 
const char* ssid = "Zhone_F758";
const char* password =  "znid310942296";
 

FirebaseData firebaseData;
FirebaseJson json;
 
void setup()
{
  pinMode(trigPin , OUTPUT);
  pinMode(echoPin , INPUT); 
  
  pinMode(LED1 , OUTPUT);
  pinMode(LED2 , OUTPUT);
  
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }
 
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  timeClient.begin();
  timeClient.setTimeOffset(10800);
 
}
 
void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;
  
    
 
    

    if ( distance < 50 )
  {
    digitalWrite(LED1, HIGH);
    json.set("/data", "Ocu");
  Firebase.updateNode(firebaseData,"/Sensor",json);

  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  time_t epochTime = timeClient.getEpochTime();
  json.set("/time", formattedTime);
  Firebase.updateNode(firebaseData,"/Sensor",json);
  json.set("/seconds", epochTime);
  Firebase.updateNode(firebaseData,"/Sensor",json);
  
    
    delay(100);
  }
  else
  {
    digitalWrite(LED1, LOW);
  }
  if ( distance >= 50 )
  {
    digitalWrite(LED2, HIGH);
       json.set("/data", "Avi");
  Firebase.updateNode(firebaseData,"/Sensor",json);

  timeClient.update();
  String formattedTime = timeClient.getFormattedTime();
  time_t epochTime = timeClient.getEpochTime();
  json.set("/time", formattedTime);
  Firebase.updateNode(firebaseData,"/Sensor",json);
  json.set("/seconds", epochTime);
  Firebase.updateNode(firebaseData,"/Sensor",json);
  
 
    delay(100);
  }
  else
  {
    digitalWrite(LED2, LOW);
  }

  delay(100);

  
    
 
    Serial.println("Disconnecting...");
    
 
    delay(2000);
}
