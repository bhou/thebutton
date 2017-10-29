// PIN definitions for LED and button
int BUTTON = D1;
int RED = D2;
int YELLOW = D3;
int GREEN = D4;


/* Set these to your desired credentials for access point */
const char *apSSID = "TheButton";
const char *apPassword = "TheButton";

/* setting variables */
String setting_ssid = "";
String setting_password = "";
int setting_triggerDelay = 300;
String setting_host = "thebutton.cc"; 
int setting_port = 443;
String setting_method = "GET"; 
String setting_url = "/test";
bool setting_json = false;
String setting_body = "";

void setupPIN() {
  pinMode(BUTTON, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loadSettings() {
	loadSSID();
	loadPassword();
	loadTriggerDelay();
	loadHost();
	loadPort();
	loadMethod();
	loadURL();
	loadMethod();
	loadIsJSONBody();
	loadRequestBody();
  /*
  Serial.println(setting_ssid);
  Serial.println(setting_password);
  Serial.println(setting_triggerDelay);
  Serial.println(setting_host);
  Serial.println(setting_port);
  Serial.println(setting_method);
  Serial.println(setting_url);
  Serial.println(setting_json);
  Serial.println(setting_body);
  */
}
