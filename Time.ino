       
void Time_init() 
{
  handle_time_zone();
  HTTP.on("/Time", handle_Time);     
  HTTP.on("/timeZone", handle_time_zone);    
  String _timeZone = jsonRead(Variables, "timeZone");
  timeZone = _timeZone.toInt();
  timeSynch(timeZone);
  outData();
}


void timeSynch(int zone)
{
  if (WiFi.status() == WL_CONNECTED) 
  {
    // Настройка соединения с NTP сервером
    configTime(zone * 3600, 0, "pool.ntp.org", "ru.pool.ntp.org");
    int i = 0;
    Serial.println("\nWaiting for time");
    while (!time(nullptr) && i < 10) 
    {
      Serial.print(".");
      i++;
      delay(1000);
    }
    Serial.println("");
    Serial.println("ITime Ready!");
    Serial.println(GetTime());
    Serial.println(GetDate());
  }
}

void handle_time_zone() 
{               
 HTTP.on("/timeZone", HTTP_GET, []() 
 {
    jsonWrite(Variables, "timeZone", HTTP.arg("timeZone"));
    saveVariables();                 // Функция сохранения данных во Flash
    HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
  });
}

void handle_Time()
{
  timeSynch(timeZone);
  HTTP.send(200, "text/plain", "OK"); // отправляем ответ о выполнении
}

// Получение текущего времени
String GetTime() 
{
 time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
 String Time = ""; // Строка для результатов времени
 Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
 int i = Time.indexOf(":"); //Ишем позицию первого символа :
 Time = Time.substring(i - 2, i + 6); // Выделяем из строки 2 символа перед символом : и 6 символов после
 return Time; // Возврашаем полученное время
}

// Получение даты
String GetDate() 
{
 time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
 String Data = ""; // Строка для результатов времени
 Data += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
 int i = Data.lastIndexOf(" "); //Ишем позицию последнего символа пробел
 String Time = Data.substring(i - 8, i+1); // Выделяем время и пробел
 Data.replace(Time, ""); // Удаляем из строки 8 символов времени и пробел
 return Data; // Возврашаем полученную дату
}
int Hour_For_Work ()
{
 time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
 String Time = ""; // Строка для результатов времени
 Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
 int i = Time.indexOf(":"); //Ишем позицию первого символа :
 Time = Time.substring(i - 2, i); // Выделяем из строки 2 символа перед символом : 
 hourNow = Time.toInt();
 //Serial.print("hour now "); Serial.print(hourNow);  Serial.print(" "); Serial.println(Time);
return hourNow;
}

int Day_For_Work ()
{
 time_t now = time(nullptr); // получаем время с помощью библиотеки time.h
 String Time = ""; // Строка для результатов времени
 Time += ctime(&now); // Преобразуем время в строку формата Thu Jan 19 00:55:35 2017
 int i = Time.indexOf(" "); //Ишем позицию первого символа :
 Time = Time.substring( 0, i ); // Выделяем из строки символы от начала и до пробела
 if      ( Time == "Mon" ) dayNow = 1;
 else if ( Time == "Tue" ) dayNow = 2;
 else if ( Time == "Wed" ) dayNow = 3;
 else if ( Time == "Thu" ) dayNow = 4;
 else if ( Time == "Fri" ) dayNow = 5;
 else if ( Time == "Sat" ) dayNow = 6;
 else if ( Time == "Sun" ) dayNow = 0;
 //Serial.print("deys of "); Serial.print(dayNow);  Serial.print(" "); Serial.println(Time); 
 return dayNow;
}
void sinhronizeTime ()
{
  if ( currentMillis - sinhronizeTimeMillis > sinhronizeTimeInterval )
  {
    sinhronizeTimeMillis = currentMillis;
    Time_init();
    Serial.print ( "Sinhronize Time .. " ); Serial.print ( GetTime () ); Serial.print ( " " ); Serial.println ( GetDate () );
  }
}
