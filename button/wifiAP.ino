ESP8266WebServer server(80);

String htmlTemplate = "<!DOCTYPE html> <html> <body> <h2>The BUTTON Configuration Panel</h2><br> <form action=\"/setup\" method=\"post\"> <p> <h3>WiFi settings</h3><br><br> SSID:<br> <input type=\"text\" name=\"ssid\" value=\"SSID_PLACE_HOLDER\"> <br><br> Password:<br> <input type=\"password\" name=\"password\" value=\"PASSWORD_PLACE_HOLDER\"> <br><br> </p> <p> <h3>Button settings (When you push the BUTTON, trigger following request) </h3><br><br> POST:<br> <input type=\"radio\" name=\"post\" value=\"1\" POST_ON_PLACE_HOLDER>ON<br><input type=\"radio\" name=\"post\" value=\"0\" POST_OFF_PLACE_HOLDER>OFF<br><br> Host:<br> https://<input type=\"text\" name=\"host\" value=\"HOST_PLACE_HOLDER\" size=\"92\"> <br><br> Port:<br> <input type=\"text\" name=\"port\" value=\"PORT_PLACE_HOLDER\"> <br><br> URL:<br> <input type=\"text\" name=\"url\" value=\"URL_PLACE_HOLDER\" size=\"100\"> <br><br> JSON:<br> <input type=\"radio\" name=\"json\" value=\"1\" JSON_ON_PLACE_HOLDER>ON<br><input type=\"radio\" name=\"json\" value=\"0\" JSON_OFF_PLACE_HOLDER>OFF<br><br> Body:<br> <textarea name=\"body\" rows=\"10\" cols=\"100\">BODY_PLACE_HOLDER</textarea><br><br></p><input type=\"submit\" value=\"Submit\"></form></body></html>";

String getHTML() {
	String html = htmlTemplate;
	html.replace("SSID_PLACE_HOLDER", getSSID());
	html.replace("PASSWORD_PLACE_HOLDER", getPassword());
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
		setSSID(urldecode(server.arg("ssid")));
		needToReconnect = true;
	}
	
	if (server.hasArg("password")) {
		setPassword(urldecode(server.arg("password")));
		needToReconnect = true;
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

