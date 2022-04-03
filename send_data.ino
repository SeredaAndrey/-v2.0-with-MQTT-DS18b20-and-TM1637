void SendData ()
{
  if ( currentMillis - SendDataMillis > SendDataInterval )
  {
    SendDataMillis = currentMillis;
    Serial.println ( "attempt to send to MQTT" );
    MQTTcall ();
    if ( flagFailMQTTconnect == 1 && flagActivURLcontrols == "1" ) 
    { 
      SendTemperature ();
      if ( RadiatorsOnOff == 0 ) 
      {
        Radiator_On_Off ( 1, "0" ); delay (200); Radiator_On_Off ( 2, "0" ); delay (200);
      }
      else if ( RadiatorsOnOff == 1 ) 
      {
        Radiator_On_Off ( 1, "1" ); delay (200); Radiator_On_Off ( 2, "1" ); delay (200); 
      }
      else if ( RadiatorsOnOff == 2 )
      {
        // нет действий
      }
    }
  }
}

String getURL (String urls)
{
  String answer = "";
  HTTPClient http;
  http.begin ( urls );
  int httpCode = http.GET ();
  if ( httpCode == HTTP_CODE_OK )
  {
    answer = http.getString ();
  }
  http.end ();
  return answer;
}

void SendTemperature ()
{
  String urls = "http://";
  urls += IPBoolerHost;
  urls += "/Temperature" + NumberOfHomeSystemController + "?Temperature" + NumberOfHomeSystemController + "=" + _Tnow;
  getURL(urls);
}
void Radiator_On_Off ( int Rad, String  activate )
{
  String urls = "http://";
  String ip = "";
  if ( Rad == 1 ) ip = IPslave1;
  else if ( Rad == 2 ) ip = IPslave2;
  urls += ip;
  urls += "/Activate?Activate=" + activate;
  Serial.print("Activate "); Serial.print( Rad ); Serial.print(" radiator. Get urls: "); Serial.println(urls);
  getURL(urls);
}
 
