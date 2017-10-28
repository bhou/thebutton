// Don't use the fingerprint to verify https response
const char* fingerprint = "CF 05 98 89 CA FF 8E D8 5E 5C E0 C2 E4 F7 E6 C3 C7 50 DD 5C";

void setupWiFiConnection() {
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
	WiFi.disconnect();
  WiFi.begin(getSSID().c_str(), getPassword().c_str());
  unsigned long start = millis();
  unsigned long now = 0;
  bool connected = true;
  while (WiFi.status() != WL_CONNECTED) {
    now = millis();
    if (now - start > 10000) {
      connected = false;
      break;
    }
    digitalWrite(YELLOW, LOW);
    delay(250);
    digitalWrite(YELLOW, HIGH);
    delay(250);
    // Serial.print(".");
  }
  digitalWrite(YELLOW, LOW);
  if (connected) {
    digitalWrite(GREEN, HIGH);
    Serial.print("Successfully connected to wifi network");
  } else {
    digitalWrite(RED, HIGH);
    Serial.print("Failed to connect to wifi network");
  }
}

void handleWiFiReconnect() {
	if (WiFi.status() != WL_CONNECTED) {
    Serial.println("wifi reconnecting");
		setupWiFiConnection();
	}
}

void sendHTTPS(String reqMethod, String host, int httpsPort, String url, String body, bool isJson) {
	// Use WiFiClientSecure class to create TLS connection
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host.c_str(), httpsPort)) {
    Serial.println("connection failed");
    digitalWrite(GREEN, LOW);
		for (int i = 0; i < 10; i++) {
			digitalWrite(RED, HIGH);
			delay(150);
			digitalWrite(RED, LOW);
			delay(150);
		}
		digitalWrite(GREEN, HIGH);
    return;
  }

  if (client.verify(fingerprint, host.c_str())) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  Serial.print("requesting URL: ");
  Serial.println(url);

  digitalWrite(YELLOW, HIGH);
  digitalWrite(GREEN, LOW);
  String request = reqMethod + " " + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Length: " + body.length() + "\r\n" +
               "User-Agent: the BUTTON\r\n" +
               "Connection: close\r\n";
  if (isJson) {
    request += "Content-Type: application/json\r\n";
  }

  request += "\r\n" + body;
     
  client.print(request);

  Serial.println("request sent");
  Serial.println(request);
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  String respBody = client.readString();
  
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(respBody);
  Serial.println("==========");
  Serial.println("closing connection");
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, HIGH);
}

