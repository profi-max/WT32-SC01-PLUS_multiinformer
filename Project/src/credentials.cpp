#include <Arduino.h>

/*
Практика: Получаем ключ авторизации OpenWeatherMap API
Переходим на страницу https://openweathermap.org
Нажимаем Sign Up в навигационной панели и создать аккаунт
После создания аккаунта вернуться на страницу https://openweathermap.org и кликнуть Sign in
После входа попадаем в панель разработчика. Кликаем на плашку API key
Сохраняем сгенерированный ключ в удобном месте.
*/



String pc_server_path="http://ip вашего пк:8085/data.json";//адрес сервера пк
//Погода
String api_key = "apikey;  //ваш api ключ погоды
String qLocation = "Gubkin,ru"; //город для погоды
//Wifi
String SSID = "ssid";
String PASS = "pass";