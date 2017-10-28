int switchState = 0;
int oldSwitchState = 0;

unsigned long lastChangeTime = 0;
unsigned long now = 0;
bool isTriggered = false;

void handlePushButton() {
  switchState = digitalRead(BUTTON);

  if (switchState != oldSwitchState) {
    oldSwitchState = switchState;
    lastChangeTime = millis();
    if (switchState == HIGH) { 
      isTriggered = false;
    }
    return;
  }

  if (switchState == LOW) {
    return;
  }

  now = millis();

  if (now - lastChangeTime > 500) {
    if (switchState == HIGH && !isTriggered) {
      isTriggered = true;
      sendHTTPS(getMethod(), getHost(), getPort(), getURL(), getRequestBody(), isJSONBody());
    }
  }
}
