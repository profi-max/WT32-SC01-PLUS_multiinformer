/*******************************************************************************
Created by profi-max (Oleg Linnik) 2024
https://profimaxblog.ru
https://github.com/profi-max

*******************************************************************************/
#ifndef _MAIN_H
#define _MAIN_H

//#ifdef __cplusplus
//extern "C" {
//#endif

#define LGFX_USE_V1
//Подключаем библиотеки

  #include <Arduino.h>
  #include <lvgl.h> //библиотека пользовательского интерфейса
  #include <FS.h> //Работа с файловой системой
  #include <LittleFS.h> //файловая система esp32
  #include "SD.h"//работа с sd картой
  #include <SPI.h>//интерфейс взаимодействия с sd картой
  #include <Wire.h> //i2c инетрфейс для тач панели и датчика bme
   #include <GyverNTP.h>//синхронизация времени по интернету
  #include <GyverTimer.h>//подключение различных таймеров
  #include <ArduinoJson.h>//библиотека для работы с файлами конфигурации
  #include <WiFi.h>//wifi функции
  #include <WiFiClient.h>//для связи по протоколу https
  #include <HTTPClient.h>//отправка http запросов
  #include <Adafruit_Sensor.h>//универсальная библиотека для работы с различными сенсорами
  #include <Audio.h> //ESP32 Audio I2S от ESPHome
  #include <LovyanGFX.hpp>
  #include "sdcard.h"
  #include <WebServer.h> //Библиотека Web сервера
  // getting access to the nice mime-type-table and getContentType()
  #include <detail/RequestHandlersImpl.h>
  #include <ESPxWebFlMgr.h> //файловый менеджер


  //#define USE_BME280


  #define BME_ADDR 0x76  // адрес зависит от пина SDO (0: 0x76)(1: 0x77)

#ifdef USE_BME280
  #include <Adafruit_BME280.h>//библиотека для работы с датчиком BME280
#else
  #include <Adafruit_BME680.h>//библиотека для работы с датчиком BME680
#endif

//Определяем различные параметры устройств
  //Пины ESP32 подключенные к SD карте
  #define SD_SCK 39
  #define SD_MISO 38
  #define SD_MOSI 40
  #define SD_CS 41

  #define I2S_DOUT      37
  #define I2S_BCLK      36
  #define I2S_LRC       35

  #define BME_I2C_SDA 11
  #define BME_I2C_SCL 12

  #define SCREEN_WIDTH 480
  #define SCREEN_HEIGHT 320
  
  //Пины перефирии
//  #define TFT_BACKLIGHT 45 //пин подсветки экрана
  #define PHOTO_PIN 10 //пин фоторезистора
  

  //Флаг форматирования файловой системы при ошибке инициализации LittleFS
  #define FORMAT_LITTLEFS_IF_FAILED true

  //Дополнительные символы в шрифте
  #define LV_SYMBOL_SUNRISE "\xEF\x82\xB3" //Восход
  #define LV_SYMBOL_SUNSET "\xEF\x82\xB4" //Закат
  #define LV_SYMBOL_HUMIDITY "\xEF\x82\xB5" //Влажность
  #define LV_SYMBOL_PRESSURE "\xEF\x82\xB6"//Атм. давление
  #define LV_SYMBOL_CPU "\xEF\x82\xB7" //процессор
  #define LV_SYMBOL_GPU "\xEF\x82\xB8" //видеокарта
  #define LV_SYMBOL_FAN "\xEF\x82\xB9" //вентилятор
  #define LV_SYMBOL_AIR "\xEF\x82\xBA" //качество воздуха
  #define LV_SYMBOL_TEMP "\xEF\x82\xBB" //температура

  //Объявление графических ресурсов используемых в проекте
  LV_IMG_DECLARE(clouds100);//облака для экрана погоды
  LV_IMG_DECLARE(drizzle100);//слякоть
  LV_IMG_DECLARE(mist100);//Туман
  LV_IMG_DECLARE(rain100);//Дождь
  LV_IMG_DECLARE(snow100);//Снег
  LV_IMG_DECLARE(storm100);//Гроза
  LV_IMG_DECLARE(sun100);//Солнце
  LV_IMG_DECLARE(play); //кнопка play
  LV_IMG_DECLARE(stop); //кнопка stop
  LV_IMG_DECLARE(prevst); //кнопка prev
  LV_IMG_DECLARE(nextst); //кнопка next
  LV_IMG_DECLARE(volmin); //кнопка vol-
  LV_IMG_DECLARE(volmax); //кнопка vol+
  LV_IMG_DECLARE(playlist); //редактор плейлиста

LV_FONT_DECLARE(ui_font_digital);
LV_FONT_DECLARE(fira);
LV_FONT_DECLARE(ui_font_fira24);




//  Global variables

extern uint8_t sn, vol, un; //sn номер станции, vol громкость макс 20, un колличество треков в плейлисте
extern uint8_t daybegin;
extern uint8_t dayend;
extern char URL[100], sta[50];
extern String url;
extern GyverNTP ntp; //часовой пояс GMT+3


extern  bool photosensor ; //использовать фоторезистор
extern  bool usesensor; //Использовать датчик температуры
  //uint8_t sensortype = 1; //тип датчика 0 - bmp280, 1 - bme280, 2 - bme680, 
extern  bool ledindicator; //Включение или отключение rgb светодиода
extern  bool darktheme; //Включение или отключение rgb светодиода  
extern  uint8_t daybegin, dayend;
//Переменные конфигурации дисплея
extern const uint16_t screenWidth; //ширина экрана
extern const uint16_t screenHeight; //высота экрана
  //Подсветка дисплея
extern uint8_t bright_level; //яркость подсветки экрана


  
//Значения различных таймеров
   extern  uint32_t refpcinterval;//Обновление парметров ПК 3 секунды
   extern  uint32_t refweatherinterval;//Погода 5 минут
   extern  uint32_t refsensorinterval;//получение данных с сенсора 5 секунд
//Предварительная инициализация json для монитора ПК
//служебные переменные для анимаций
   extern  u_int8_t prev_cpu_usage;//предыдущее значение загрузки проца
   extern  u_int8_t prev_gpu_usage;//предыдущее значение загрузки видео
   extern  u_int8_t prev_cpu_temp;//предыдущее значение температуры проца
   extern  u_int8_t prev_gpu_temp;//предыдущее значение температуры видео
   extern  u_int8_t prev_cpu_fan;//предыдущее значение температуры проца
   extern  u_int8_t prev_gpu_fan;//предыдущее значение температуры видео
   extern  u_int8_t prev_ram;//предыдущее значение загрузки ОЗУ
   extern  u_int32_t prev_gpuram;//предыдущее значение загрузки видеопамяти

  
  //Переменные для отслеживание изменений в настройках и вызов функции сохранения
  extern bool saveconf; //флаг измения настроек
  extern uint8_t prev_tab; //предыдущая активная вкладка
  
  extern int8_t gmt; //часовой пояс
  extern  const char * ntpserver;
  extern const char *filename;  // имя файла конфигурации


extern String pc_server_path;//адрес сервера пк
//Погода
extern String api_key;  //ваш api ключ погоды
extern String qLocation; //город для погоды
//Wifi
extern String SSID;
extern String PASS;





  extern  lv_obj_t * wifistatus; //статус wifi
  extern  lv_obj_t * ui_status_clock; //Часы в статус баре
  extern  lv_obj_t * tabview; //Вкладки
  
    //Экраны
    //1 экран
  extern  lv_obj_t * statusbox;//служебные сообщения на 1 вкладке
  extern  lv_obj_t * displayclock;//часы
  extern  lv_obj_t * calendar;//календарь
  extern  lv_obj_t * ui_weatherimage_main;//Изображение погоды
  extern  lv_obj_t * roomtemp;//температура с датчика
  extern  lv_obj_t * roompress;//давление с датчика
  extern  lv_obj_t * roomhumid;//влажность с датчика
  extern  lv_obj_t * roomair;// показания датчика качества воздуха
  extern  lv_obj_t * roomair_bar;//индикатор качества воздуха
  extern  lv_obj_t * roomair_bar_label;//баллы качества воздуха
    //4 экран курсы валют
  extern  lv_obj_t * cur_table;//таблица
  extern  lv_obj_t  * ui_cur_title; //Заголовок таблицы
    //2 экран. Монитор ПК
  extern  lv_obj_t * cpumeter; //загрузка и теипература процессора
  extern  lv_meter_indicator_t * cpu_indic;//полоса загрузки процессора
  extern  lv_meter_indicator_t * cpufan_indic;//вентилятор процессора
  extern  lv_meter_indicator_t * cputemp_indic;//полоса температуры процессора
  extern  lv_obj_t * gpumeter;//загрузка и температура видеокарты
  extern  lv_meter_indicator_t * gpu_indic;//загрузка видеокарты
  extern  lv_meter_indicator_t  *gputemp_indic;//температура видеокарты
  extern  lv_meter_indicator_t * gpufan_indic;//вентилятор видеокарты
  extern  lv_obj_t * rambar;//полоса оперативной памяти
  extern  lv_obj_t * gpurambar;//полоса памяти видеокарты
  extern  lv_obj_t * ui_upload_label;//передача по сети
  extern  lv_obj_t * ui_download_label;//прием по сети
    //Анимации изменения длины полос
  extern  lv_anim_t cpu;
  extern  lv_anim_t gpu;
  extern  lv_anim_t ramcpu;
  extern  lv_anim_t ramgpu;
    //Различные надписи
  extern  lv_obj_t * cpu_load_label;
  extern  lv_obj_t * cpu_temp_label;
  extern  lv_obj_t * cpu_fan_label;
  extern  lv_obj_t * gpu_load_label;
  extern  lv_obj_t * gpu_temp_label;
  extern  lv_obj_t * gpu_fan_label;
  extern  lv_obj_t * ram_val_label;
  extern  lv_obj_t * gpuram_val_label;
    //3 экран. Объявление переменных экрана погоды
  extern  lv_obj_t * windmeter; //Отображение направления ветра
  extern  lv_obj_t * ui_windspeed;// надпись для скорости ветра
  extern  lv_obj_t * ui_windgust;// надпись для скорости ветра
  extern  lv_meter_indicator_t * wind_indic;//индикатор направления ветра
    //Различные надписи для экрана погоды
  extern  lv_obj_t * weathercity;//Название города
  extern  lv_obj_t *ui_weathertemp;//температура
  extern  lv_obj_t *ui_humid;//влажность
  extern  lv_obj_t *ui_feeltemp;//температура ощущется как
  extern   lv_obj_t *ui_avgtemp;//максимальная и минимальная температуры
  extern  lv_obj_t *ui_weatherdesc;//описание погодных условий
  extern  lv_obj_t *ui_pressure;//атмосферное давление
  extern  lv_obj_t *ui_visiblity;//видимость
  extern  lv_obj_t *ui_sunset;//закат
  extern  lv_obj_t *ui_sunrise;//рассвет
  extern  lv_obj_t *ui_weatherimage;//картинка с погодными условиями
    //графики
  extern  lv_obj_t *ui_pressurechart;//график давления
  extern  lv_obj_t *ui_tempchart;//график температуры
  extern  lv_obj_t *ui_humidchart;//график влажности
    //массивы
  extern  lv_chart_series_t * ui_prser; //массив координат графика давления
  extern  lv_chart_series_t * ui_tempser; //массив координат графика температуры
  extern  lv_chart_series_t * ui_huser; //массив координат графика влажности
    //Экран радио
  extern  lv_obj_t * radio_volumembar; //полоса громкости
  extern  lv_obj_t * radio_station_num_label; //номер станции
  extern  lv_obj_t * radio_playing_value_label; //текущий трек
  extern  lv_obj_t  * radio_playing_label; //название трека
  extern  lv_obj_t  * radio_visualiser; //визуализация трека
  extern  lv_chart_series_t  * radio_visualiser_series; //массив данных для визуализации
  extern  lv_obj_t * playlistwin; //редактор плейлиста
  extern  lv_obj_t * playlist_table;//таблица плейлиста
  extern  lv_obj_t * radio_play_btn;

    //7 экран настройки
  extern  lv_obj_t * slider_label;
  extern  lv_obj_t * set_tabview; //Вкладки настроек
  extern  lv_obj_t * kb; //клавиатура
  extern  lv_obj_t * wt_ta; //поле ввода API погоды
  extern  lv_obj_t * pc_ta; //поле ввода адреса пк
  extern  lv_obj_t * ya_ta; //поле ввода API яндекса
  extern  lv_obj_t * wtl_ta; //поле ввода местоположения погоды
  extern  lv_obj_t * yandex_int_slider_label;
  extern  lv_obj_t * weather_int_slider_label;
  extern  lv_obj_t * pc_int_slider_label;
  extern  lv_obj_t * bme_int_slider_label;
  extern  lv_obj_t * gmt_slider_label;
  extern  lv_obj_t * wifitable;
  extern  lv_obj_t * wifipass_ta;
  extern  lv_obj_t * wifissid_ta;
  extern  lv_obj_t * slider_daytime_label;




//  Functions 
String playlistread(fs::FS &fs, const char * path, uint16_t line);  // spiifsconfig.cpp

String getDateTime(uint32_t t); // weather.cpp
void getweather(); // weather.cpp

void loadConfiguration(const char *filename); //spiifsconfig.cpp
void saveConfiguration(const char *filename);
String playlistread(fs::FS &fs, const char * path, uint16_t line);
uint8_t playlistnumtrack(fs::FS &fs, const char * path);
void saveRadioConf(const char *filename);
void loadRadioConf(const char *filename);

void loopWebServer(void);  // webserver.cpp

void hardwareMonitor(); // hadrwaremonitor.cpp

void  cur_check(); // currency.cpp

void url_sta(uint8_t c); // radio.cpp

void setupWebserver(void); // webserver.cpp

//#ifdef __cplusplus
//} /*extern "C"*/
//#endif // #ifdef __cplusplus

#endif // #ifndef _MAIN_H