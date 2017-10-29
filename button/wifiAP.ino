ESP8266WebServer server(80);

String htmlTemplate = "<!DOCTYPE html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\"><style>textarea{width:100%}input[type=text],input[type=password]{width:100%}</style></head><body><div><div><h2 style=\"text-align:center;\">The BUTTON Configuration Panel</h2><form action=\"/setup\" method=\"post\"><fieldset><legend style=\"font-size:18px;margin-top:10px;\">WiFi Settings</legend><label>SSID</label><input type=\"text\" name=\"ssid\" placeholder=\"SSID\" value=\"SSID_PLACE_HOLDER\"><br><br><label>Password</label><input type=\"password\" name=\"password\" placeholder=\"Password\" value=\"PASSWORD_PLACE_HOLDER\"></fieldset><fieldset><legend style=\"font-size:18px;margin-top:10px;\">Button settings (When you push the BUTTON, trigger following request)</legend><label>Trigger Delay (ms)</label><input type=\"text\" name=\"trigger_delay\" placeholder=\"trigger delay in millisecond\" value=\"TRIGGER_DELAY_PLACE_HOLDER\"><br><br><label>POST</label><label><input type=\"radio\" name=\"post\" value=\"1\" POST_ON_PLACE_HOLDER> ON<input type=\"radio\" name=\"post\" value=\"0\" POST_OFF_PLACE_HOLDER> OFF</label><br><br><label>Host </label>https://<input class=\"pure-input-1\" type=\"text\" name=\"host\" placeholder=\"host\" value=\"HOST_PLACE_HOLDER\"><br><br><label>Port</label><input type=\"text\" name=\"port\" placeholder=\"port\" value=\"PORT_PLACE_HOLDER\"><br><br><label>URL</label><input type=\"text\" name=\"url\" placeholder=\"URL\" value=\"URL_PLACE_HOLDER\" size=\"90\"><br><br><label>Request on JSON</label><label><input type=\"radio\" name=\"json\" value=\"1\" JSON_ON_PLACE_HOLDER> ON<input type=\"radio\" name=\"json\" value=\"0\" JSON_OFF_PLACE_HOLDER> OFF</label><br><br><label>BODY</label><br><textarea name=\"body\" rows=\"10\">BODY_PLACE_HOLDER</textarea></fieldset><input type=\"submit\" value=\"SAVE\"></form></div></div></body></html>";

String getHTML() {
	String html = htmlTemplate;
  /*
  Serial.println(getSSID());
  Serial.println(getPassword());
  Serial.println(String(getTriggerDelay()));
  Serial.println(getHost());
  Serial.println(getPort());
  Serial.println(getURL());
  Serial.println(getRequestBody());
  Serial.println(getMethod());
  Serial.println(isJSONBody());
  */
  
	html.replace("SSID_PLACE_HOLDER", getSSID());
	html.replace("PASSWORD_PLACE_HOLDER", getPassword());
  html.replace("TRIGGER_DELAY_PLACE_HOLDER", String(getTriggerDelay()));
	html.replace("HOST_PLACE_HOLDER", getHost());
	html.replace("PORT_PLACE_HOLDER", String(getPort()));
	html.replace("URL_PLACE_HOLDER", getURL());
	html.replace("BODY_PLACE_HOLDER", getRequestBody());

  if (getMethod() == "POST") {
    html.replace("POST_ON_PLACE_HOLDER", "checked=\"checked\"");
    html.replace("POST_OFF_PLACE_HOLDER", "");
  } else {
    html.replace("POST_ON_PLACE_HOLDER", "0");
    html.replace("POST_OFF_PLACE_HOLDER", "checked=\"checked\"");
  }

  if (isJSONBody()) {
    html.replace("JSON_ON_PLACE_HOLDER", "checked=\"checked\"");
    html.replace("JSON_OFF_PLACE_HOLDER", "");
  } else {
    html.replace("JSON_ON_PLACE_HOLDER", "");
    html.replace("JSON_OFF_PLACE_HOLDER", "checked=\"checked\"");
  }

	return html;
}

void setupWiFiAccessPoint() {
  Serial.println();
  Serial.print("Configuring access point...");

  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(apSSID, apPassword);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/setup", handleSettingRequest);
  server.begin();
  Serial.println("HTTP server started");
}

/* 
 * GET http://192.168.4.1 with header password as the new password
 */
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void returnFail(String msg)
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(500, "text/plain", msg + "\r\n");
}

void returnOK()
{
  server.sendHeader("Connection", "close");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "OK\r\n");
}

void handleSettingRequest() {
	bool needToReconnect = false;
	if (server.hasArg("ssid")) {
    if (server.arg("ssid") != getSSID()) {
		  setSSID(urldecode(server.arg("ssid")));
		  needToReconnect = true;
    }
	}
	
	if (server.hasArg("password")) {
    if (server.arg("password") != getPassword()) {
		  setPassword(urldecode(server.arg("password")));
		  needToReconnect = true;
    }
	}

  if (server.hasArg("trigger_delay")) {
    setTriggerDelay(server.arg("trigger_delay"));
  }

  if (server.hasArg("post")) {
    if (server.arg("post") == "1") {
      setMethod("POST");
    } else {
      setMethod("GET");
    }
  }

  if (server.hasArg("json")) {
    setIsJSONBody(server.arg("json"));
  }

	if (server.hasArg("host")) {
		setHost(urldecode(server.arg("host")));
	}
	
	if (server.hasArg("url")) {
		setURL(urldecode(server.arg("url")));
	}
	
	if (server.hasArg("port")) {
		setPort(server.arg("port"));
	}

	if (server.hasArg("body")) {
		setRequestBody(urldecode(server.arg("body")));
	}

	returnOK();

	if (needToReconnect) {
		setupWiFiConnection();
	}
}

void handleWiFiAP() {
  server.handleClient();
}

