// A3GS sample sketch.8 -- httpGET with SSL

#include <SoftwareSerial.h>
#include "a3gs2.h"

const char *server = "twitter.com";
const char *path = "";
int port = a3gsDEFAULT_PORT;

char res[a3gsMAX_RESULT_LENGTH+1];
int len;

void setup()
{
  Serial.begin(9600);
  delay(3000);  // Wait for Start Serial Monitor
  Serial.println("Ready.");

  Serial.print("Initializing.. ");
  if (a3gs.start() == 0 && a3gs.begin() == 0) {
    Serial.println("Succeeded.");
    Serial.print("httpGET() requesting.. ");
    len = sizeof(res);
    if (a3gs.httpGET(server, port, path, res, len, true) == 0) {
      Serial.println("OK!");
      Serial.print("[");
      Serial.print(res);
      Serial.println("]");
    }
    else {
      Serial.print("Can't get HTTPS response from ");
      Serial.println(server);
    }
  }
  else
    Serial.println("Failed.");

  Serial.println("Shutdown..");
  a3gs.end();
  a3gs.shutdown();
}

void loop()
{
}
