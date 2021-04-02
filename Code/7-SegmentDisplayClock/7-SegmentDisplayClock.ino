#include <WiFi.h>
#include <WebServer.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>

const char* ssid = "COMHEM_674d69";
const char* password = "zwz2cdqt";

//Time
/*****************************/

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String timeStamp;
const int timeCheckInterval = 1000 * 10;
unsigned long previousTimeCheck = 0;
char minuteCheck;
bool updateTime = 0;

// 7-Segment display
/*****************************/
#include "SevenSegmentClock.h"
#include "ServoCalibrationValues.h"
uint8_t togglePin = 19;
bool updateSegments = 0;
SevenSegment segment_1(0x40, 6, segment1_A, 5, segment1_B, 4, segment1_C, 3, segment1_D, 2, segment1_E, 1, segment1_F, 0, segment1_G);//, togglePin);
SevenSegment segment_2(0x40, 15, segment2_A, 14, segment2_B, 13, segment2_C, 12, segment2_D, 11, segment2_E, 10, segment2_F, 9, segment2_G);//, togglePin);

SevenSegment segment_3(0x41, 0, segment3_A, 1, segment3_B, 2, segment3_C, 3, segment3_D, 4, segment3_E, 5, segment3_F, 7, segment3_G);//, togglePin);
SevenSegment segment_4(0x41, 6, segment4_A, 10, segment4_B, 11, segment4_C, 15, segment4_D, 14, segment4_E, 13, segment4_F, 12, segment4_G);//, togglePin);
/*
  String incomingString = "8";
  char ch = '8';
  String allCharacter = "0123456789ABCDEFGHIJLNOPQRSTUY-* ";
*/
/*****************************/

//Get temperature & Humidity

const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=Stockholm,se&units=metric&APPID=";
const String key = "2fdf3f48acf0e047df5496be5d37239c";
const int humidTempCheckInterval = 1000 * 60 * 10;
unsigned long previoushumidTempCheck = 0;
String humidity;
String temperature;
String payload;

// WebServer
/*************************/
WebServer server(80);

bool TIME_status = LOW;
bool TEMP_status = LOW;
bool TIMER_status = LOW;
bool HUMID_status = LOW;

bool updateHumid = 0;
bool updateTemp = 0;
/*************************/

void getTime();
void connectToWifi();

void setup() {
  Serial.begin(115200);

  //Time
  /*****************************/
  connectToWifi();
  /*****************************/
  // 7-Segment display
  /*****************************/
  pinMode(togglePin, OUTPUT);
  digitalWrite(togglePin, LOW);

  delay(1000);
  segment_1.initialize();
  segment_2.initialize();
  segment_3.initialize();
  segment_4.initialize();
  delay(1000);
  segment_1.writeCharacter(' ');
  delay(500);
  segment_2.writeCharacter(' ');
  delay(500);
  segment_3.writeCharacter(' ');
  delay(500);
  segment_4.writeCharacter(' ');
  delay(500);
  digitalWrite(togglePin, HIGH);
  /*****************************/


  initializeWebserver();
  //Get Temperature & Humidity
    payload = getHumidTemp();
    temperature = getData(payload,"temp");
    humidity = getData(payload,"humidity");
    updateHumid = 1;
    updateTemp = 1;
 

  
  timeClient.begin();
  timeClient.setTimeOffset(2 * 3600);
  getTime();
  updateTime = 1;
  updateSegments = 1;
  minuteCheck = timeStamp[4];
}

void loop() {
  if (millis() - previousTimeCheck >= timeCheckInterval) {
    previousTimeCheck = millis();
    getTime();
    if (minuteCheck != timeStamp[4]) {
      minuteCheck = timeStamp[4];
      updateTime = 1;
      updateSegments = 1;
    }
  }

  if (millis() - previoushumidTempCheck >= humidTempCheckInterval) {
    previoushumidTempCheck = millis();
    payload = getHumidTemp();
    temperature = getData(payload, "temp");
    humidity = getData(payload, "humidity");
    updateSegments = 1;
  }

  server.handleClient();
  if (TIME_status) {
    //Get current time
    //Write Time to Seg
    if (updateTime) {
      getTime();
      updateTime = 0;
    }
    if (updateSegments) {
      Serial.println("Updating Segments");
      digitalWrite(togglePin, LOW);
      segment_1.writeCharacter(timeStamp[0]);
      delay(500);
      segment_2.writeCharacter(timeStamp[1]);
      delay(500);
      segment_3.writeCharacter(timeStamp[3]);
      delay(500);
      segment_4.writeCharacter(timeStamp[4]);
      Serial.print(timeStamp[0]); Serial.print(timeStamp[1]);
      Serial.print(":");
      Serial.print(timeStamp[3]); Serial.println(timeStamp[4]);
      delay(500);
      digitalWrite(togglePin, HIGH);
      updateSegments = 0;
    }
  }
  else if (TEMP_status) {
    //Get current Temp
    //Write Temp to Seg
    updateTemp = 0;
    if (updateSegments) {
      Serial.println("Updating Segments");
      digitalWrite(togglePin, LOW);
      segment_1.writeCharacter(temperature[0]);
      delay(500);
      segment_2.writeCharacter(temperature[1]);
      delay(500);
      segment_3.writeCharacter('*');
      delay(500);
      segment_4.writeCharacter('C');
      delay(500);
      digitalWrite(togglePin, HIGH);
      Serial.print("Temperature "); Serial.print(temperature); Serial.println(" *C");
      updateSegments = 0;
    }
  }
  /*
    else if (TIMER_status) {
    //Start timer
    }
  */
  else if (HUMID_status) {
    //Get humidity
    //Write Humid to Seg
    if (updateSegments) {
      Serial.println("Updating Segments");
      digitalWrite(togglePin, LOW);
      segment_1.writeCharacter(humidity[0]);
      delay(500);
      segment_2.writeCharacter(humidity[1]);
      delay(500);
      segment_3.writeCharacter('*');
      delay(500);
      segment_4.writeCharacter('o');
      delay(500);
      digitalWrite(togglePin, HIGH);
      Serial.print("Humidity "); Serial.print(humidity); Serial.println(" %");
      updateSegments = 0;
    }
  } else {
    //Something default
  }
}

void connectToWifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //if (MDNS.begin("esp32")) {
  //  Serial.println("MDNS responder started");
  //}
}

void getTime() {
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  String formattedDate = timeClient.getFormattedDate();
  int splitT = formattedDate.indexOf("T");
  // Extract time
  timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
}

String getHumidTemp() {
  HTTPClient http;

  http.begin(endpoint + key); //Specify the URL
  int httpCode = http.GET();  //Make the request
  String payload = http.getString();
  return payload;

}

String getData(String payLoad, String searchedWord) {
  char targetEnd = ',';

  int payLoadLength = payLoad.length();
  int searchedWordLength = searchedWord.length();

  int i, j, k;
  i = j = k = 0;
  bool found = 0;
  for (i = 0; i < payLoadLength; i++) {
    if (payLoad[i] == searchedWord[j]) {
      j++;
      if (j == searchedWordLength) {
        found = !found;
        break;
      }
    } else {
      j = 0;
    }
  }

  if (found) {
    String dataString = "";
    while (payLoad[i + 3 + k] != targetEnd) {
      dataString += payLoad[i + 3 + k];
      k++;
    }
    Serial.println(dataString);
    return dataString;
  } else {
    return "";
  }

}

void initializeWebserver() {

  server.on("/", handle_OnConnect);
  server.on("/TimeON", handle_Time_ON);
  server.on("/TimeOFF", handle_Time_OFF);
  server.on("/TemperatureON", handle_Temperature_ON);
  server.on("/TemperatureOFF", handle_Temperature_OFF);
  server.on("/HumidityON", handle_Humidity_ON);
  server.on("/HumidityOFF", handle_Humidity_OFF);
  server.on("/TimerON", handle_Timer_ON);
  server.on("/TimerOFF", handle_Timer_OFF);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void handle_OnConnect() {
  TIME_status = LOW;
  TEMP_status = LOW;
  TIMER_status = LOW;
  HUMID_status = LOW;
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Time_ON() {
  TIME_status = HIGH;
  TEMP_status = LOW;
  TIMER_status = LOW;
  HUMID_status = LOW;
  Serial.println("Time Status: ON");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Time_OFF() {
  TIME_status = LOW;
  Serial.println("Time Status: OFF");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Temperature_ON() {
  TIME_status = LOW;
  TEMP_status = HIGH;
  TIMER_status = LOW;
  HUMID_status = LOW;
  Serial.println("Temperature Status: On");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Temperature_OFF() {
  TEMP_status = LOW;
  Serial.println("Temperature Status: OFF");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Humidity_ON() {
  TIME_status = LOW;
  TEMP_status = LOW;
  TIMER_status = LOW;
  HUMID_status = HIGH;
  Serial.println("Humidity Status: On");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Humidity_OFF() {
  HUMID_status = LOW;
  Serial.println("Humidity Status: OFF");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}


void handle_Timer_ON() {
  TIME_status = LOW;
  TEMP_status = LOW;
  TIMER_status = HIGH;
  HUMID_status = LOW;
  Serial.println("Timer Status: On");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_Timer_OFF() {
  TIMER_status = LOW;
  Serial.println("Timer Status: OFF");
  server.send(200, "text/html", SendHTML(TIME_status, TEMP_status, TIMER_status, HUMID_status));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t TIME, uint8_t TEMP, uint8_t TIMER, uint8_t HUMIDITY) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #FF0000;}\n";
  ptr += ".button-on:active {background-color: #2980b9;}\n";
  ptr += ".button-off {background-color: #008000;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";

  /*
    ptr += ".slidecontainer {width: 100%}";
    ptr += ".slider {-webkit-appearance: none;";
    ptr += "width: 50%;";
    ptr += "height: 25px;";
    ptr += "background: #d3d3d3;";
    ptr += "outline: none;";
    ptr += "opacity: 0.7;";
    ptr += "-webkit-transition: .2s;";
    ptr += "transition: opacity .2s;";
    ptr += "}";
    ptr += ".slider:hover {opacity: 1}";
    ptr += ".slider::-webkit-slider-thumb {";
    ptr += "-webkit-appearance: none;";
    ptr += "width: 25px;";
    ptr += "height: 25px;";
    ptr += "background: #4CAF50;";
    ptr += "cursor: pointer;";
    ptr += "}";
    ptr += ".slider::-moz-range-thumb {";
    ptr += "width: 25px;";
    ptr += "height: 25px;";
    ptr += "background: #4CAF50;";
    ptr += "cursor: pointer;";
    ptr += "}";
  */

  ptr += "</style>\n";


  ptr += "</head>\n";




  ptr += "<body>\n";
  ptr += "<h1>7-Segment Display Controller</h1>\n";
  ptr += "<h3>by Philip Hamilton</h3>\n";

  if (TIME)
  {
    //ptr += "<p>Time Status: ON</p><a class=\"button button-off\" href=\"/TimeOFF\">ON</a>\n";
    ptr += "<a class=\"button button-off\" href=\"/TimeOFF\">Time</a>\n";
  }
  else
  {
    //ptr += "<p>Time Status: OFF</p><a class=\"button button-on\" href=\"/TimeON\">OFF</a>\n";
    ptr += "<a class=\"button button-on\" href=\"/TimeON\">Time</a>\n";
  }

  if (TEMP)
  {
    //ptr += "<p>Temp Status: ON</p><a class=\"button button-off\" href=\"/TemperatureOFF\">ON</a>\n";
    ptr += "<a class = \"button button-off\" href=\"/TemperatureOFF\">Temp</a>\n";
  }
  else
  {
    //ptr += "<p>Temp Status: OFF</p><a class=\"button button-on\" href=\"/TemperatureON\">OFF</a>\n";
    ptr += "<a class=\"button button-on\" href=\"/TemperatureON\">Temp</a>\n";
  }
  if (HUMIDITY)
  {
    //ptr += "<p>Humidity Status: ON</p><a class=\"button button-off\" href=\"/HumidityOFF\">ON</a>\n";
    ptr += "<a class=\"button button-off\" href=\"/HumidityOFF\">Humidity</a>\n";
  }
  else {
    //ptr += "<p>Humidity Status: OFF</p><a class=\"button button-on\" href=\"/HumidityON\">OFF</a>\n";
    ptr += "<a class=\"button button-on\" href=\"/HumidityON\">Humidity</a>\n";
  }
  /*
    if (TIMER)
    {
    //ptr += "<p>Timer Status: ON</p><a class=\"button button-off\" href=\"/TimerOFF\">ON</a>\n";
    ptr += "<a class=\"button button-off\" href=\"/TimerOFF\">Timer</a>\n";
    }
    else
    {
    //ptr += "<p>Timer Status: OFF</p><a class=\"button button-on\" href=\"/TimerON\">OFF</a>\n";
    ptr += "<a class=\"button button-on\" href=\"/TimerON\">Timer</a>\n";
    }

    ptr += "<div class='slidecontainer'>";
    ptr += "<p>Custom range slider:</p>";
    ptr += "<input type='range' min='1' max='100' value='50' class='slider' id='myRange'>";
    ptr += "</div>";
  */

  updateSegments = 1;

  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
