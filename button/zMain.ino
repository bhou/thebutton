
void setup() {
  Serial.begin(115200);
  setupPIN();
  setupEEPROM();
  welcome();
  setupWiFiAccessPoint();
  setupWiFiConnection();
}

void loop() {
  handleWiFiAP();
	handleWiFiReconnect();
	handlePushButton();
}


