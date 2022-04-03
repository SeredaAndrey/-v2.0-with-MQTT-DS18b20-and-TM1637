void WIFIinit() 
{
  HTTP.on ( "/Commands", HTTP_GET, []()                    // --------------------Получаем ComandON & ComandOFF со страницы
  {
    jsonWrite ( Names, "ComandON", HTTP.arg ( "ComandON" ) );
    jsonWrite ( Names, "ComandOFF", HTTP.arg ( "ComandOFF" ) );
    ComandON = HTTP.arg ( "ComandON" );
    ComandOFF = HTTP.arg ( "ComandOFF" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssid", HTTP_GET, []()                        // --------------------Получаем SSDP со страницы
  {
    jsonWrite ( Autorisation, "ssid", HTTP.arg ( "ssid" ) );
    jsonWrite ( Autorisation, "password", HTTP.arg ( "password" ) );
    ssid = HTTP.arg ( "ssid" ); password = HTTP.arg ( "password" );
    saveAutorisation ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssidap", HTTP_GET, []()                      // --------------------Получаем SSDP со страницы  
  {
    jsonWrite ( Autorisation, "ssidAP", HTTP.arg ( "ssidAP"   ));
    jsonWrite ( Autorisation, "passwordAP", HTTP.arg ( "passwordAP" ) );
    ssidAP = HTTP.arg ( "ssidAP" ); passwordAP = HTTP.arg ( "passwordAP" );
    saveAutorisation ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/IPRoom", HTTP_GET, []()                      // --------------------Получаем IPBoolerHost, IPRoomSlave1 и IPRoomSlave2 со страницы
  {
     jsonWrite ( IPadresses, "IPBoolerHost", HTTP.arg ( "IPBoolerHost" ) );
    IPBoolerHost = HTTP.arg ( "IPBoolerHost" );
    jsonWrite ( IPadresses, "IPRoomSlave1", HTTP.arg ( "IPRoomSlave1" ) );
    IPslave1 = HTTP.arg ( "IPRoomSlave1" ); 
    jsonWrite ( IPadresses, "IPRoomSlave2", HTTP.arg ( "IPRoomSlave2" ) );
    IPslave2 = HTTP.arg ( "IPRoomSlave2" ); 
    saveIPs ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/Temp", HTTP_GET, []() 
  {
    jsonWrite ( SetupMode, "Tkomf", HTTP.arg ( "Tkomf" ) );
    jsonWrite ( SetupMode, "Teco", HTTP.arg ( "Teco" ) );
    jsonWrite ( SetupMode, "dT", HTTP.arg ( "dT" ) );
    saveSetupMode ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
    TcomfS = HTTP.arg ( "Tkomf" ); Tcomf = atof ( TcomfS.c_str () );
    TecoS =  HTTP.arg ( "Teco" ); Teco = atof ( TecoS.c_str () );
    dTempS = HTTP.arg ( "dT" ); dT = atof ( dTempS.c_str () );
  });
  HTTP.on ( "/ProgDay", HTTP_GET, []() 
  {
    jsonWrite ( SetupMode, "D1", HTTP.arg ( "D1" ) );
    jsonWrite ( SetupMode, "D2", HTTP.arg ( "D2" ) );
    jsonWrite ( SetupMode, "D3", HTTP.arg ( "D3" ) );
    jsonWrite ( SetupMode, "D4", HTTP.arg ( "D4" ) );
    jsonWrite ( SetupMode, "D5", HTTP.arg ( "D5" ) );
    jsonWrite ( SetupMode, "D6", HTTP.arg ( "D6" ) );
    jsonWrite ( SetupMode, "D0", HTTP.arg ( "D0" ) );
    saveSetupMode ();                 
    HTTP.send ( 200, "text/plain", "OK" );
    LoadProg ();
  }); 
  HTTP.on ( "/topic", HTTP_GET, []()                  // --------------------Получаем pubtopic, subtopic1 & subtopic2 со страницы
  {
    jsonWrite ( Names, "pubtopic", HTTP.arg ( "pubtopic" ) );
    pubtopic = HTTP.arg ( "pubtopic" ); 
    jsonWrite ( Names, "subtopic1", HTTP.arg ( "subtopic1" ) );
    subtopic1 = HTTP.arg ( "subtopic1" );
    jsonWrite ( Names, "subtopic2", HTTP.arg ( "subtopic2" ) );
    subtopic2 = HTTP.arg ( "subtopic2" );
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssdp", HTTP_GET, []()                   // --------------------Получаем SSDP со страницы
  {
    jsonWrite ( Names, "ssdp", HTTP.arg ( "ssdp" ) );
    SSDP_Name = HTTP.arg ( "ssdp" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/Mode", HTTP_GET, []() 
  {
    jsonWrite ( SetupMode, "Mode", HTTP.arg ( "Mode" ) );
    saveSetupMode ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
    String ModeS = HTTP.arg ( "Mode" ); Mode = ModeS.toInt ();
  });
  HTTP.on ( "/flagActivURLcontrols", HTTP_GET, []()   // --------------------Получаем flagActivURLcontrols со страницы
  {
    jsonWrite ( Variables, "flagActivURLcontrols", HTTP.arg ( "flagActivURLcontrols" ) );
    flagActivURLcontrols = HTTP.arg ( "flagActivURLcontrols" ); 
    saveVariables ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/NumberOfHomeSystemController", HTTP_GET, []()   // --------------------Получаем flagActivURLcontrols со страницы
  {
    jsonWrite ( Names, "NumberOfHomeSystemController", HTTP.arg ( "NumberOfHomeSystemController" ) );
    NumberOfHomeSystemController = HTTP.arg ( "NumberOfHomeSystemController" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/MQTTip", HTTP_GET, []()                 // --------------------Получаем MQTTip со страницы
  {
    jsonWrite ( IPadresses, "MQTTip", HTTP.arg ( "MQTTip" ) );
    _MQTTip = HTTP.arg ( "MQTTip" ); 
    saveIPs ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
 
  
  
  
  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  if (ssid == "" && password == "" ) 
  {
    WiFi.begin();
  }
  else 
  {   
    WiFi.begin(ssid.c_str(), password.c_str());
  }
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi up AP");
    StartAPMode();
  }
  else 
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode() 
{
  IPAddress apIP(192, 168, 4, 1);
  IPAddress staticGateway(192, 168, 4, 1);
  IPAddress staticSubnet(255, 255, 255, 0);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, staticGateway, staticSubnet);
  ssidAP = jsonRead ( Autorisation, "ssidAP" ); Serial.print ("Loading from SPIFFS ssidAP = "); Serial.println( ssidAP );
  passwordAP = jsonRead ( Autorisation, "passwordAP" ); Serial.print ("Loading from SPIFFS passwordAP = "); Serial.println( passwordAP );
  WiFi.softAP ( ssidAP.c_str(), passwordAP.c_str() );
  Mode = 2;
  ResetFlag = 1;
  ResetESPMillis = currentMillis;
  return true;
}

void ResetESP ()
{
  if ( ResetFlag == 1 )
  {
    if ( currentMillis - ResetESPMillis > ResetESPInterval)
    {
       ESP.restart();
    }
  }
}
