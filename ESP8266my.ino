//------------------------------------------------------------------------------------------------------------------------------------
//управление ПВК v.2.6 (добавлено: восстановление состояний реле, MQTT, Viber, коррекция температуры мультипликативная, аддитивная)
//основной канал автора на ютубе  "НеОбзор58"            https://www.youtube.com/channel/UC6mMZ4GGXMdpSGEy-j1EnxQ
//второй   канал автора на ютубе  "Доступная автоматика" https://www.youtube.com/channel/UCxfwRP66zE4zwn6lgvS6wQg
//сайт и страница проекта                                http://www.simple-automation.ru/publ/proekty/kontroller_dlja_pvk_na_baze_esp8266_nodemcu/kontroller-dlja-pvk-na-baze-esp8266-nodemcu-lua/15-1-0-10
//
//     желающим поддержать автора: карта Сбера 676280489001157828 получатель Григорий Валерьевич Ц.
//
//------------------------------------------------------------------------------------------------------------------------------------

//#define USE_LOG
//#define USE_LCD
//#define USE_IRREMOTE
#define USE_BMP280 // Use BMP280 Atmosphere Pressure sensor?
#define USE_VIBER // Use Viber Messager?

// ----------------------- BMP280 Declare --------------------------------------------------------------------------------------------
#ifdef USE_BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP280 bme;

float bmePressure, bmePressure_now;
#endif

//----------общие переменные и константы----------------------------------------------------------------------------------------------
//назначаем пины
const byte   D1_pin PROGMEM = D1;      //GPIO5
const byte swt1_pin PROGMEM = D0;
const byte swt2_pin PROGMEM = D5;      //GPIO16
const byte swt3_pin PROGMEM = D2;      //GPIO4
const byte RECV_PIN PROGMEM = D3;      //GPIO0
const byte pinBuiltinLed PROGMEM = D4; //GPIO2
const byte pinSDA PROGMEM = D5;
const byte pinSCL PROGMEM = D6;

//имена файлов настроек
const String SensorConfFile = "sensor.cfg";
const String NameMsgFile = "message.cfg";
const String NameSettingsFile = "settings.cfg";
const String NameResumeStateFile = "resumeState.cfg";

//----------работа с wi-fi файловой системой EEPROM-----------------------------------------------------------------------------------
#include <FS.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <EEPROM.h>
ESP8266WebServer server(80);
bool ApMode, AccessMode;
String AccessLogin, AccessPassword;
String ssid, password, domain;
uint8_t ip1, ip2, ip3, ip4;
uint8_t ms1, ms2, ms3, ms4;
uint8_t gt1, gt2, gt3, gt4;
uint8_t dn1, dn2, dn3, dn4;
byte arduino_mac[] = { 0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

const char* const ssidAP PROGMEM = "ESP_Control";
const char* const passwordAP PROGMEM = "Pa$$w0rd";

const char configSign[4] = { '#', 'G', 'R', 'S' };
const byte maxStrParamLength = 32;

char PerevodStr = 0x0D;
char VozvrStr = 0x0A;

//----MQTT----------------------------------------------------------------------------------------------------------------
//1. бесплатный mqtt сервер после регистрации www.cloudmqtt.com
//2. после регистрации нужно добавить двух пользователей, одного для есп, дрогого для телеф
//3. клиент для андроид в гугл плей (IoT MQTT Dashboard) https://play.google.com/store/apps/details?id=com.thn.iotmqttdashboard&hl=ru
//4. клиенту нужно разрешить/подписать на temp/# (temp/t0, temp/t1....) и добавить значения в subscribe
//5. клиенту нужно разрешить/подписать на swt/# (swt/0, swt/1,swt/3) и добавить движки в publish

#include <PubSubClient.h>// MQTT library
WiFiClient espClient;
PubSubClient mqttClient(espClient);
bool useMQTT;
String mqttServer, mqttUser, mqttUserPassword, mqttClientId;
uint16_t mqttServerPort;

// ----------------------- Viber Declare ------------------------------------------------------------------------------------------
#ifdef USE_VIBER
#include <ESP8266HTTPClient.h>

bool useViber;

String viberURL, viberAuthToken, viberUserId;
uint32_t viberPeriodic, nextTimeViber;

String json_obj;

HTTPClient http;

#endif

//-----------датчики температуры------------------------------------------------------------------------------------------
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D1
#define TEMPERATURE_PRECISION 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

char chGrad;
String stGrad;
const uint8_t NSenseMax = 6;
uint8_t NSenseFact;
byte insideThermometer[NSenseMax][8];

float tempC[NSenseMax], tempC_mqtt[NSenseMax], tempC_KX[NSenseMax];
float tempC_now[NSenseMax];
int8_t t[NSenseMax];//используется датчик или нет
String tNameSens[NSenseMax];//имя датчика
float tdK[NSenseMax];//мультипликативная составляющая%
float tdX[NSenseMax];//аддитивная составляющая в градусах

uint8_t error_read_ds_Max;//количество ошибок (подряд) при опросе
uint16_t error_read_ds[NSenseMax], error_read_ds_all, error_read_correct_ds[NSenseMax], error_read_correct_ds_all;
uint16_t t_msec_get_ds;//интервал опроса датчиков, Мсек
uint8_t Zaderj, jamp_t;//задержка в опросе датчиков 0-50 мсек, и скор из температуры за опрос 0-20 град

//сообщения о достижении температуры
const int8_t NomMessMax = 20;
int8_t NomMessAll;
struct str_mesTemp {
  uint8_t NsenseM;// номер датчика сигнала
  float     TempM;// температура сигнала
  String  WavFile;// звук.сообщение
  String  Message;// сообщение
  bool       Need;// использовать да/нет
  bool    accompl;// сработало да/нет
};
str_mesTemp mesTemp[NomMessMax];

//------------нагрев-------------------------------------------------------------------------------------------------------
#include <PID_v1.h>
float TkVol, Prg_TkVol, Tk_now;
uint8_t ModeWarm, Prg_ModeWarm; //режим нагрева 1-3
uint8_t Nsense, Prg_Nsense; //номер датчика для регулировки нагрева
uint8_t WarmVol, Prg_WarmVol; //0-100%
uint32_t Prg_WarmTime, OldWarmWorkTime;
uint8_t  WarmHour, WarmMin, WarmSec;
uint32_t t_control_now, t_control;
uint32_t t_work_warm, t_work_warm_ModeWarm, reachT, t_warm, t_pwm_on, t_pwm_off;
String strtworkwarm;
int8_t TSec;//период PWM в сек 0-255
int8_t erSt;//ошибки от 0-10
int8_t power_ten;
bool StatusWarm;

float TWarmContr, Prg_TWarmContr, TWarmContr_now;
int8_t NsenseWarmContr, Prg_NsenseWarmContr;
bool TimerWarmAvailSt;
int8_t TimerWarmDaySt, TimerWarmMonthSt, TimerWarmHourSt, TimerWarmMinSt, TimerWarmSecSt;
int16_t TimerWarmYearSt;
uint32_t TimerWarmStUnx;

bool TimerWarmAvailEnd;
int8_t TimerWarmDayEnd, TimerWarmMonthEnd, TimerWarmHourEnd, TimerWarmMinEnd, TimerWarmSecEnd;
int16_t TimerWarmYearEnd;
uint32_t TimerWarmEndUnx;
//PID
double Setpoint, Input, Output;
float gap;
// Определяем агрессивные и консервативные параметры PID управления
//float aggKp = 4, aggKi = 0.2, aggKd = 1;
//float consKp = 1, consKi = 0.05, consKd = 0.25;
double aggKp, aggKi, aggKd;
double consKp, consKi, consKd;
// Определяем начальные параметры согласно библиотеке
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);

//-----------отбор---------------------------------------------------------------------------------------------------------
int8_t NsenseOtbContr, Prg_NsenseOtbContr;
uint32_t t_otb, t_work_otb, t_pwm_on_otb , t_pwm_off_otb;
float TstOtb, TendOtb, Prg_TstOtb, Prg_TendOtb, Tk_otb;
String strtworkotb;
uint8_t PercOtb;
uint8_t TimeOtbPeriod;

//----------миксер---------------------------------------------------------------------------------------------------------
uint32_t t_work_mix, t_mix, t_pow_on, t_pow_off;
String TimeOn, strtworkmix;
float TMixContr_now;
uint8_t MixOnHour, MixOnMin, MixOnSec, MixOffHour, MixOffMin, MixOffSec, MixHour, MixMin, MixSec, TMixContr, NsenseMixContr;
uint8_t Prg_TMixContr, Prg_NsenseMixContr;
uint32_t Prg_MixWorkTime, Prg_MixStopTime, Prg_MixTime;
const uint8_t NomPrerMixAll = 5; //количество остановов миксера

struct prerMix {
  bool    Avail;
  uint8_t PrerMixHourSt;//
  uint8_t PrerMixHourEnd;//
  uint8_t PrerMixMinSt;//
  uint8_t PrerMixMinEnd;//
  uint32_t PrerMixStUnx;
  uint32_t PrerMixEndUnx;
};
prerMix PrerMix[NomPrerMixAll];

bool TimerMixAvailSt;
int8_t TimerMixDaySt, TimerMixMonthSt, TimerMixHourSt, TimerMixMinSt, TimerMixSecSt;
int16_t TimerMixYearSt;
uint32_t TimerMixStUnx;

bool TimerMixAvailEnd;
int8_t TimerMixDayEnd, TimerMixMonthEnd, TimerMixHourEnd, TimerMixMinEnd, TimerMixSecEnd;
int16_t TimerMixYearEnd;
uint32_t TimerMixEndUnx;

//----------управление реле--------------------------------------------------------------------------------------------------
bool autoMode;
bool relay1Level, relay2Level, relay3Level;
bool Prg_swt1, Prg_swt2, Prg_swt3;
bool prev_swt1, prev_swt2, prev_swt3;
bool resumeState;

//--------программный режим----------------------------------------------------------
bool Prg, Prg_accomp;
uint8_t NumStrPrgAll;
uint8_t NumStrPrg, PrevNumStrPrg;
String NameProg;
int8_t KeyPress;

struct stepProgr
{
  uint8_t            N;  // Номер строки программы
  bool             WOn;  // Использовать нагрев
  uint8_t         WPow;  // мощность тэна
  float            WTk;  // температура нагрева
  uint8_t        WMode;  // режим нагрева:удержание,фикс.мощн
  uint8_t          WNs;  // какой датчик использовать для нагрева
  float            WTC;  // температура аварии
  uint8_t         WNsC;  // какой датчик использовать для аварии
  uint32_t       WTime;  // время нагрева

  bool            MOn;  // Использовать миксер
  uint8_t        MOnS;  // время ВКЛ
  uint8_t       MOffS;  // время ВЫКЛ
  uint32_t      MTime;  // время работы
  uint8_t        MNsC;  // какой датчик использовать для миксера
  float           MTC;  // температура до которой работает миксер

  bool            OOn;  // Использовать клапан отбора
  uint8_t        ONsC;  // какой датчик использовать для отбора
  float          OTst;  // температура ВКЛ
  float         OTend;  // температура ВЫКЛ

  uint8_t       Contr;  // контроль выполнения: по нагреву, по миксеру
  uint8_t       NextN;  // переход к следующему шагу: выдать предупреждение и ждать подтверждения, просто перейти
  String         Mess;  // сообщение

  bool         WCompl;  // fileStrData[22] -шаг по нагреву исполнен
  bool         MCompl;  // fileStrData[23] -шаг по мешалке исполнен
  bool        inProgr;  // fileStrData[24] -начато выполнение
  bool        respGet;  // fileStrData[25] -получен ответ на сообщение
  uint8_t     statErr;  // fileStrData[26] -статус ошибки
};

const int8_t NumStrPrgMax = 30;

stepProgr Prog[NumStrPrgMax];

//------------работа со временем--------------------------------------------------------------
extern "C" {
#include <sntp.h>
}
#include "Date.h";

uint32_t startTime, startMs, nextTime;
String ntpServer1, ntpServer2, ntpServer3;
uint32_t updateInterval;
int8_t timeZone;
const char* const strNever PROGMEM = "NoNTP";
const char* const defNtpServer PROGMEM = "pool.ntp.org";
const uint32_t defUpdateInterval = 3600; // 1 hour
const int8_t defTimeZone = 3; // GMT+3 Moscow TZ
String timeStr;
const uint32_t noTime = (uint32_t)0;
const char* const noDef = '\0';

bool ntpUpd;
int8_t now_hour, now_min, now_sec, now_day, now_month;
uint8_t now_wd;
int16_t now_year;
uint32_t now_timeUnx;

//------используемые устройства--------------------------------------------------
#ifdef USE_LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // Устанавливаем дисплей (0x27)
uint32_t LCD_control;
#endif

#ifdef USE_IRREMOTE
#include <IRremoteESP8266.h>
#include <IRutils.h>
#include <IRrecv.h>
IRrecv irrecv(RECV_PIN);
decode_results results;
uint32_t t_ik;//присваивается значения от millis()
#endif

//-------------------------------------------------------------------------------------------------------------------------------------------
void MydigitalWrite(int pin, bool state)
{
  if (digitalRead(pin) != state) digitalWrite(pin, state);
}
//--------------------------------------------------------------
String quoteEscape(const String& str)
{
  String result = "";
  int start = 0, pos;

  while (start < str.length()) {
    pos = str.indexOf('"', start);
    if (pos != -1) {
      result += str.substring(start, pos) + F("&quot;");
      start = pos + 1;
    } else {
      result += str.substring(start);
      break;
    }
  }
  return result;
}
//---------------------------------------------
bool readConfig()
{
  uint16_t offset = 0;
  Serial.println(F("Reading config from EEPROM"));
  for (byte i = 0; i < sizeof(configSign); i++)  {
    if (EEPROM.read(offset + i) != configSign[i])
      return false;
  }
  offset += sizeof(configSign);
  offset = readEEPROMString(offset, ssid);
  offset = readEEPROMString(offset, password);
  offset = readEEPROMString(offset, AccessLogin);
  offset = readEEPROMString(offset, AccessPassword);
  offset = readEEPROMString(offset, NameProg);

  EEPROM.get(offset, ApMode); offset += sizeof(ApMode);
  EEPROM.get(offset, AccessMode); offset += sizeof(AccessMode);

  EEPROM.get(offset, ip1);       offset += sizeof(ip1);
  EEPROM.get(offset, ip2);       offset += sizeof(ip2);
  EEPROM.get(offset, ip3);       offset += sizeof(ip3);
  EEPROM.get(offset, ip4);       offset += sizeof(ip4);

  EEPROM.get(offset, ms1);       offset += sizeof(ms1);
  EEPROM.get(offset, ms2);       offset += sizeof(ms2);
  EEPROM.get(offset, ms3);       offset += sizeof(ms3);
  EEPROM.get(offset, ms4);       offset += sizeof(ms4);

  EEPROM.get(offset, gt1);       offset += sizeof(gt1);
  EEPROM.get(offset, gt2);       offset += sizeof(gt2);
  EEPROM.get(offset, gt3);       offset += sizeof(gt3);
  EEPROM.get(offset, gt4);       offset += sizeof(gt4);

  EEPROM.get(offset, dn1);       offset += sizeof(dn1);
  EEPROM.get(offset, dn2);       offset += sizeof(dn2);
  EEPROM.get(offset, dn3);       offset += sizeof(dn3);
  EEPROM.get(offset, dn4);       offset += sizeof(dn4);

  return true;
}
//-------------------------------------
void writeConfig()
{
  uint16_t offset = 0;

  Serial.println(F("Writing config to EEPROM"));
  EEPROM.put(offset, configSign);

  offset += sizeof(configSign);
  offset = writeEEPROMString(offset, ssid);
  offset = writeEEPROMString(offset, password);
  offset = writeEEPROMString(offset, AccessLogin);
  offset = writeEEPROMString(offset, AccessPassword);
  offset = writeEEPROMString(offset, NameProg);

  EEPROM.put(offset, ApMode); offset += sizeof(ApMode);
  EEPROM.put(offset, AccessMode); offset += sizeof(AccessMode);

  EEPROM.put(offset, ip1); offset += sizeof(ip1);
  EEPROM.put(offset, ip2); offset += sizeof(ip2);
  EEPROM.put(offset, ip3); offset += sizeof(ip3);
  EEPROM.put(offset, ip4); offset += sizeof(ip4);

  EEPROM.put(offset, ms1);       offset += sizeof(ms1);
  EEPROM.put(offset, ms2);       offset += sizeof(ms2);
  EEPROM.put(offset, ms3);       offset += sizeof(ms3);
  EEPROM.put(offset, ms4);       offset += sizeof(ms4);

  EEPROM.put(offset, gt1);       offset += sizeof(gt1);
  EEPROM.put(offset, gt2);       offset += sizeof(gt2);
  EEPROM.put(offset, gt3);       offset += sizeof(gt3);
  EEPROM.put(offset, gt4);       offset += sizeof(gt4);

  EEPROM.put(offset, dn1);       offset += sizeof(dn1);
  EEPROM.put(offset, dn2);       offset += sizeof(dn2);
  EEPROM.put(offset, dn3);       offset += sizeof(dn3);
  EEPROM.put(offset, dn4);       offset += sizeof(dn4);

  EEPROM.commit();
}
//-----------------------------------------------------------------------
uint16_t readEEPROMString(uint16_t offset, String& str)
{
  char buffer[maxStrParamLength + 1];
  buffer[maxStrParamLength] = 0;
  for (byte i = 0; i < maxStrParamLength; i++) {
    if (! (buffer[i] = EEPROM.read(offset + i)))
      break;
  }
  str = String(buffer);
  return offset + maxStrParamLength;
}
//-----------------------------------------------------------------------
uint16_t writeEEPROMString(uint16_t offset, const String& str) {
  for (byte i = 0; i < maxStrParamLength; i++) {
    if (i < str.length())
      EEPROM.write(offset + i, str[i]);
    else
      EEPROM.write(offset + i, 0);
  }
  return offset + maxStrParamLength;
}
//-------------------------------------------------------------------------------------------------
//---------------------------WiFi setup functions--------------------------------------------------
//-------------------------------------------------------------------------------------------------
bool setupWiFiAsStation() {
  const uint32_t timeout = 40000;
  uint32_t maxtime = millis() + timeout;

  WiFi.mode(WIFI_STA);

  if (ssid.length() == 0) return false;

  Serial.println(F("Connecting to "));
  Serial.println(ssid);

#ifdef USE_LCD
  lcd.setCursor(0, 0);
  lcd.print(F("Connecting to   "));
  lcd.setCursor(0, 1);
  lcd.print(ssid + F("          "));
#endif

  WiFi.begin(ssid.c_str(), password.c_str());

  if ((ip1 + ip2 + ip3 + ip4) != 0)
  {
    IPAddress ip(ip1, ip2, ip3, ip4);
    IPAddress subnet(ms1, ms2, ms4, ms4);
    IPAddress dns(dn1, dn2, dn3, dn4);
    IPAddress gateway(gt1, gt2, gt3, gt4);

    WiFi.config(ip, gateway, subnet, dns);

  }

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(pinBuiltinLed, LOW);
    delay(500);
    digitalWrite(pinBuiltinLed, HIGH);
    Serial.print(".");
    if (millis() >= maxtime) {
      Serial.println();
      Serial.println(ssid);
      //Serial.println(password);
      Serial.println(F(" fail!"));
      return false;
    }
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

#ifdef USE_LCD
  lcd.setCursor(0, 0);
  lcd.print(F("Mode: STA"));
  lcd.setCursor(0, 1);
  lcd.print(F("IP "));
  lcd.setCursor(3, 1);
  lcd.print(WiFi.localIP());
  delay(2500);
#endif



  return true;
}
//----------------------------------------------------------------
void setupWiFiAsAP()
{
  Serial.print(F("Configuring access point "));
  Serial.println(ssidAP);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssidAP, passwordAP);

  Serial.print(F("IP address: "));
  Serial.println(WiFi.softAPIP());

#ifdef USE_LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Mode: AP"));
  lcd.setCursor(0, 1);
  lcd.print(F("IP "));
  lcd.setCursor(3, 1);
  lcd.print(WiFi.softAPIP());
  delay(2000);
#endif

}
//----------------------------------------------------------------
void setupWiFi() {
  if (ApMode || (! setupWiFiAsStation())) setupWiFiAsAP();
  server.begin();
#ifdef USE_LCD
  lcd.setCursor(0, 0);
  lcd.print(F("HTTP started    "));
  delay(2000);
#endif
  Serial.println(F("HTTP started"));


}
//------------------------------------
String AddNull (String StrForAdd)
{
  if (StrForAdd.length() == 1)
    return "0" + StrForAdd;
  if (StrForAdd.length() == 0)
    return "00" + StrForAdd;

  return StrForAdd;
}
//--------------------------------------------------------------------------------------

#ifdef USE_VIBER
#include "viber.h"
#endif
#include "handles.h"
#include "h_switch.h"
#include "prg_modules.h"
#include "Control_mix.h"
#include "Control_warm.h"
#include "Control_otbor.h"
#include "upg_spiffs.h"
#include "Control_other.h"

//---------------------------------------------------------------------------------------
void openSettingsFile () {
#ifdef USE_LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Open:"));
  lcd.setCursor(0, 1);
  lcd.print(NameSettingsFile);
  delay(1500);
#endif

  if (!SPIFFS.exists("/" + NameSettingsFile))
  { //файл настроек не существует
#ifdef USE_LCD
    lcd.setCursor(0, 1);
    lcd.print("no file         ");
    delay(1000);
#endif

  } else {
    Serial.println(F("Открываем ")); Serial.println(NameSettingsFile);
    File f = SPIFFS.open("/" + NameSettingsFile, "r");
    if (!f) {
      Serial.println(F("..не получилось открыть файл"));
    } else {
      Serial.println(F("..читаем файл"));
      String s;
      uint16_t st_start, st_end, st_len;
      for (uint8_t i = 0; i < 20; i++)  {
        s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
        //s.remove(s.length() - 1);
        st_start = s.indexOf("{"); st_end = s.indexOf("}") + 1;

        if (s.indexOf(F("END")) == -1) {
          if ((st_start != -1) && (st_end != -1)) {
            s = s.substring(st_start, st_end); st_len = s.length();
#ifdef USE_LOG
            Serial.println(s);
#endif
            DynamicJsonBuffer jsonBuffer;   //Memory pool
            JsonObject& root = jsonBuffer.parseObject(s);
            if (root.success()) {
              int8_t hh, mm, ss;
              uint8_t wd;
              int8_t d, m;
              int16_t y;

              if (root["Vol"] == 0) {

                //Serial.println("Vol0");

                WarmVol = root["WarmVol"];
                TkVol = root["TkVol"];
                ModeWarm = root["ModeWarm"];
                consKp = root["consK"][0];
                consKi = root["consK"][1];
                consKd = root["consK"][2];
                aggKp = root["aggK"][0];
                aggKi = root["aggK"][1];
                aggKd = root["aggK"][2];
                gap = root["gap"];
                TSec = root["TSec"];
                WarmHour = root["WarmTime"][0];
                WarmMin = root["WarmTime"][1];
                WarmSec = root["WarmTime"][2];
                Nsense = root["Nsense"];
                TWarmContr = root["TWarmContr"];
                NsenseWarmContr = root["NsenseWarmContr"];

                TimerWarmAvailSt = root["TimerWarmAvailSt"];
                TimerWarmAvailEnd = root["TimerWarmAvailEnd"];
                TimerWarmStUnx = root["TimerWarmStUnx"];
                TimerWarmEndUnx = root["TimerWarmEndUnx"];

                parseUnixTime(TimerWarmStUnx, TimerWarmHourSt, TimerWarmMinSt, TimerWarmSecSt, wd, TimerWarmDaySt, TimerWarmMonthSt, TimerWarmYearSt);
                parseUnixTime(TimerWarmEndUnx, TimerWarmHourEnd, TimerWarmMinEnd, TimerWarmSecEnd, wd, TimerWarmDayEnd, TimerWarmMonthEnd, TimerWarmYearEnd);

              }
              else if (root["Vol"] == 1) {
                //Serial.println("Vol1");
                MixOnHour = root["MixOnTime"][0];
                MixOnMin = root["MixOnTime"][1];
                MixOnSec = root["MixOnTime"][2];
                MixOffHour = root["MixOffTime"][0];
                MixOffMin = root["MixOffTime"][1];
                MixOffSec = root["MixOffTime"][2];
                MixHour = root["MixTime"][0];
                MixMin = root["MixTime"][1];
                MixSec = root["MixTime"][2];
                TMixContr = root["TMixContr"];
                NsenseMixContr = root["NsenseMixContr"];


                for (byte i = 0; i < NomPrerMixAll; i++) {
                  PrerMix[i].Avail = root["Avail" + String(i)];
                  PrerMix[i].PrerMixStUnx = root["PrerMixStUnx" + String(i)];
                  PrerMix[i].PrerMixEndUnx = root["PrerMixEndUnx" + String(i)];
                  parseUnixTime(PrerMix[i].PrerMixStUnx, hh, mm, ss, wd, d, m, y);
                  PrerMix[i].PrerMixHourSt = hh;
                  PrerMix[i].PrerMixMinSt = mm;
                  parseUnixTime(PrerMix[i].PrerMixEndUnx, hh, mm, ss, wd, d, m, y);
                  PrerMix[i].PrerMixHourEnd = hh;
                  PrerMix[i].PrerMixMinEnd = mm;
                }
                TimerMixAvailSt = root["TimerMixAvailSt"];
                TimerMixAvailEnd = root["TimerMixAvailEnd"];
                TimerMixStUnx = root["TimerMixStUnx"];
                TimerMixEndUnx = root["TimerMixEndUnx"];

                parseUnixTime(TimerMixStUnx, TimerMixHourSt, TimerMixMinSt, TimerMixSecSt, wd, TimerMixDaySt, TimerMixMonthSt, TimerMixYearSt);
                parseUnixTime(TimerMixEndUnx, TimerMixHourEnd, TimerMixMinEnd, TimerMixSecEnd, wd, TimerMixDayEnd, TimerMixMonthEnd, TimerMixYearEnd);
              }
              else if (root["Vol"] == 2) {
                //Serial.println("Vol2");
                PercOtb = root["PercOtb"];
                TimeOtbPeriod = root["TimeOtbPeriod"];
                TstOtb = root["TstOtb"];
                TendOtb = root["TendOtb"];
                NsenseOtbContr = root["NsenseOtbContr"];
              }
              else if (root["Vol"] == 3) {
                //Serial.println("Vol3");
                resumeState = root["resumeState"];
                relay1Level = root["relayLevel"][0];
                relay2Level = root["relayLevel"][1];
                relay3Level = root["relayLevel"][2];
                const char* ntpServer = root["ntpServer"][0]; if (ntpServer != noDef) ntpServer1 = String(ntpServer);
                ntpServer = root["ntpServer"][1]; if (ntpServer != noDef) ntpServer2 = String(ntpServer);
                ntpServer = root["ntpServer"][2]; if (ntpServer != noDef) ntpServer3 = String(ntpServer);
                updateInterval = root["updateInterval"];
                timeZone = root["timeZone"];
                ntpUpd = root["ntpUpd"];

                useMQTT = root["useMQTT"];
                const char* mqttS = root["mqttServer"]; if (mqttS != noDef) mqttServer = String(mqttS);
                mqttServerPort = root["mqttServerPort"];

                const char* mqttU = root["mqttUser"]; if (mqttU != noDef) mqttUser = String(mqttU);
                const char* mqttUP = root["mqttUserPassword"]; if (mqttUP != noDef) mqttUserPassword = String(mqttUP);
                const char* mqttC = root["mqttClientId"]; if (mqttC != noDef) mqttClientId = String(mqttC);

                useViber = root["useViber"];
                const char* vibUrl = root["viberURL"]; if (vibUrl != noDef) viberURL = String(vibUrl);
                viberPeriodic = root["viberPeriodic"];
                const char* vibAT = root["viberAuthToken"]; if (vibAT != noDef) viberAuthToken = String(vibAT);
                const char* vibUI = root["viberUserId"]; if (vibUI != noDef) viberUserId = String(vibUI);

                Zaderj = root["Zaderj"];
                jamp_t = root["jamp_t"];
                error_read_ds_Max = root["error_read_ds_Max"];
                t_msec_get_ds = root["t_msec_get_ds"];

              }
            } else {
              Serial.println(F("..Проблемы с парсингом файла"));
            }
          } else {
            Serial.println(F("..Не форматная строка в файле"));
          }
        } else { //нашли слово END в конце файла
          NomMessAll = i;
          Serial.println(F("..дошли до конца файла"));

#ifdef USE_LCD
          lcd.setCursor(6, 0);
          lcd.print("ok");
          delay(1500);

#endif
          break;
        }
      }
      f.close();
    }
  }
}
//------------------------------------------------------
void openTempMessFile() {
#ifdef USE_LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Open:"));
  lcd.setCursor(0, 1);
  lcd.print(NameMsgFile);
  delay(1500);
#endif

  if (!SPIFFS.exists("/" + NameMsgFile))
  { //файл настроек не существует
#ifdef USE_LCD
    lcd.setCursor(0, 1);
    lcd.print("no file         ");
    delay(1000);
#endif
  } else {
    Serial.println(F("Открываем ")); Serial.println(NameMsgFile);
    File f = SPIFFS.open("/" + NameMsgFile, "r");
    if (!f) {
      Serial.println(F("..не получилось открыть файл"));
    } else {
      Serial.println(F("..читаем файл"));
      String s;
      uint8_t st_start, st_end, st_len;
      for (uint8_t i = 0; i < NomMessMax; i++)  {
        s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
        st_start = s.indexOf("{"); st_end = s.indexOf("}") + 1;
#ifdef USE_LOG
        Serial.println(s);
#endif
        if (s.indexOf(F("END")) == -1) {
          if ((st_start != -1) && (st_end != -1)) {
            s = s.substring(st_start, st_end); st_len = s.length();
            DynamicJsonBuffer jsonBuffer;   //Memory pool
            JsonObject& root = jsonBuffer.parseObject(s);
            if (root.success()) {
              mesTemp[i].Need = root["Need"];
              mesTemp[i].NsenseM = root["NsenseM"];
              mesTemp[i].TempM = root["TempM"];
              const char* WavFile = root["WavFile"]; if (WavFile != noDef) mesTemp[i].WavFile = String(WavFile);
              const char* Message = root["Message"]; if (Message != noDef) mesTemp[i].Message = String(Message);


            } else {
              Serial.println(F("..проблемы с парсингом"));
            }
          } else {
            Serial.println(F("..не форматная строка в файле"));
          }
        } else { //нашли слово END в конце файла
          NomMessAll = i;
          Serial.println(F("..дошли до конца файла"));
#ifdef USE_LCD
          lcd.setCursor(6, 0);
          lcd.print(F("ok"));
          delay(1500);
#endif
          break;
        }
      }
      f.close();
    }
  }
}
//------------------------------------------------------
void openSensorConfFile()
{
#ifdef USE_LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Open:"));
  lcd.setCursor(0, 1);
  lcd.print(SensorConfFile);
  delay(1500);
#endif

  if (!SPIFFS.exists("/" + SensorConfFile))
  { //файл настроек не существует
#ifdef USE_LCD
    lcd.setCursor(0, 1);
    lcd.print("no file         ");
    delay(1000);
#endif
  }
  else {
    Serial.println(F("Открываем ")); Serial.println(SensorConfFile);
    File f = SPIFFS.open("/" + SensorConfFile, "r");
    if (!f) {
      Serial.println(F("..не получилось открыть файл"));
    }
    else {
      Serial.println(F("..читаем файл"));
      String s;
      uint8_t st_start, st_end, st_len;
      for (uint8_t i = 0; i < NSenseMax; i++)  {
        s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
        st_start = s.indexOf(F("{")); st_end = s.indexOf(F("}")) + 1;
#ifdef USE_LOG
        Serial.println(s);
#endif
        if (s.indexOf(F("END")) == -1) {
          if ((st_start != -1) && (st_end != -1)) {
            s = s.substring(st_start, st_end); st_len = s.length();
            DynamicJsonBuffer jsonBuffer;   //Memory pool
            JsonObject& root = jsonBuffer.parseObject(s);
            if (root.success()) {
              t[i] = root["t"];
              for (uint8_t k = 0; k < 8; k++) {
                insideThermometer[i][k] = root["frame"][k];
              }
              const char* tNameS = root["tNameSens"]; if (tNameS != noDef) tNameSens[i] = String(tNameS);
              tdK[i] = root["tdK"];
              tdX[i] = root["tdX"];
            }
            else {
              Serial.println(F("..проблемы с парсингом"));
            }
          }
          else {
            Serial.println(F("..не форматная строка"));
          }
        }
        else { //нашли слово END в конце файла
          NSenseFact = i;
          Serial.println(F("..дошли до конца файла"));
          Serial.print(F("..всего датчиков в файле = ")); Serial.println(NSenseFact);
#ifdef USE_LCD
          lcd.setCursor(6, 0);
          lcd.print(F("ok"));
          delay(1500);
          lcd.clear();
#endif
          break;
        }
      }
      f.close();
    }
  }
}
//------------------------------------------------------
//------------------------------------------------------
void openResumeStateFile()
{
  if (resumeState == 1) {

    if (!SPIFFS.exists("/" + NameResumeStateFile))
    { //файл настроек не существует
    }
    else {
      Serial.println(F("Открываем ")); Serial.println(NameResumeStateFile);
      File f = SPIFFS.open("/" + NameResumeStateFile, "r");
      if (!f) {
        Serial.println(F("..не получилось открыть файл"));
      }
      else {
        Serial.println(F("..читаем файл"));
        String s;
        uint8_t st_start, st_end, st_len;
        for (uint8_t i = 0; i < 20; i++)  {
          s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
          st_start = s.indexOf(F("{")); st_end = s.indexOf(F("}")) + 1;
#ifdef USE_LOG
          Serial.println(s);
#endif
          if (s.indexOf(F("END")) == -1) {
            if ((st_start != -1) && (st_end != -1)) {
              s = s.substring(st_start, st_end); st_len = s.length();
              DynamicJsonBuffer jsonBuffer;   //Memory pool
              JsonObject& root = jsonBuffer.parseObject(s);
              if (root.success()) {
                autoMode = root["autoMode"];
                Prg_swt1 = root["rele1"];
                Prg_swt2 = root["rele2"];
                Prg_swt3 = root["rele3"];

              }
              else {
                Serial.println(F("..проблемы с парсингом"));
              }
            }
            else {
              Serial.println(F("..не форматная строка"));
            }
          }
          else { //нашли слово END в конце файла

            Serial.println(F("..дошли до конца файла"));
            Serial.println(F("..состояние реле восстановлено"));
            break;
          }
        }
        f.close();

      }
    }
  }
}
//-----------------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  Serial.println();

#ifdef USE_IRREMOTE
  irrecv.enableIRIn(); // Start the receiver
#endif

#ifdef USE_LCD
  Wire.begin(pinSDA, pinSCL);
  lcd.begin(pinSDA, pinSCL);
  //lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  lcd.setCursor(1, 0);
  lcd.print(F("www.simple-"));
  lcd.setCursor(2, 1);
  lcd.print(F("automation.ru"));
  delay(3000);
#endif

  chGrad = (char)49840; stGrad = chGrad; stGrad = stGrad + F("C");


  pinMode(pinBuiltinLed, OUTPUT);
  pinMode(swt1_pin, OUTPUT);  //digitalWrite(swt1_pin, !LOW);
  pinMode(swt2_pin, OUTPUT);  //digitalWrite(swt2_pin, !LOW);
  pinMode(swt3_pin, OUTPUT);  //digitalWrite(swt3_pin, !LOW);

  prev_swt1 = LOW;
  prev_swt2 = LOW;
  prev_swt3 = LOW;
  Prg == false;
  t_work_mix = 0; t_pow_on = 0; t_pow_off = 0;

  t_control = 0;
  power_ten = 0;

  t_pwm_on = 0;
  t_pwm_off = 0;

  t_work_otb = 0;
  t_otb = 0;
  t_pwm_on_otb = 0;
  t_pwm_off_otb = 0;

  for (byte i = 0; i < NSenseMax; i++) {
    tempC[i] = -127;
    tempC_now[i] = -127;
  }
  erSt = 0;

  //error_read_ds = 0;
  error_read_ds_all = 0;
  error_read_correct_ds_all = 0;




  EEPROM.begin(1024);
  if (! readConfig())
  {
    Serial.println(F("EEPROM is empty!"));
    digitalWrite(swt1_pin, LOW);
    digitalWrite(swt2_pin, !LOW);
    digitalWrite(swt3_pin, !LOW);

  }
  else
  {
    if (relay1Level == 1) digitalWrite(swt1_pin, LOW);
    if (relay1Level == 0) digitalWrite(swt1_pin, HIGH);

    if (relay2Level == 1) digitalWrite(swt2_pin, LOW);
    if (relay2Level == 0) digitalWrite(swt2_pin, HIGH);

    if (relay3Level == 1) digitalWrite(swt3_pin, LOW);
    if (relay3Level == 0) digitalWrite(swt3_pin, HIGH);
  }

  setupWiFi();

#ifdef USE_BMP280
    Wire.begin(D3, D6);
    delay(10);
    bme.begin(0x76);  
    delay(10);
#endif

  //-------------------------------------------------

  //  server.begin();

  server.on("/", handleRoot);
  server.on("/index.html", handleRoot);
  server.on("/switch", h_switch);
  server.on("/select", h_select);
  server.on("/selectProm", h_selectProm);
  server.on("/mixer", h_mixer);
  server.on("/save", h_save);
  server.on("/save_m", h_save_m);
  server.on("/save_kor", h_save_kor);

  server.on("/warm", h_warm);
  server.on("/reboot", h_reboot);
  server.on("/wifi", h_wifi);
  server.on("/mqtt", h_mqtt);
  #ifdef USE_VIBER
  server.on("/viber", h_viber);
  #endif
  server.on("/otbor", h_otbor);
  server.on("/data_mainPage", HTTP_GET, h_data_mainPage);
  server.on("/open_file", HTTP_GET, h_prg_open_file);
  server.on("/data_file", HTTP_GET, h_prg_fill_data);
  server.on("/alert", HTTP_GET, h_alert);

  server.on("/selprog", HTTP_GET, h_prog);
  server.on("/dispTemp", h_dispTemp);
  server.on("/dispTempProm", h_dispTempInf);
  server.on("/tempMess", HTTP_GET, h_tempMess);
  server.on("/data_tempMess", HTTP_GET, h_data_tempMess);
  server.on("/data_resetMess", HTTP_GET, h_data_resetMess);

  server.on("/save_prg", HTTP_GET, h_save_prg);

  server.on("/check", HTTP_GET, h_prg_check);
  server.on("/data_contr", HTTP_GET, h_data_check_working_prg);
  server.on("/data_tekStat", HTTP_GET, h_data_tekStat_prg);

  server.onNotFound(handleNotFound);
  server.on("/spiffs", HTTP_GET, handleSPIFFS);
  server.on("/spiffs", HTTP_POST, handleFileUploaded, handleFileUpload);
  server.on("/spiffs", HTTP_DELETE, handleFileDelete);
  server.on("/update", HTTP_GET, handleUpdate);
  server.on("/update", HTTP_POST, handleSketchUpdated, handleSketchUpdate);

  server.on("/timeConf", handleTimeConfig);

  server.on("/settime", handleSetTime);
  server.on("/gettimer", handleGetTimer);
  server.on("/data_settimer", handleSetTimer);

  if (! SPIFFS.begin())
  {
    Serial.println(F("Unable to mount SPIFFS!"));
    return;
  }
  openSettingsFile();
  openTempMessFile();
  openSensorConfFile();
  openResumeStateFile();

#ifdef USE_IRREMOTE
  t_ik = millis();
#endif
  myPID.SetSampleTime(1000);
  myPID.SetOutputLimits(0, 100);
  myPID.SetMode(AUTOMATIC);


  if (ntpServer1.length() < 2) ntpServer1 = FPSTR(defNtpServer);
  if (updateInterval < 60) updateInterval = defUpdateInterval;

  sntp_set_timezone(timeZone);
  if (ntpServer1.length()) sntp_setservername(0, (char*)ntpServer1.c_str());
  if (ntpServer2.length()) sntp_setservername(1, (char*)ntpServer2.c_str());
  if (ntpServer3.length()) sntp_setservername(2, (char*)ntpServer3.c_str());
  sntp_init();
  startTime = noTime;
  startMs = millis();
  now_timeUnx = 0;
}
//-------------------------------------------


void loop()
{
  const uint32_t timeout = 180000; // 3 min.
  static uint32_t nextTime = timeout;
  static uint32_t nextTimeMQTT = timeout;
  static uint32_t nextTimeBMP280 = 30000;
  uint32_t t_sec, vol_hour, vol_min, vol_sec;

  if ((!ApMode) && (WiFi.status() != WL_CONNECTED) && ((WiFi.getMode() == WIFI_STA) || ((int32_t)(millis() - nextTime) >= 0)))  {
    setupWiFi();
    nextTime = millis() + timeout;
  }
  server.handleClient();


  t_sec = millis() / 1000;
  vol_hour = t_sec / 60 / 60;
  vol_min = t_sec / 60 - vol_hour * 60;
  vol_sec = t_sec - vol_hour * 60 * 60 - vol_min * 60;
  TimeOn = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));

  vol_hour = t_work_mix / 60 / 60;
  vol_min = t_work_mix / 60 - vol_hour * 60;
  vol_sec = t_work_mix - vol_hour * 60 * 60 - vol_min * 60;
  strtworkmix = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));

  vol_hour = t_work_warm / 60 / 60;
  vol_min = t_work_warm / 60 - vol_hour * 60;
  vol_sec = t_work_warm - vol_hour * 60 * 60 - vol_min * 60;
  strtworkwarm = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));

  vol_hour = t_work_otb / 60 / 60;
  vol_min = t_work_otb / 60 - vol_hour * 60;
  vol_sec = t_work_otb - vol_hour * 60 * 60 - vol_min * 60;
  strtworkotb = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));

  if (Prg == true) {
    if (NumStrPrgAll < 3) {
      Prg = false;
    }
  }
  if (Prg == true) {
    KeyPress = 0;
    if (Prog[NumStrPrg].inProgr == 0)//если выполнение шага не начато
    {
      //---------Warm----------------
      Prg_swt1 = Prog[NumStrPrg].WOn;
      Prg_WarmVol = Prog[NumStrPrg].WPow;
      Prg_TkVol = Prog[NumStrPrg].WTk;
      Prg_ModeWarm = Prog[NumStrPrg].WMode;
      Prg_Nsense = Prog[NumStrPrg].WNs;
      Prg_TWarmContr = Prog[NumStrPrg].WTC;
      Prg_NsenseWarmContr = Prog[NumStrPrg].WNsC;
      Prg_WarmTime = Prog[NumStrPrg].WTime;
      //----------Mix----------------
      Prg_swt2 = Prog[NumStrPrg].MOn;
      Prg_MixWorkTime = Prog[NumStrPrg].MOnS;
      Prg_MixStopTime = Prog[NumStrPrg].MOffS;
      Prg_MixTime = Prog[NumStrPrg].MTime;
      Prg_NsenseMixContr = Prog[NumStrPrg].MNsC;
      Prg_TMixContr = Prog[NumStrPrg].MTC;
      //---------Otb----------------
      Prg_swt3 = Prog[NumStrPrg].OOn;
      Prg_NsenseOtbContr = Prog[NumStrPrg].ONsC;
      Prg_TstOtb = Prog[NumStrPrg].OTst;
      Prg_TendOtb = Prog[NumStrPrg].OTend;

      Prog[NumStrPrg].inProgr = 1;//начали
      Serial.println(F("start prg"));
    }

    if (Prog[NumStrPrg].Contr == 0) { //контроль выполнения по нагреву 0
      if  (Prog[NumStrPrg].WCompl == 1) { //шаг по нагреву исполнен  переходим на след шаг
        Serial.print(NumStrPrg); Serial.print(" of "); Serial.println(NumStrPrgAll);
        if (NumStrPrg == NumStrPrgAll - 1) { //дошли до конца программы все выключаем
          Prg = false; Prg_accomp = true; Prg_swt1 = LOW; Prg_swt2 = LOW; Prg_swt3 = LOW;
          Serial.println(F("end prg"));
        }
        else {
          if (Prog[NumStrPrg].NextN == 0) { //переход к след шагу выдать предупреждение и ждать
            if  (Prog[NumStrPrg].respGet == 1) { //если получен ответ на сообщение переходим дальше
              Serial.println(F("next step prg after message"));
              Prg_fillData(1);
            }
            else { //пока ждем все выключаем
              Serial.println(F("wait press OK"));
              Prg_swt1 = LOW; Prg_swt2 = LOW; Prg_swt3 = LOW;
            }
          }
          else { //просто перейти
            Serial.println(F("next step prg"));
            Prg_fillData(1);
          }
        }
      }
    }
    else { //контроль выполнения по мешалке 1
      if  (Prog[NumStrPrg].MCompl == 2) { //шаг по миксеру исполнен
        Serial.print(NumStrPrg); Serial.print(F(" of ")); Serial.println(NumStrPrgAll);
        if (NumStrPrg == NumStrPrgAll - 1) {//дошли до конца программы все выключаем
          Prg = false; Prg_accomp = true; Prg_swt1 = LOW; Prg_swt2 = LOW; Prg_swt3 = LOW;
          Serial.println(F("mix end prg"));
        }
        else {
          if (Prog[NumStrPrg].NextN == 0) { //переход к след шагу выдать предупреждение и ждать

            if  (Prog[NumStrPrg].respGet == 1) { //если получен ответ на сообщение переходим дальше
              Serial.println(F("mix next step prg after message"));
              Prg_fillData(1);
            }
            else { //пока ждем все выключаем
              Serial.println(F("mix wait press OK"));
              Prg_swt1 = LOW; Prg_swt2 = LOW; Prg_swt3 = LOW;
            }
          }
          else { //просто перейти
            Serial.println(F("mix next step prg"));
            Prg_fillData(1);
          }
        }
      }
    }
  }
  else {
    //---Warm---
    Prg_WarmVol = WarmVol;
    Prg_TkVol = TkVol;
    Prg_ModeWarm = ModeWarm;
    Prg_Nsense = Nsense ;
    Prg_TWarmContr = TWarmContr;
    Prg_NsenseWarmContr = NsenseWarmContr;
    Prg_WarmTime = WarmHour * 60 * 60 + WarmMin * 60 + WarmSec;
    //---Mix---
    Prg_MixWorkTime = MixOnHour * 60 * 60 + MixOnMin * 60 + MixOnSec;
    Prg_MixStopTime = MixOffHour * 60 * 60 + MixOffMin * 60 + MixOffSec;
    Prg_MixTime = MixHour * 60 * 60 + MixMin * 60 + MixSec;
    Prg_NsenseMixContr = NsenseMixContr;
    Prg_TMixContr = TMixContr;
    //---Otb---
    Prg_NsenseOtbContr = NsenseOtbContr;
    Prg_TstOtb = TstOtb;
    Prg_TendOtb = TendOtb;
  }

  working_Mix();
  working_Warm();
  working_Otbor();
  working_other();

#ifdef USE_IRREMOTE

  //uint64_t vk1=0x10;//0xE0E0629D;
  //uint64_t vk2=0x810;//0xE0E0629D;
  //uint64_t vk3=0x410;//0xE0E0629D;

  if ((millis() - t_ik) >= 800) {
    if (irrecv.decode(&results)) {
      serialPrintUint64(results.value, HEX);
      Serial.println();

      if (results.value == 0x10) Prg_swt1 = !Prg_swt1;
      if (results.value == 0x810) Prg_swt2 = !Prg_swt2;
      if (results.value == 0x410) Prg_swt3 = !Prg_swt3;
      if (results.value == 0xA90) {
        Prg_swt1 = LOW;
        Prg_swt2 = LOW;
        Prg_swt3 = LOW;
      }
      irrecv.resume(); // Receive the next value
    }
    t_ik = millis();
  }
  delay (10);
#endif

  if ((WiFi.getMode() == WIFI_STA) && (WiFi.status() == WL_CONNECTED) && (ntpUpd)) {
    static uint32_t nextTime = millis();
    if ((nextTime != noTime) && (millis() >= nextTime)) {
      Serial.print(F("Getting time from NTP server(s)... "));
      uint32_t now = sntp_get_current_timestamp();
      if (now == noTime) {
        nextTime = millis() + 5000;
        Serial.println(F("FAIL!"));
      }
      else {
        Serial.println(F("success"));
        startTime = now;
        startMs = millis();
        if (updateInterval)
          nextTime = startMs + updateInterval * 1000;
        else
          nextTime = noTime;
      }
    }
  }
  else {
    //startTime=timeUnx;
  }
  //if (startTime != noTime) {
  now_timeUnx = startTime + (millis() - startMs) / 1000;
  parseUnixTime(now_timeUnx, now_hour, now_min, now_sec, now_wd, now_day, now_month, now_year);
  timeStr = dateWdTimeToStr(now_timeUnx);

  if ((!ApMode) && (WiFi.status() == WL_CONNECTED) && useMQTT && !mqttClient.connected()) {
    if (((int32_t)(millis() - nextTimeMQTT) >= 0) || (nextTimeMQTT == timeout))  {
      nextTimeMQTT = millis() + timeout;
      Serial.println();
      Serial.print(F("Trying to connect MQTT... "));
      Serial.print(mqttServer);
      Serial.print(F(":"));
      Serial.println(String(mqttServerPort));
      mqttClient.setServer(mqttServer.c_str(), mqttServerPort);
      mqttClient.setCallback(mqttCallback);

      for (uint8_t i = 0; i < 3; i++) {
        Serial.println("..Connecting to MQTT...");
        if (mqttClient.connect(mqttClientId.c_str(), mqttUser.c_str(), mqttUserPassword.c_str())) {
          //mqttClient.subscribe("text/#");
          mqttClient.subscribe((mqttClientId + "/swt/#").c_str());
          Serial.println("connected");
          break;

        } else {
          Serial.print("failed with state ");
          Serial.println(mqttClient.state());
        }
      }
    }
  }

  if (useMQTT) mqttClient.loop();

#ifdef USE_BMP280
if (((int32_t)(millis() - nextTimeBMP280) >= 0) || (nextTimeBMP280 == timeout))  {
    nextTimeBMP280 = millis() + timeout;
    bmePressure_now = bme.readPressure() * 0.75F / 100.00F;
    for (uint8_t i = 0; i < 5; i++) {
      if (abs(650 - bmePressure_now) <= 200 && abs(650 - bmePressure_now) >= 0) {
         bmePressure = bmePressure_now;
         break;
      }
      delay(10);
    }
    if (useMQTT) {
       mqttClient.publish((mqttClientId + "/bmp280/temp").c_str(), String(bme.readTemperature()).c_str(), true); 
       mqttClient.publish((mqttClientId + "/bmp280/mmhg").c_str(), String(bmePressure).c_str(), true); 
       mqttClient.publish((mqttClientId + "/bmp280/alt").c_str(), String(bme.readAltitude(SEALEVELPRESSURE_HPA)).c_str(), true); 
    }
}
#endif

#ifdef USE_VIBER
if (useViber) {
   for (byte k = 0; k < NomMessAll; k++) {
      if (mesTemp[k].Need == 1) {
         if ((tempC[mesTemp[k].NsenseM] >= mesTemp[k].TempM) && (mesTemp[k].accompl == 0)) {
            doViberAlarmMessage(k);
            mesTemp[k].accompl = 1;
            break;
         }
      }
   }

   if (viberPeriodic > 0 && ((int32_t)(millis() - nextTimeViber) >= 0) || (nextTimeViber == viberPeriodic))  {
      nextTimeViber = millis() + viberPeriodic;

      doViberStatusMessage();
   }

}
#endif
}
//--------------------------------------------------------------------------------------
