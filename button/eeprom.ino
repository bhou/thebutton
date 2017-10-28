// =======================================================
// EEPROM functions 
// =======================================================

/* EEPROM address */
const int SSID_ADDR = 0;
const int PASSWORD_ADDR = 50;

const int HOST_ADDR = 80; // max host length 30
const int PORT_ADDR = 110; // max 6 digital
const int POST_ADDR = 118; // max 1 digital
const int URL_ADDR = 120;	// max url length 192
const int JSON_ADDR = 310;  // max 1 digital
const int BODY_ADDR = 312; // max body length 200 

void setupEEPROM() {
  EEPROM.begin(512);
}

void writeEEPROM(int addr, String value) {
  int len = value.length();
  EEPROM.write(addr, len);
  for (int i = 0; i < len; i++) {
    digitalWrite(RED, LOW);
    EEPROM.write(addr + 1 + i, value.charAt(i));
    delay(100);
    digitalWrite(RED, HIGH);
  }
  EEPROM.commit();
  digitalWrite(RED, LOW);
}

String readEEPROM(int addr) {
  int len = (int) EEPROM.read(addr);
	if (len <= 0 || len >= 300) return "";
  String output = "";
  for (int i = 0; i < len; i++) {
    output += (char)EEPROM.read(addr + 1 + i);
  } 
  return output;
}

void setSSID(String ssid) {
	writeEEPROM(SSID_ADDR, ssid);
}

String getSSID() {
  return readEEPROM(SSID_ADDR);
}

void setPassword(String password) {
	writeEEPROM(PASSWORD_ADDR, password);
}

String getPassword() {
  return readEEPROM(PASSWORD_ADDR);
}

void setHost(String host) {
	writeEEPROM(HOST_ADDR, host);
}

String getHost() {
  return readEEPROM(HOST_ADDR);
}

void setPort(String port) {
	writeEEPROM(PORT_ADDR, port);
}

int getPort() {
	String port = readEEPROM(PORT_ADDR);
	if (port == "") return 443;
  return port.toInt();
}

void setURL(String url) {
	writeEEPROM(URL_ADDR, url);
}

String getURL() {
  return readEEPROM(URL_ADDR);
}

void setRequestBody(String req) {
	writeEEPROM(BODY_ADDR, req);
}

String getRequestBody() {
  return readEEPROM(BODY_ADDR);
}

void setMethod(String method) {
  if (method == "POST") {
    writeEEPROM(POST_ADDR, "1");
  } else {
    writeEEPROM(POST_ADDR, "0");
  }
}

String getMethod() {
  if (readEEPROM(POST_ADDR) == "1") {
    return "POST";
  } else {
    return "GET";
  }
}

void setIsJSONBody(String json) {
  writeEEPROM(JSON_ADDR, json);
}

bool isJSONBody() {
  return readEEPROM(JSON_ADDR) == "1";
}
