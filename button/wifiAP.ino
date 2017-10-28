ESP8266WebServer server(80);

// String htmlTemplate_ = "<!DOCTYPE html> <html> <body> <h2>The BUTTON Configuration Panel</h2><br> <form action=\"/setup\" method=\"post\"> <p> <h3>WiFi settings</h3><br><br> SSID:<br> <input type=\"text\" name=\"ssid\" value=\"SSID_PLACE_HOLDER\"> <br><br> Password:<br> <input type=\"password\" name=\"password\" value=\"PASSWORD_PLACE_HOLDER\"> <br><br> </p> <p> <h3>Button settings (When you push the BUTTON, trigger following request) </h3><br><br> POST:<br> <input type=\"radio\" name=\"post\" value=\"1\" POST_ON_PLACE_HOLDER>ON<br><input type=\"radio\" name=\"post\" value=\"0\" POST_OFF_PLACE_HOLDER>OFF<br><br> Host:<br> https://<input type=\"text\" name=\"host\" value=\"HOST_PLACE_HOLDER\" size=\"92\"> <br><br> Port:<br> <input type=\"text\" name=\"port\" value=\"PORT_PLACE_HOLDER\"> <br><br> URL:<br> <input type=\"text\" name=\"url\" value=\"URL_PLACE_HOLDER\" size=\"100\"> <br><br> JSON:<br> <input type=\"radio\" name=\"json\" value=\"1\" JSON_ON_PLACE_HOLDER>ON<br><input type=\"radio\" name=\"json\" value=\"0\" JSON_OFF_PLACE_HOLDER>OFF<br><br> Body:<br> <textarea name=\"body\" rows=\"10\" cols=\"100\">BODY_PLACE_HOLDER</textarea><br><br></p><input type=\"submit\" value=\"Submit\"></form></body></html>";
String htmlTemplate = "<!DOCTYPE html><html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1252\"><style>img,legend{border:0}legend,td,th{padding:0}html{font-family:sans-serif;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}body{margin:0}article,aside,details,figcaption,figure,footer,header,hgroup,main,menu,nav,section,summary{display:block}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}a{background-color:transparent}a:active,a:hover{outline:0}abbr[title]{border-bottom:1px dotted}b,optgroup,strong{font-weight:700}dfn{font-style:italic}h1{font-size:2em;margin:.67em 0}mark{background:#ff0;color:#000}small{font-size:80%}sub,sup{font-size:75%;line-height:0;position:relative;vertical-align:baseline}sup{top:-.5em}sub{bottom:-.25em}svg:not(:root){overflow:hidden}figure{margin:1em 40px}hr{box-sizing:content-box;height:0}pre,textarea{overflow:auto}code,kbd,pre,samp{font-family:monospace,monospace;font-size:1em}button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}button{overflow:visible}button,select{text-transform:none}button,html input[type=button],input[type=reset],input[type=submit]{-webkit-appearance:button;cursor:pointer}button[disabled],html input[disabled]{cursor:default}button::-moz-focus-inner,input::-moz-focus-inner{border:0;padding:0}input{line-height:normal}input[type=checkbox],input[type=radio]{box-sizing:border-box;padding:0}input[type=number]::-webkit-inner-spin-button,input[type=number]::-webkit-outer-spin-button{height:auto}input[type=search]{-webkit-appearance:textfield;box-sizing:content-box}input[type=search]::-webkit-search-cancel-button,input[type=search]::-webkit-search-decoration{-webkit-appearance:none}fieldset{border:1px solid silver;margin:0 2px;padding:.35em .625em .75em}table{border-collapse:collapse;border-spacing:0}.hidden,[hidden]{display:none!important}.pure-img{max-width:100%;height:auto;display:block}</style><style>.pure-form input[type=text],.pure-form input[type=number],.pure-form input[type=search],.pure-form input[type=tel],.pure-form input[type=color],.pure-form input[type=password],.pure-form input[type=email],.pure-form input[type=url],.pure-form input[type=date],.pure-form input[type=month],.pure-form input[type=time],.pure-form input[type=datetime],.pure-form input[type=datetime-local],.pure-form input[type=week],.pure-form select,.pure-form textarea{padding:.5em .6em;display:inline-block;border:1px solid #ccc;box-shadow:inset 0 1px 3px #ddd;border-radius:4px;vertical-align:middle;box-sizing:border-box}.pure-form input:not([type]){padding:.5em .6em;display:inline-block;border:1px solid #ccc;box-shadow:inset 0 1px 3px #ddd;border-radius:4px;box-sizing:border-box}.pure-form input[type=color]{padding:.2em .5em}.pure-form input:not([type]):focus,.pure-form input[type=text]:focus,.pure-form input[type=number]:focus,.pure-form input[type=search]:focus,.pure-form input[type=tel]:focus,.pure-form input[type=color]:focus,.pure-form input[type=password]:focus,.pure-form input[type=email]:focus,.pure-form input[type=url]:focus,.pure-form input[type=date]:focus,.pure-form input[type=month]:focus,.pure-form input[type=time]:focus,.pure-form input[type=datetime]:focus,.pure-form input[type=datetime-local]:focus,.pure-form input[type=week]:focus,.pure-form select:focus,.pure-form textarea:focus{outline:0;border-color:#129FEA}.pure-form input[type=file]:focus,.pure-form input[type=radio]:focus,.pure-form input[type=checkbox]:focus{outline:#129FEA auto 1px}.pure-form .pure-checkbox,.pure-form .pure-radio{margin:.5em 0;display:block}.pure-form input:not([type])[disabled],.pure-form input[type=text][disabled],.pure-form input[type=number][disabled],.pure-form input[type=search][disabled],.pure-form input[type=tel][disabled],.pure-form input[type=color][disabled],.pure-form input[type=password][disabled],.pure-form input[type=email][disabled],.pure-form input[type=url][disabled],.pure-form input[type=date][disabled],.pure-form input[type=month][disabled],.pure-form input[type=time][disabled],.pure-form input[type=datetime][disabled],.pure-form input[type=datetime-local][disabled],.pure-form input[type=week][disabled],.pure-form select[disabled],.pure-form textarea[disabled]{cursor:not-allowed;background-color:#eaeded;color:#cad2d3}.pure-form input[readonly],.pure-form select[readonly],.pure-form textarea[readonly]{background-color:#eee;color:#777;border-color:#ccc}.pure-form input:focus:invalid,.pure-form select:focus:invalid,.pure-form textarea:focus:invalid{color:#b94a48;border-color:#e9322d}.pure-form input[type=file]:focus:invalid:focus,.pure-form input[type=radio]:focus:invalid:focus,.pure-form input[type=checkbox]:focus:invalid:focus{outline-color:#e9322d}.pure-form select{height:2.25em;border:1px solid #ccc;background-color:#fff}.pure-form select[multiple]{height:auto}.pure-form label{margin:.5em 0 .2em}.pure-form fieldset{margin:0;padding:.35em 0 .75em;border:0}.pure-form legend{display:block;width:100%;padding:.3em 0;margin-bottom:.3em;color:#333;border-bottom:1px solid #e5e5e5}.pure-form-stacked input:not([type]),.pure-form-stacked input[type=text],.pure-form-stacked input[type=number],.pure-form-stacked input[type=search],.pure-form-stacked input[type=tel],.pure-form-stacked input[type=color],.pure-form-stacked input[type=file],.pure-form-stacked input[type=password],.pure-form-stacked input[type=email],.pure-form-stacked input[type=url],.pure-form-stacked input[type=date],.pure-form-stacked input[type=month],.pure-form-stacked input[type=time],.pure-form-stacked input[type=datetime],.pure-form-stacked input[type=datetime-local],.pure-form-stacked input[type=week],.pure-form-stacked label,.pure-form-stacked select,.pure-form-stacked textarea{display:block;margin:.25em 0}.pure-form-aligned .pure-help-inline,.pure-form-aligned input,.pure-form-aligned select,.pure-form-aligned textarea,.pure-form-message-inline{display:inline-block;vertical-align:middle}.pure-form-aligned textarea{vertical-align:top}.pure-form-aligned .pure-control-group{margin-bottom:.5em}.pure-form-aligned .pure-control-group label{text-align:right;display:inline-block;vertical-align:middle;width:10em;margin:0 1em 0 0}.pure-form-aligned .pure-controls{margin:1.5em 0 0 11em}.pure-form .pure-input-rounded,.pure-form input.pure-input-rounded{border-radius:2em;padding:.5em 1em}.pure-form .pure-group fieldset{margin-bottom:10px}.pure-form .pure-group input,.pure-form .pure-group textarea{display:block;padding:10px;margin:0 0 -1px;border-radius:0;position:relative;top:-1px}.pure-form .pure-group input:focus,.pure-form .pure-group textarea:focus{z-index:3}.pure-form .pure-group input:first-child,.pure-form .pure-group textarea:first-child{top:1px;border-radius:4px 4px 0 0;margin:0}.pure-form .pure-group input:first-child:last-child,.pure-form .pure-group textarea:first-child:last-child{top:1px;border-radius:4px;margin:0}.pure-form .pure-group input:last-child,.pure-form .pure-group textarea:last-child{top:-2px;border-radius:0 0 4px 4px;margin:0}.pure-form .pure-group button{margin:.35em 0}.pure-form .pure-input-1{width:100%}.pure-form .pure-input-3-4{width:75%}.pure-form .pure-input-2-3{width:66%}.pure-form .pure-input-1-2{width:50%}.pure-form .pure-input-1-3{width:33%}.pure-form .pure-input-1-4{width:25%}.pure-form .pure-help-inline,.pure-form-message-inline{display:inline-block;padding-left:.3em;color:#666;vertical-align:middle;font-size:.875em}.pure-form-message{display:block;color:#666;font-size:.875em}@media only screen and (max-width :480px){.pure-form button[type=submit]{margin:.7em 0 0}.pure-form input:not([type]),.pure-form input[type=text],.pure-form input[type=number],.pure-form input[type=search],.pure-form input[type=tel],.pure-form input[type=color],.pure-form input[type=password],.pure-form input[type=email],.pure-form input[type=url],.pure-form input[type=date],.pure-form input[type=month],.pure-form input[type=time],.pure-form input[type=datetime],.pure-form input[type=datetime-local],.pure-form input[type=week],.pure-form label{margin-bottom:.3em;display:block}.pure-group input:not([type]),.pure-group input[type=text],.pure-group input[type=number],.pure-group input[type=search],.pure-group input[type=tel],.pure-group input[type=color],.pure-group input[type=password],.pure-group input[type=email],.pure-group input[type=url],.pure-group input[type=date],.pure-group input[type=month],.pure-group input[type=time],.pure-group input[type=datetime],.pure-group input[type=datetime-local],.pure-group input[type=week]{margin-bottom:0}.pure-form-aligned .pure-control-group label{margin-bottom:.3em;text-align:left;display:block;width:100%}.pure-form-aligned .pure-controls{margin:1.5em 0 0}.pure-form .pure-help-inline,.pure-form-message,.pure-form-message-inline{display:block;font-size:.75em;padding:.2em 0 .8em}</style><style>.pure-g{letter-spacing:-.31em;text-rendering:optimizespeed;font-family:FreeSans,Arimo,\"Droid Sans\",Helvetica,Arial,sans-serif;display:-webkit-box;display:-webkit-flex;display:-ms-flexbox;display:flex;-webkit-flex-flow:row wrap;-ms-flex-flow:row wrap;flex-flow:row wrap;-webkit-align-content:flex-start;-ms-flex-line-pack:start;align-content:flex-start}@media all and (-ms-high-contrast:none),(-ms-high-contrast:active){table .pure-g{display:block}}.opera-only :-o-prefocus,.pure-g{word-spacing:-.43em}.pure-u,.pure-u-1,.pure-u-1-1,.pure-u-1-12,.pure-u-1-2,.pure-u-1-24,.pure-u-1-3,.pure-u-1-4,.pure-u-1-5,.pure-u-1-6,.pure-u-1-8,.pure-u-10-24,.pure-u-11-12,.pure-u-11-24,.pure-u-12-24,.pure-u-13-24,.pure-u-14-24,.pure-u-15-24,.pure-u-16-24,.pure-u-17-24,.pure-u-18-24,.pure-u-19-24,.pure-u-2-24,.pure-u-2-3,.pure-u-2-5,.pure-u-20-24,.pure-u-21-24,.pure-u-22-24,.pure-u-23-24,.pure-u-24-24,.pure-u-3-24,.pure-u-3-4,.pure-u-3-5,.pure-u-3-8,.pure-u-4-24,.pure-u-4-5,.pure-u-5-12,.pure-u-5-24,.pure-u-5-5,.pure-u-5-6,.pure-u-5-8,.pure-u-6-24,.pure-u-7-12,.pure-u-7-24,.pure-u-7-8,.pure-u-8-24,.pure-u-9-24{display:inline-block;zoom:1;letter-spacing:normal;word-spacing:normal;vertical-align:top;text-rendering:auto}.pure-g [class*=pure-u]{font-family:sans-serif}.pure-u-1-24{width:4.1667%}.pure-u-1-12,.pure-u-2-24{width:8.3333%}.pure-u-1-8,.pure-u-3-24{width:12.5%}.pure-u-1-6,.pure-u-4-24{width:16.6667%}.pure-u-1-5{width:20%}.pure-u-5-24{width:20.8333%}.pure-u-1-4,.pure-u-6-24{width:25%}.pure-u-7-24{width:29.1667%}.pure-u-1-3,.pure-u-8-24{width:33.3333%}.pure-u-3-8,.pure-u-9-24{width:37.5%}.pure-u-2-5{width:40%}.pure-u-10-24,.pure-u-5-12{width:41.6667%}.pure-u-11-24{width:45.8333%}.pure-u-1-2,.pure-u-12-24{width:50%}.pure-u-13-24{width:54.1667%}.pure-u-14-24,.pure-u-7-12{width:58.3333%}.pure-u-3-5{width:60%}.pure-u-15-24,.pure-u-5-8{width:62.5%}.pure-u-16-24,.pure-u-2-3{width:66.6667%}.pure-u-17-24{width:70.8333%}.pure-u-18-24,.pure-u-3-4{width:75%}.pure-u-19-24{width:79.1667%}.pure-u-4-5{width:80%}.pure-u-20-24,.pure-u-5-6{width:83.3333%}.pure-u-21-24,.pure-u-7-8{width:87.5%}.pure-u-11-12,.pure-u-22-24{width:91.6667%}.pure-u-23-24{width:95.8333%}.pure-u-1,.pure-u-1-1,.pure-u-24-24,.pure-u-5-5{width:100%}</style></head><body><div class=\"pure-g\"><div class=\"pure-u-1-4\"></div><div class=\"pure-u-1-2\"><h2 style=\"text-align:center;\">The BUTTON Configuration Panel</h2><form class=\"pure-form pure-form-stacked\" action=\"/setup\" method=\"post\"><fieldset><legend style=\"font-size:18px;margin-top:10px;\">WiFi Settings</legend><label>SSID</label><input class=\"pure-input-1\" type=\"text\" placeholder=\"SSID\" value=\"SSID_PLACE_HOLDER\"><label>Password</label><input class=\"pure-input-1\" type=\"password\" placeholder=\"Password\" value=\"PASSWORD_PLACE_HOLDER\"></fieldset><fieldset><legend style=\"font-size:18px;margin-top:10px;\">Button settings (When you push the BUTTON, trigger following request)</legend><label>POST</label><label class=\"pure-radio\"><input type=\"radio\" name=\"post\" value=\"1\" POST_ON_PLACE_HOLDER> ON <input type=\"radio\" name=\"post\" value=\"0\" POST_OFF_PLACE_HOLDER> OFF</label><label>Host (must be https, do not put http protocol in field)</label><input class=\"pure-input-1\" type=\"text\" placeholder=\"host\" value=\"HOST_PLACE_HOLDER\"><label>Port</label><input class=\"pure-input-1\" type=\"text\" placeholder=\"port\" value=\"PORT_PLACE_HOLDER\"><label>URL</label><input class=\"pure-input-1\" type=\"text\" placeholder=\"URL\" value=\"URL_PLACE_HOLDER\"><label>Request on JSON</label><label class=\"pure-radio\"><input type=\"radio\" name=\"json\" value=\"1\" JSON_ON_PLACE_HOLDER> ON <input type=\"radio\" name=\"json\" value=\"0\" JSON_OFF_PLACE_HOLDER> OFF </label><label>BODY</label><textarea name=\"body\" rows=\"10\" cols=\"100\">BODY_PLACE_HOLDER</textarea></fieldset><input type=\"submit\" value=\"SAVE\"></form></div></div></body></html/>"

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

