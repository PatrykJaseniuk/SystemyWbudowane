unsigned long koniec;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);

  ustawAlarm(10);
}

// the loop routine runs over and over again forever:
void loop()
{

  if (alarmCzyKoniec())
  {
    while (true)
    {
      Serial.println("Alarm!\n");
      digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(1000);                     // wait for a second
      digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
      delay(1000);                     // wait for a second
    }
  }
  // print out the state of the button:
  // delay in between reads for stability
}

void ustawAlarm(int czas)
{

  auto start = millis();
  Serial.println(start);

  koniec = start + (czas * 1000);
  Serial.println(koniec);
}

bool alarmCzyKoniec()
{
  if (millis() > koniec)
  {
    return true;
  }
  else
  {
    return false;
  }
}