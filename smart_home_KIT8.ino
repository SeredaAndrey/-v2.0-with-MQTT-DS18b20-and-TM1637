#include "set_library.h"
#include "Const_variable.h"


void loop ()
{
  currentMillis = millis();
  PressKeys();
  handleMQTT ();
  HTTP.handleClient();
  Mode_init();
  ds18b20_read();
  dispRefr();
  SendData();
  sinhronizeTime ();
  delay (1);
  dnsServer.processNextRequest();
  ResetESP();
  Debug ();
}
