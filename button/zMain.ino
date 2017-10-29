
void setup() {
  Serial.begin(115200);
  setupPIN();
  setupEEPROM();

	loadSettings();

  welcome();

  setupWiFiAccessPoint();
  setupWiFiConnection();
}

void loop() {
  handleWiFiAP();
	handleWiFiReconnect();
	handlePushButton();
}


