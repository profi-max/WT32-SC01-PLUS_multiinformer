#include "main.h"

void  cur_check()
{
  WiFiClient client;
  HTTPClient https;
  lv_table_set_cell_value(cur_table, 0, 0, "Валюта");
  lv_table_set_cell_value(cur_table, 0, 1, "Курс");
  //https.useHTTP10(true);
  https.begin(client,"http://iss.moex.com/iss/statistics/engines/futures/markets/indicativerates/securities.json");
  int httpResponseCode = https.GET();  // Запрашиваем информацию у сервера
  //Проверяем получили ли мы ответ от сервера
  if (httpResponseCode > 0)
  {
//    String payload;
//    payload = https.getString();
//    Serial.println(payload);
//    Serial.printf("payload memory usage %d\r", payload.length());


  //Ошибок не обнаружено. Получаем строку с курсами валют для дальнейшей работы
    Serial.printf("HTTP Response code: %d\n", httpResponseCode);
    //Зажигаем зеленый светодиод при удачном выполнении запроса
      //Парсинг JSON
    StaticJsonDocument<48> filter;
    filter["securities"]["data"][0] = true;

    //StaticJsonDocument<1024> doc;
    DynamicJsonDocument doc(4400);
    DeserializationError error = deserializeJson(doc, client, DeserializationOption::Filter(filter));


    if (error) 
    {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      //Зажигаем красный светодиод при ошибке
    }
    else
    { 
      //Зажигаем синий светодиод при удачном парсинге JSON
      doc.shrinkToFit();
      Serial.printf("JSON document memory usage %d\n", doc.memoryUsage());
      JsonArray securities_data = doc["securities"]["data"];
      uint32_t size = securities_data.size();
      for (byte i = 0; i < size ; i++)
      {
        JsonArray curdata = securities_data[i];
        String name = curdata[2]; // "CAD/RUB"
        String val = curdata[3];
        lv_table_set_cell_value(cur_table, i+1, 0, name.c_str());
        lv_table_set_cell_value(cur_table, i+1, 1, val.c_str());
      }
    }
  }
  else 
  {
    //Данные не получены. Выводим в консоль код ошибки
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    //Зажигаем красный светодиод при ошибке
  }
  https.end();                         // Освобождаем ресурсы и закрываем соединение
}
