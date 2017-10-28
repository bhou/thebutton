// PIN definitions for LED and button
int BUTTON = D1;
int RED = D2;
int YELLOW = D3;
int GREEN = D4;


/* Set these to your desired credentials for access point */
const char *apSSID = "TheButton";
const char *apPassword = "TheButton";

void setupPIN() {
  pinMode(BUTTON, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

