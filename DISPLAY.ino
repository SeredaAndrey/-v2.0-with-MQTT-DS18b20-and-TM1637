void dispRefr ()
{
  if ( currentMillis - dispMillis > dispRefrinterval)
  {
    dispMillis = currentMillis;
    int i;                               // номер позиции
    String _Hour;
    int TimeD;                            // Строка для результатов часов
    String _Minute;
    String Time = "";                    // Строка для результатов времени
    String _Time = "";
    time_t now = time(nullptr);          // получаем время с помощью библиотеки time.h
    Time += ctime(&now);                 // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
    i = Time.indexOf(":");               // Ишем позицию первого символа :
    _Hour = Time.substring(i - 2, i);    // Выделяем из строки 2 символа перед символом : и присваеваем часам
    _Time = Time.substring(i - 2, i+1);  // Выделяем из строки 2 символа перед символом : и один после
    Time.replace (_Time, "");            // Удаляем из строки времени часы и первый символ :
    i = Time.indexOf(":");               // Ишем позицию первого символа :
    _Minute = Time.substring(i - 2, i);  // Выделяем из строки 2 символа перед символом : и присваиваем минутам
    _Time = ""; _Time += _Hour; _Time += _Minute; TimeD = _Time.toInt();
    
    int TempD = TnowR;
    
    if ( flagDisp == 1 )
    {
      display.clear();
      display.showNumberDec ( TempD, false, 2, 1 );

      flagDisp = 0; 
    }
    else if ( flagDisp == 0 ) 
    {
      display.clear();
      display.showNumberDec ( TimeD, true );
      //display.showDots(1, digits);
          
      flagDisp = 1;
    }
  }
}
