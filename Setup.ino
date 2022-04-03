void setup()
{
  display.setBrightness(0x0f);
  //display.begin ( SSD1306_SWITCHCAPVCC, 0x3C );
  //display.display ();
  //display.clearDisplay ();
  pinMode(PinButtons, INPUT_PULLUP);
  Wire.begin();
  Serial.begin(115200);
  Serial.println("");
  setup_out_init ("Start FS" );          FS_init();
  setup_out_init ("Loading 'Setup.json'");  SetupMode = readFile("SetupMode.json", 4096);  
  setup_out_init ("Loading 'Names.json'");  Names = readFile("Names.json", 4096);  
  setup_out_init ("Loading 'Autorisation.json'");  Autorisation = readFile("Autorisation.json", 4096);  
  setup_out_init ("Loading 'Variables.json'");  Variables = readFile("Variables.json", 4096);  
  setup_out_init ("Loading 'IPadresses.json'");  IPadresses = readFile("IPadresses.json", 4096);  
  LoadVariable ();
  setup_out_init ("Start WIFI");        WIFIinit();
  setup_out_init ("Start begin Time");  Time_init(); 
  setup_out_init ("Start SSDP");        SSDP_init();
  setup_out_init ("Start WebServer");   HTTP_init();
  setup_out_init ("Load Mode Work");    HTTP_init();
  //display.clearDisplay (); display.display ();
}

void LoadVariable ()
{
  _MQTTip = jsonRead ( IPadresses, "MQTTip" );                                       Serial.print ("Loading from SPIFFS MQTTip = "); Serial.println( _MQTTip );
  SSDP_Name = jsonRead ( Names, "ssdp" );                                            Serial.print ("Loading from SPIFFS SSDP_Name = "); Serial.println( SSDP_Name );
  pubtopic = jsonRead ( Names, "pubtopic" );                                         Serial.print ("Loading from SPIFFS pubtopic = "); Serial.println( pubtopic );
  subtopic1 = jsonRead ( Names, "subtopic1" );                                       Serial.print ("Loading from SPIFFS subtopic1 = "); Serial.println( subtopic1 );
  subtopic2 = jsonRead ( Names, "subtopic2" );                                       Serial.print ("Loading from SPIFFS subtopic2 = "); Serial.println( subtopic2 );
  Mode = jsonReadtoInt ( SetupMode, "Mode" );                                        Serial.print ("Loading from SPIFFS Mode = "); Serial.println( Mode );
  TcomfS = jsonRead ( SetupMode, "Tkomf" ); Tcomf = atof ( TcomfS.c_str () );        Serial.print ("Loading from SPIFFS Tkomf = "); Serial.println( Tcomf );
  TecoS = jsonRead ( SetupMode, "Teco" ); Teco = atof ( TecoS.c_str () );            Serial.print ("Loading from SPIFFS Teco = "); Serial.println( Teco );
  dTempS = jsonRead ( SetupMode, "dT" ); dT = atof ( dTempS.c_str () );              Serial.print ("Loading from SPIFFS dT = "); Serial.println( dT );
  ssid = jsonRead ( Autorisation, "ssid" );                                          Serial.print ("Loading from SPIFFS ssid = "); Serial.println( ssid );
  password = jsonRead ( Autorisation, "password" );                                  Serial.print ("Loading from SPIFFS password = "); Serial.println( password );
  IPBoolerHost = jsonRead ( IPadresses, "IPBoolerHost" );                            Serial.print ("Loading from SPIFFS IPBoolerHost = "); Serial.println( IPBoolerHost );
  NumberOfHomeSystemController = jsonRead ( Names, "NumberOfHomeSystemController" ); Serial.print ("Loading from SPIFFS NumberOfHomeSystemController = "); Serial.println( NumberOfHomeSystemController );
  flagActivURLcontrols = jsonReadtoInt ( Variables, "flagActivURLcontrols" );        Serial.print ("Loading from SPIFFS flagActivURLcontrols = "); Serial.println( flagActivURLcontrols );
  ComandON = jsonRead ( Names, "ComandON" );                                         Serial.print ("Loading from SPIFFS ComandON = "); Serial.println( ComandON );
  ComandOFF = jsonRead ( Names, "ComandOFF" );                                       Serial.print ("Loading from SPIFFS ComandOFF = "); Serial.println( ComandOFF );
  LoadProg();
  String ip = _MQTTip; 
  int i = ip.indexOf( "." );                                                                    String _ip = ip.substring( 0, i ); MQTTip [ 0 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 1 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 2 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 3 ] = _ip.toInt();
  IPAddress ip_MQTTip ( MQTTip[0], MQTTip[1], MQTTip[2], MQTTip[3] ); 
  Serial.print ( MQTTip[0] ); Serial.print ( "," ); Serial.print ( MQTTip[1] ); Serial.print ( "," ); Serial.print ( MQTTip[2] ); Serial.print ( "," ); Serial.println ( MQTTip[3] );
}

void setup_out_init ( String text )
{
  //display.setTextSize ( 1 );
  //display.setTextColor ( WHITE );
  //display.setCursor ( 10 , 0 );
  //display.clearDisplay ();
  //display.println ( text );
  //display.display ();
  Serial.println ( text );
  delay(200);
}
