// A3GS2 sample sketch.3 -- httpPOST (Use xively.com Colud Service)
//   [[Note]] Replace YOUR_FEED_ID_HERE, CHANNEL_ID and YOUR_API_KEY_HERE with real values, See a3gs's user manual.
//            Insert Temparture Sensor(LM61BIZ) into A0(GND), A1(Vout), A2(VSS+)

#include <SoftwareSerial.h>
#include "a3gs.h"

#define LM61BIZ_Pin 1    // LM61BIZ output pin: A1

const char *server = "176.56.236.75";
const char *path = "safecast/index.php?api_key=q1LKu7RQ8s5pmyxunnDW";
const char *header="";
const int port = a3gsDEFAULT_PORT;
const boolean useHTTPS = false;  // Use https(true) or http(false), xively.com must use https

char res[30];
char body[20]; 
int len;

void setup()
{
  pinMode(A0, OUTPUT);  // A0(LM61BIZ - GND)
  digitalWrite(A0, LOW);
  pinMode(A2, OUTPUT);  // A2(LM61BIZ - VSS+)
  digitalWrite(A2, HIGH);

  Serial.begin(9600);
  delay(3000);  // Wait for Start Serial Monitor
  Serial.println(">Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0)
    Serial.println("Succeeded.");
  else {
    Serial.println("Failed.");
    while (1) ;  // STOP
  }
}

int getTemp(void)  // get temperature(x10 C)
{
  int mV = analogRead(LM61BIZ_Pin) * 4.88;
  return (mV - 600);  
}

void loop()
{
  static int Count = 1;

  Serial.print(">httpPOST requesting: ");
  Serial.println(Count++, DEC);
  len = sizeof(res);
  int temp = getTemp();
  //sprintf(body, "%d.%d", temp/10, temp%10);
  if (a3gs.httpPOST(server, port, path, header, body, res, &len, useHTTPS) == 0) {
    Serial.println("Succeeded.");
    Serial.print(">Response=[");
    Serial.print(res);
    Serial.println("]");
  }
  else
    Serial.println("Failed.");

  delay(15000);  // take an interval
}

// END