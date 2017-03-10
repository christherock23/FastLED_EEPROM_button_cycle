#define BUTTON_LEAD 4

bool buttonState = LOW;
bool lastButtonState = LOW;
int mode = 1; //Default mode is one.

/* monitor button press */
bool buttonListener() {
  bool modeChanged = false;

  buttonState = digitalRead(BUTTON_LEAD);

  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      mode++;
      modeChanged = true;
      delay(250);             // Debounce delay. I checked the best parameter and 250 was it.
    }
  }
  lastButtonState = buttonState;

  return modeChanged;
}
