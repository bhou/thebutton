
void setup() {
  Serial.begin(115200);
  setupPIN();
  setupEEPROM();

	loadSettings();

  welcome();

  setupWiFiAccessPoint();
  //setupWiFiConnection();
  reconnectWiFi();
}

void loop() {
  handleWiFiAP();
	//handleWiFiReconnect();
  checkWiFiStatus();
	handlePushButton();
}


