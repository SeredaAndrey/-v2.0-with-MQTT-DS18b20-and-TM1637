// mosquitto_pub -h localhost -t "SmartHome/Living-Rooms/Room-Controller/Temperature" -m 21.0 сделать публикацию в топике
// mosquitto_sub -h localhost -t "SmartHome/Living-Rooms/Room-Controller/Activate"            подписаться на топик              

void handleMQTT ()
{
  IPAddress ip_MQTTip ( MQTTip[0], MQTTip[1], MQTTip[2], MQTTip[3] ); 
  String _topic = "/SmartHome"; _topic += pubtopic; 
  String _topicTempE = _topic + "/temperatureECO";
  String _topicTempC = _topic + "/temperatureCOMF";
  String _topicdTemp = _topic + "/dTemp";
  String _topicMode = _topic + "/Mode";
  if ( WiFi.status () == WL_CONNECTED )
  {
    client.set_server ( ip_MQTTip );
    //Serial.println ( "Connect to WiFi - ACCEPT" );
    if ( !client.connected () )
    {
      //Serial.println ( "Connect to MQTT - ACCEPT" );
      if ( client.connect ( SSDP_Name ) )
      {
        client.set_callback ( callback );
        client.subscribe ( _topicTempE );
        client.subscribe ( _topicTempC );
        client.subscribe ( _topicdTemp );
        client.subscribe ( _topicMode );
      }
    }
    else flagFailMQTTconnect = 1;
    if ( client.connected () )
    {
      client.loop ();
    }
    SendData ();
  }
}

void MQTTcall ()
{
  String _Mode;
  String _topic = "/SmartHome"; 
  _topic += pubtopic;
  String _topicTemp = _topic + "/temperature";
  String _topicTempE = _topic + "/temperatureECO";
  String _topicTempC = _topic + "/temperatureCOMF";
  String _topicdTemp = _topic + "/dTemp";
  String _topicMode = _topic + "/Mode"; 
  String _Subtopic1 = _topic; _Subtopic1 += subtopic1; _Subtopic1 += "/Activate";
  String _Subtopic2 = _topic; _Subtopic2 += subtopic2; _Subtopic2 += "/Activate";
        if      ( Mode == 1 )           _Mode = "1"; 
        else if ( Mode == 2 )           _Mode = "2"; 
        else if ( Mode == 0 )           _Mode = "0";
        else if ( Mode == 3 )           _Mode = "3"; 
        else                            _Mode = "wrong status mode";
  String _Command = "";
        if ( RadiatorsOnOff == 0 )      _Command = ComandOFF;
        else if ( RadiatorsOnOff == 1 ) _Command = ComandON;
  Serial.print ( "Connect to MQTT with SSDP_Name " ); Serial.print ( SSDP_Name ); Serial.println ( " - ACCEPT" ); flagFailMQTTconnect = 0;
  client.publish ( _topicTemp, _Tnow ); Serial.print ( "Publish " ); Serial.print ( _topicTemp ); Serial.print ( " " ); Serial.println ( _Tnow ); //отправка температуры на сервер
  client.publish ( _topicTempE, TecoS ); Serial.print ( "Publish " ); Serial.print ( _topicTempE ); Serial.print ( " " ); Serial.println ( TecoS ); //отправка еко температуры на сервер
  client.publish ( _topicTempC, TcomfS ); Serial.print ( "Publish " ); Serial.print ( _topicTempC ); Serial.print ( " " ); Serial.println ( TcomfS ); //отправка комф температуры на сервер
  client.publish ( _topicdTemp, dTempS ); Serial.print ( "Publish " ); Serial.print ( _topicdTemp ); Serial.print ( " " ); Serial.println ( dTempS ); //отправка дельта температуры на сервер
  client.publish ( _topicMode, _Mode ); Serial.print ( "Publish " ); Serial.print ( _topicMode ); Serial.print ( " " ); Serial.println ( _Mode ); //отправка моде на сервер
  if ( Mode != 3 ) {
  client.publish ( _Subtopic1, _Command ); Serial.print ( "Publish " ); Serial.print ( _Subtopic1 ); Serial.print ( " " ); Serial.println ( _Command );   //отправка команды на включение правого радиатора
  client.publish ( _Subtopic2, _Command ); Serial.print ( "Publish " ); Serial.print ( _Subtopic2 ); Serial.print ( " " ); Serial.println ( _Command ); } //отправка команды на включение левого радиатора
  client.set_callback ( callback );
//  client.subscribe ( _topicActiv );
//  Serial.println ( client.subscribe ( _topicActiv ) );
  flagFailMQTTconnect = 0;
}

void callback(const MQTT::Publish& pub) 
{
  String _topic = "/SmartHome"; _topic += pubtopic; 
  String _topicTempE = _topic + "/temperatureECO";
  String _topicTempC = _topic + "/temperatureCOMF";
  String _topicdTemp = _topic + "/dTemp";
  String _topicMode = _topic + "/Mode"; 
  String payload = pub.payload_string();
  String Variable;
  if ( String ( pub.topic () ) == _topicMode )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    if ( Variable == "1" ) 
    { 
      Mode = 1; 
      jsonWrite ( SetupMode, "Mode", "1" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
    else if ( Variable == "2" ) 
    { 
      Mode = 2; 
      jsonWrite ( SetupMode, "Mode", "2" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
    else if ( Variable == "0" ) 
    { 
      Mode = 0; 
      jsonWrite ( SetupMode, "Mode", "0" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
    else if ( Variable == "3" ) 
    { 
      Mode = 3; 
      jsonWrite ( SetupMode, "Mode", "3" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
  }
  if ( String ( pub.topic () ) == _topicTempE )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    TecoS = Variable;
    Teco = atof ( Variable.c_str () );
    jsonWrite ( SetupMode, "Teco", TecoS );
    saveSetupMode ();
  }
  if ( String ( pub.topic () ) == _topicTempC )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    TcomfS = Variable;
    Tcomf = atof ( Variable.c_str () );
    jsonWrite ( SetupMode, "Tkomf", TcomfS );
    saveSetupMode ();
  }
  if ( String ( pub.topic () ) == _topicdTemp )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    dTempS = Variable;
    dT = atof ( Variable.c_str () );
    jsonWrite ( SetupMode, "dT", dTempS );
    saveSetupMode ();
  }
}
