////////////////////////////// SSID & password //////////////////////////////
String ssid       = "Pushkina15_2.4GHz"; 
String password   = "Sereda19792004"; 
////////////////////////////// SSIDAP & passwordIP //////////////////////////////
String ssidAP     = "WiFi_ESP_for_Config";   
String passwordAP = "Sereda19792004";
////////////////////////////// IPs //////////////////////////////
String _MQTTip  = "192.168.10.100";
String IPslave1  = "192.168.10.131";
String IPslave2  = "192.168.10.132";
String IPBoolerHost  = "192.168.10.110";
int myip   [4] = { 192, 168, 10,  99 };         
int mask   [4] = { 255, 255, 255, 0  };
int gate   [4] = { 192, 168, 10,  1  }; 
int MQTTip [4] = { 192, 168, 10, 100 };
////////////////////////////// HTTP, MQTT & UDP //////////////////////////////
int port = 80;
int timeZone = 3;  
String pubtopic = "/Parents-Rooms";  //топик комнатного контроллера
String subtopic1 = "/Controller-1";  //топик контроллера правого радиатора
String subtopic2 = "/Controller-2";  //топик контроллера левого радиатора
//String subtopic3 = "/Controller-3";  //топик контроллера увлажнителя
String flagActivURLcontrols = "1";   //Флаг активации режима при котором при отсутсвии подключения к MQTT упарвление через URL запросы
bool flagFailMQTTconnect = 0;
String NumberOfHomeSystemController = "130";
String ComandON = "DeviceON!";
String ComandOFF = "DeviceOFF!";
////////////////////////////// Names //////////////////////////////
String SSDP_Name   = "Parents-Rooms-Controller"; 
////////////////////////////// FS //////////////////////////////
String IPadresses = "{}";            //"{"MQTTip":"192.168.10.100", "IPRoomSlave1":"192.168.10.131", "IPRoomSlave2":"192.168.10.132", "IPBoolerHost":"192.168.10.110"}"
String Names = "{}";                 //"{"SSDP_Name":"Parents-Rooms-Hot-Panel-1","pubtopic":"/Parents-Rooms","subtopic1":"/Controller-1","subtopic2":"/Controller-2"}";
String SetupMode = "{}";             //Запись состояний MODE 
String Variables = "{}";             //Запись состояний TimeZone & Temperature
String Autorisation = "{}";          //"{"ssid":"Pushkina15_2.4GHz","password":"Sereda19792004","ssidAP":"WiFi_ESP_for_Config","passwordAP":"Sereda19792004"}";
////////////////////////////// Modes //////////////////////////////
double TnowR;                        // Реальная температура в доубле
double dT = 0.5;                     // дельта Т
double Teco = 19;                    // Эко температура
double Tcomf = 25;                   // Комфортаня температура
String TcomfS; String TecoS;         // Эко и Комф температура в стринге
String dTempS;
String _Tnow;                        // Реальная температура в стринге
int Mode = 3;                        // Режим работы устройства 0-всегда выключен, 1-автоматический, 2-всегда включен, 3-не управляет слейв утройствами
bool ResetFlag = 0;                  // флаг активирующий таймер перезагрузки контроллера
int flagDisp = 0;
bool EcoORComf;
double TEMPwork;
int dayNow, hourNow;
bool RadiatorsOnOff = 0;
////////////////////////////// TIMERS //////////////////////////////
unsigned long currentMillis;
#define ds18b20interval 10000        // опрос датчика температуры каждую минуту (60 000мс) 
#define SendDataInterval 15000       // отсылка данных на хост каждые 3 минуты (180 000мс) 
#define ResetESPInterval 300000      // перезагрузка ESP через 5 минут после загрузки в АР режиме (300000мс) - должно хватить для настройки в режим клиента 
#define dispRefrinterval 5000        // обновление экрана каждые 5 секунд
#define ActivateRefresh 1000
#define sinhronizeTimeInterval 600000
#define DebugInterval 10000
long DebugMillis = 0;
long sinhronizeTimeMillis = 0;
long ActivateRefreshMillis = 0;
long SendDataMillis = 0;
long ResetESPMillis = 0;
long dispMillis = 0;
long ds18b20readMillis = 0;          // счетчик прошедшего времени для интервала чтения с датчика температуры
////////////////////////////// GPIO //////////////////////////////
#define PinButtons 0
bool     button_state      = false;
bool     button_auto_state = false;
uint32_t ms_button         = 0;
uint32_t ms_auto_click     = 0;
////////////////////////////// PROGRAMS //////////////////////////////
int d=1;
//                        |вс|пн|вт|ср|чт|пт|сб|
int modeProg    [ 7 ]  = { 2, 1, 1, 1, 1, 1, 2 };   // массив опраделяющий в какой из дней недели работает программа №1, №2, №3, №4 начиная с воскресенья
//                        |0 |1 |2 |3 |4 |5 |6 |7 |8 |9 |10|11|12|13|14|15|16|17|18|19|20|21|22|23|
const int Prog1 [ 24 ] = { 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
const int Prog2 [ 24 ] = { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 };
const int Prog3 [ 24 ] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
const int Prog4 [ 24 ] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
