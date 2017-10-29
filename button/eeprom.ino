// =======================================================
// EEPROM functions 
// =======================================================

/* EEPROM address */
const int SSID_ADDR = 0;	// max ssid length 18
const int PASSWORD_ADDR = 50; // max password 16

const int TRIGGER_DELAY_ADDIR = 68; // max trigger millisecond 6 digital

const int HOST_ADDR = 80; // max host length 28 
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

String readEEPROM(int addr, int maxlen) {
  int len = (int) EEPROM.read(addr);
	if (len <= 0 || len > maxlen) return "";
  String output = "";
  for (int i = 0; i < len; i++) {
    output += (char)EEPROM.read(addr + 1 + i);
  } 
  return output;
}

void setSSID(String ssid) {
	writeEEPROM(SSID_ADDR, ssid);
	setting_ssid = ssid;
}
String getSSID() {
	return setting_ssid;
}
String loadSSID() {
	setting_ssid = readEEPROM(SSID_ADDR, 18);
	return setting_ssid;
}

void setPassword(String password) {
	writeEEPROM(PASSWORD_ADDR, password);
	setting_password = password;
}
String getPassword() {
	return setting_password;
}
String loadPassword() {
	setting_password = readEEPROM(PASSWORD_ADDR, 16);
	return setting_password;
}

void setHost(String host) {
	writeEEPROM(HOST_ADDR, host);
	setting_host = host;
}
String getHost() {
	return setting_host;
}
String loadHost() {
	setting_host = readEEPROM(HOST_ADDR, 28);
	return setting_host;
}

void setPort(String port) {
	writeEEPROM(PORT_ADDR, port);
	if (port == "") {
		setting_port = 443;
	} else {
		setting_port = port.toInt();	
	}
}
int getPort() {
	return setting_port;
}
int loadPort() {
	String port = readEEPROM(PORT_ADDR, 6);
	if (port == "") {
		setting_port = 443;
	} else {
		setting_port = port.toInt();	
	}
	return setting_port;
}

void setTriggerDelay(String triggerDelay) {
	writeEEPROM(TRIGGER_DELAY_ADDIR, triggerDelay);
	if (triggerDelay == "") {
		setting_triggerDelay = 300;
	} else {
		setting_triggerDelay = triggerDelay.toInt();	
	}
}
int getTriggerDelay() {
	return setting_triggerDelay;
}
int loadTriggerDelay() {
	String triggerDelay = readEEPROM(TRIGGER_DELAY_ADDIR, 6);
	if (triggerDelay == "") {
		setting_triggerDelay = 300;
	} else {
		setting_triggerDelay = triggerDelay.toInt();
	}
	return setting_triggerDelay;
}

void setURL(String url) {
	writeEEPROM(URL_ADDR, url);
	setting_url = url;
}
String getURL() {
  return setting_url; 
}
String loadURL() {
	setting_url = readEEPROM(URL_ADDR, 192);
  return setting_url;
}

void setRequestBody(String req) {
	writeEEPROM(BODY_ADDR, req);
	setting_body = req;
}
String getRequestBody() {
	return setting_body;
}
String loadRequestBody() {
	setting_body = readEEPROM(BODY_ADDR, 200);
  return setting_body;
}

void setMethod(String method) {
  if (method == "POST") {
    writeEEPROM(POST_ADDR, "1");
		setting_method = "POST";
  } else {
    writeEEPROM(POST_ADDR, "0");
		setting_method = "GET";
  }
}
String getMethod() {
	return setting_method;
}
String loadMethod() {
	String method = readEEPROM(POST_ADDR, 1);
	if (method == "1") {
		setting_method = "POST";
	} else {
		setting_method = "GET";
	}
	return setting_method;
}


void setIsJSONBody(String json) {
  writeEEPROM(JSON_ADDR, json);
	if (json == "1") {
		setting_json = true;
	} else {
		setting_json = false;
	}
}
bool isJSONBody() {
	return setting_json;
}
bool loadIsJSONBody() {
	String json = readEEPROM(JSON_ADDR, 1);
	if (json == "1") {
		setting_json = true;
	}	else {
		setting_json = false;
	}
	return setting_json;
}
