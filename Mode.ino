void Mode_init()
{
  { 
    if      ( Mode == 0 ) { RadiatorsOnOff = 0; }                                                                                  // режим "ВСЕГДА ВЫКЛЮЧЕН" 
    else if ( Mode == 1 ) { TempCalculate ( CalkProg() ); }                                                                        // режим "АВТО"          
    else if ( Mode == 2 ) { RadiatorsOnOff = 1; }                                                                                  // режим "ВСЕГДА ВКЛЮЧЕН"  
    else if ( Mode == 3 ) { RadiatorsOnOff = 2; }                                                                                  // режим "БЕЗ КОНТРОЛЯ СЛЕЙВ УСТРОЙСТВ" 
  }
}


void TempCalculate( double Trasp )
{
  //Serial.print ( "TnowR = " );  Serial.println ( TnowR );
  if ( TnowR < ( Trasp - ( dT / 2 ) ) )
  { RadiatorsOnOff = 1; }
  else if ( TnowR >= ( Trasp + ( dT / 2 ) ) )
  { RadiatorsOnOff = 0; }
}

void LoadProg()
{
  int s;
  s = jsonReadtoInt ( SetupMode, "D0" );
  if ( s < 1 || s > 4 ) modeProg [0] = 2; else modeProg [0] = s;
  s = jsonReadtoInt ( SetupMode, "D1" );
  if ( s < 1 || s > 4 ) modeProg [1] = 1; else modeProg [1] = s;
  s = jsonReadtoInt ( SetupMode, "D1" );
  if ( s < 1 || s > 4 ) modeProg [2] = 1; else modeProg [2] = s;
  s = jsonReadtoInt ( SetupMode, "D1" );
  if ( s < 1 || s > 4 ) modeProg [3] = 1; else modeProg [3] = s;
  s = jsonReadtoInt ( SetupMode, "D1" );
  if ( s < 1 || s > 4 ) modeProg [4] = 1; else modeProg [4] = s;
  s = jsonReadtoInt ( SetupMode, "D1" );
  if ( s < 1 || s > 4 ) modeProg [5] = 1; else modeProg [5] = s;
  s = jsonReadtoInt ( SetupMode, "D6" );
  if ( s < 1 || s > 4 ) modeProg [6] = 2; else modeProg [6] = s;
  
  Serial.println ( " " );
  for ( d = 0; d < 7; d++ )
  {
    Serial.print ( modeProg [d] ); Serial.print ( " " );
  }
  Serial.println ( " " );
}

double CalkProg() //вычесляю какая на данный момент программа эконом или комфорт и возвращает температуру с какой нужно работать
{
  if      ( modeProg [ Day_For_Work() ] == 1 ) 
  { 
    if      ( Prog1 [ Hour_For_Work () ] == 0 ) { TEMPwork = Teco; EcoORComf = 0;  } 
    else if ( Prog1 [ Hour_For_Work () ] == 1 ) { TEMPwork = Tcomf; EcoORComf = 1; } }
  else if ( modeProg [ Day_For_Work () ] == 2 ) 
  { 
    if      ( Prog2 [ Hour_For_Work () ] == 0 ) { TEMPwork = Teco; EcoORComf = 0;  } 
    else if ( Prog2 [ Hour_For_Work () ] == 1 ) { TEMPwork = Tcomf; EcoORComf = 1; } }
  else if ( modeProg [ Day_For_Work () ] == 3 ) 
  { 
    if      ( Prog3 [ Hour_For_Work () ] == 0 ) { TEMPwork = Teco; EcoORComf = 0;  } 
    else if ( Prog3 [ Hour_For_Work () ] == 1 ) { TEMPwork = Tcomf; EcoORComf = 1; } }
  else if ( modeProg [ Day_For_Work () ] == 4 ) 
  { 
    if      ( Prog4 [ Hour_For_Work () ] == 0 ) { TEMPwork = Teco; EcoORComf = 0;  } 
    else if ( Prog4 [ Hour_For_Work () ] == 1 ) { TEMPwork = Tcomf; EcoORComf = 1; } }
    
// - костыль по временному исправлению бага потери данных о программах
  else if ( modeProg [ Day_For_Work () ] < 1 || modeProg [ Day_For_Work () ] > 4 )
  {
    if ( Day_For_Work () > 0 && Day_For_Work () < 6 ) 
    {
      if      ( Prog1 [ Hour_For_Work () ] == 0 ) { TEMPwork = Teco; EcoORComf = 0;  } 
      else if ( Prog1 [ Hour_For_Work () ] == 1 ) { TEMPwork = Tcomf; EcoORComf = 1; }
    }
    else if ( Day_For_Work () == 0 || Day_For_Work () == 6 )
    {
      if      ( Prog2 [ Hour_For_Work () ] == 0 ) { TEMPwork = Teco; EcoORComf = 0;  } 
      else if ( Prog2 [ Hour_For_Work () ] == 1 ) { TEMPwork = Tcomf; EcoORComf = 1; }
    }
  }
// - костыль по временному исправлению бага потери данных о программах  

  return TEMPwork;
}
void Debug ()
{
  if ( currentMillis - DebugMillis > DebugInterval)
  {
    DebugMillis = currentMillis;
    Serial.print ( "Mode = " );  Serial.println ( Mode ); 
    Serial.print ( "days now " ); Serial.println ( Day_For_Work () );
    Serial.print ( "hour now " ); Serial.println ( Hour_For_Work () );
    Serial.print ( "Work temperature " ); Serial.println ( TEMPwork );
  }
}
