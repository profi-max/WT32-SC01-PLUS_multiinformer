# Мультиинформер
Проект универсального мультинформера на базе отладочной платы **WT32-SC01-PLUS** с процессором ESP32-S3, экраном 3.5 дюйма 480x320, емкостным тачем, встроенным аудио-интерфейсом и слотом SD-карты.
Это вариант исходного проекта [multiinformer](https://github.com/altJSV/multiinformer), автор исходного проекта [altJSV](https://github.com/altJSV) - спасибо автору. Этот репозиторий содержит проект в папке **Project** для компиляции в среде VSCode + Platformio. Готовая прошивка находится в папке **Firmware**.

## Основные возможности
- Отображение календаря с актуальными праздниками
- Отображение точного времени, даты с инхронизированных с NTP сервером
- Поддержка модулей BME/BMP280 и BME680 для отображения информации о температуре, влажности, атмосферном давлении и качестве воздуха в помещении
- Беспроводной монитор параметров ПК (температура и загрузка процессора и видеокарты, закруженность оперативной и видеопамяти, данные о сети) через программу Libre Hardware Monitor
- Отображение погодной сводки с сайта Open Weather Maps
- Отображение курсов валют по данным ММВБ
- Онлайн радио плеер

## Используемые компоненты
При создании проекта были использованы следующие компоненты:
- Отладочная плата [WT32-SC01 PLUS ](https://aliexpress.ru/item/1005004267336768.html "WT32-SC01 PLUS ")
- Ультратонкий [динамик 4 Ом 3 Вт](https://aliexpress.ru/item/4000167008546.html "динамик 4 Ом 3 Вт")

Опционально (по желанию):
- Модуль [BME680](https://aliexpress.ru/item/4001113450307.html "BME680")
- [Фоторезистор](https://aliexpress.ru/item/1005005692182923.html "Фоторезистор")

## Можете сразу использовать готовую прошивку
Используйте файл Firmware.bin из папки **Firmware**. Загрузите программу Flash Download Tools  с официального ресурса: https://www.espressif.com/en/support/download/other-tools
Подключите USB кабель к отладочной плате, запустите приложение, выберите COM-порт и bin-файл. Когда загрузка завершится нажмите кнопку "RST" (Reset), чтобы перезапустить отладочную плату.

## Компиляция проекта
Сборка проекта осуществляется в Visual Studio Code + Platformio. Проект находится в папке **Project**.

### Используемые библиотеки и ядра
Все необходимые библиотеки уже добавлены в файл platformio.ini и загрузятся автоматически при компиляции проекта.
- [lvgl 8.4.0](https://github.com/lvgl/lvgl/releases/tag/v8.4.0 "lvgl 8.4.0")
- [GyverNTP 1.3.1](https://github.com/GyverLibs/GyverNTP "GyverNTP 1.3.1")
- [GyverTimer 3.2](https://github.com/GyverLibs/GyverTimer "GyverTimer 3.2")
- [ArduinoJson 6.21.2](https://github.com/bblanchon/ArduinoJson "ArduinoJson 6.21.2")
- [Adafruit Unified Sensor 1.1.9](https://github.com/adafruit/Adafruit_Sensor "Adafruit Unified Sensor 1.1.9")
- [Adafruit BME680 Library 2.0.2](https://github.com/adafruit/Adafruit_BME680 "Adafruit BME680 Library 2.0.2")
- [ESP32Audio I2S](https://github.com/esphome/ESP32-audioI2S "ESP32Audio I2S")
- [ESPxWebFlMgr](https://github.com/holgerlembke/ESPxWebFlMgr/tree/master "ESPxWebFlMgr")


В проекте используется форк библиотеки ESP32Audio I2S за авторством esphome. Стандартная версия без psram работает не очень плавно. Звук часто заикается. Так что используйте версию по ссылке выше. Также библиотека при остановке воспроизведения не совсем корректно освобождала ресурсы. Из=за чего возникали проблемы при работе устройства. Мною эта билиотека так же была немного модифицирована. В папке library_replacement_files/ESP32-audioI2S-dev содержатся модифицированные файлы библиотеки. Замените ими оригинальные.

В проекте в качестве файлового менеджера используется библиотека ESPxWebFlMgr. По умолчанию она имеет английский интерфейс. Для его частичной руссификации скопируйте в корень файловой системы устройства из папки **Options** проекта следующие файлы: fm.css, fm.js, fm.html. Затем закомментируйте строку fileManagerServerStaticsInternally в файле ESPxWebFlMgr.h библиотеки.

### Ввод персональных данных
Файл персональных данных находится в src\credentials.h. Отредактируйте его.
Содержимое его выглядит так:
```
    String pc_server_path="http://ip вашего пк:8085/data.json";//адрес сервера пк
    //Погода
    String api_key = "apikey;  //ваш api ключ погоды
    String qLocation = "Gubkin,ru"; //город для погоды
    //Wifi
    String SSID = "ssid";
    String PASS = "pass";
```
+ pc_server_path= - ip адрес сервера Libre Hardware Monitor
+ api_key = - ваш персональный ключ Open Weather Maps
+ qLocation = -  данные о вашем местоположении для Open Weather Maps
+ SSID = - название вашей точки доступа WiFi для подключения к интернету
+ PASS = - пароль вашей точки доступа WiFi для подключения к интернету

Эти данные нужны лишь для прошивки и первичной инициализации устройства. Позже их можно изменить в настройках мультиинформера, либо с помощью веб-файлового менеджера.

## Веб-файловый менеджер
![Файловый менеджер](/Pictures/web_file_mgr.png "Файловый менеджер")

Через веб-файловый менеджер вы имеете доступ к внутренней файловой системе отладочной платы (LittleFS).
Файловый менеджер открывавется в браузере по адресу http://xxx.xxx.xxx.xxx:8080/, где ххх - локальный IP адрес отладочной платы. Вы можете редактировать, добавлять и удалять файлы конфигурации.
+ File Drop Zone - зона куда перетаскивать файлы
+ D  - удаление файла
+ R - переименование
+ E - редактирование
+ Download all files - скачивание всех файлов одним архивом

## Интерфейс пользователя
Интерфейс проекта Мультиинформер разделен на несколько экранов. Перемещение по экранам осуществялеется либо свайпами влево и вправо, либо тапом по имени вкладки в нижней части экрана.

### Главный экран
![Главный экран](/Pictures/main_screen.png)
Является стартовым экраном при загрузке устройства. Отображает календарь с выделением текущей даты, а также знаменательных и праздничных дней. 

Также на экране отображается текущее время, синхронизированное с ntp сервером и данные полученные с подключенного датчика BME680 (температура, влажность, атмосферное давление, качество воздуха). Если датчик не подключен, то отображаются данные о погоде полученные с сайта open weather maps. 
![Отображение погоды на главном экране](/Pictures/main_screen_weather.png)
Также в нижней части экрана, если текущий день совпадает с праздничным, появляется информация об этом дне. 
В правой верхней части экрана отображается информация о статусе WiFi и присвоенный устройству IP адрес в локальной сети.

### Экран мониторинга параметров ПК
![Экран мониторинга параметров ПК](/Pictures/hardwaremon.png)
Служит для мониторинга параметров ПК посредством программы Libre Hardware Monitor.
Отображает следующие параметры
Процессор:
- Температура
- Общий процент загруженности по всем ядрам
- Потребляемая мощность

Видеокарта
- Температура
- Общий процент загруженности
- Скорость работы вентилятора в процентах

Оперативная память
- Общее колличество памяти
- Использованная память
- Оставшаяся память

Видеопамять
- Общее колличество памяти
- Использованная память
- Оставшаяся память

Подключение по локальной сети
- Скорость исходящего потока
- Скорость входящего потока

Для работа данного экрана нужно чтобы на компьютере была запущена программа Libre Hardware Monitor. https://github.com/LibreHardwareMonitor/LibreHardwareMonitor

Готовое приложение для ПК на Windows можно скачать из интернета, например, здесь https://libre-hardware-monitor.softonic.ru/. 

https://github.com/profi-max/WT32-SC01-PLUS_multiinformer/assets/157157181/f272c821-aee3-46e1-b128-9fca44de75e6


В приложении нужно:
+ Menu -> Options -> Run On Windows Startup   для автоматического запуска приложения при старте Windows.
+ Menu -> Options -> Remote Web Server -> Run    запуск сервера
+ Menu -> Options -> Remote Web Server -> Port посмотреть IP адрес и порт. Добавить в настройки информера.

### Экран погоды
![Экран погоды](/Pictures/weather.png)
Экран  данных о погоде полученных с сайта Open Weather Maps.
Отображает следующую информацию:
- Город
- Направление и силу ветра
- Температуру на улице, ее фактическое ощущение, максимум и минимум за день
- Относительную влажность воздуха
- Атмосферное давление
- Видимость
- Время рассвета и заката
- Иконку и описание текущей погоды за окном
- Графики изменения атмосферного давления, температуры и влажности за сутки

Для получения данных о погоде вам предварительно нужно получить API ключ с сайта Open Weather Maps, для этого:
+ Переходим на страницу https://openweathermap.org
+ Нажимаем Sign Up в навигационной панели и создаём аккаунт
+ После создания аккаунта вернуться на страницу https://openweathermap.org и кликнуть Sign in
+ После входа попадаем в панель разработчика. Кликаем на плашку API key

Далее ввести его либо в файл credentials.cpp в поле api_key = "", либо воспользоваться экраном настроек **Погода** непосредственно на устройстве. Либо с помошью веб-файлового менеджера в файле config.txt. Аналогично укажите название города латинскими буквами в формате "City,code". Например "Gubkin,ru".

### Экран курса валют 
![Экран курсов валют](/Pictures/currency.png)
Отображает актуальную информацию различных курсов валют по отношению к рублю. Данный экран настроек не имеет. Пролистывание списка осуществляется свайпами вверх и вниз.

### Экран онлайн радио проигрывателя
![Экран радиоплеера](/Pictures/radio_screen.png)
Позволяет проигрывать онлайн аудиопоток различных интернет-радиостанций.
Остановка и запуск воспроизведения, а также переключение треков осущесвляется с помощью соответствующих кнопок. 
Изменение громкости осуществляется тапом по слайдеру, либо по нажатию соответствующих кнопок.
Имеется простенький визуализатор аудиопотока, но на данных момент он не привязан непосредственно к самому аудио.
Ниже визуализатора располагается информация о воспроизводимом в данный момент треке, если радиостанция предоставляет данную информацию.
Сохранение последней воспроиведенной радиостанции и установленного уровня громкости осуществляется автоматически после нажатия кнопки остановки воспроизведения.
Реализовано обнаружение низкой скорости потока. При частых фризах и подвисаниях устройство автоматически переподключается к точке доступа WiFi.
Вызов списка воспроизведения, имеющихся в памяти устройства радиостанций, осуществляется по кнопке в правом нижнем углу экрана.
Первый запуск плейлиста занимает некоторое время из-за индексации списка станций. Далее список окрывается мгновенно.
![Плейлист](/Pictures/playlist.png)
Переключение воспроизводимой радиостанции осуществляется тапом по ее названию.
Пролистывание списка осуществляется свайпами вверх и вниз.
Имеется возможность отредактировать список воспроизвдения прямо на устройстве, перейдя в режим редактирования вокне списка воспроизведения, нажав на кнопку в левом верхнем углу окна. Далее тапом выбирается изменяемый параметр и с помощью экранной клавиатуры редактируется. Сохранение правок осуществляется автоматически после закрытия окна списка воспроизведения.

#### Настройка списка радиостанций
Для добавления новых радиостанций создайте на sd карте файл playlist.txt примерно такого вида:
```
    http://rusradio.hostingradio.ru/rusradio128.mp3*Русское радио
    http://free.radioheart.ru:8000/RH54154*Перец FM
    http://radio-holding.ru:9000/marusya_default*Маруся FM
    http://vladfm.ru:8000/vfm*Владивосток FM
```
Каждая станция начинается с новой строки.  Формат следующий:
url\_адрес\_потока\*Отображаемое\_имя\_станции
Максимальное колличество радиостанций в плейлисте - 255!
Поддерживаемые форматы воспроизведения MP3, AAC и FLAC
После вставки SD карты и последующей перезагрузки  playlist.txt будет скопирован с SD во внутреннюю память устройства.
Также вы можете скопировать данный файл во внутренню память с помощью веб-файлового менеджера.
Пример готового файла playlist.txt c 76 онлайн-радиостанциями находится в папке **Options**.

##### Добавление списка радиостанций через Файловый менеджер
Также playlist.txt можно переместить и редактировать прямо на устройстве с помощью встроенного файлового менеджера. Для этого введите в адресной строке браузера компьютера или смартфона IP адрес устройства и с помощью открывшегося файлового менеджера переместите  playlist.txt во внутреннюю память устройства, либо отредактируйте его прямо в браузере.

### Экран настроек
На данном экране представлены различные настройки устройства разделенные на 6 категорий:
- Основные
- Монитор ПК
- Погода
- Датчик BME
- SD карта
Переключение  категорий настроек осуществляется свайпами вверх и вниз, а также тапами по имени категории в левой части экрана. Сохранение настроек производится автоматически при закрытии панели настроек.

#### Основные
![Основные настройки](/Pictures/main_settings.png)
Здесь производится настройка яркости подсветки экрана, а также включение и отключение автоматической регулировки яркости подсветки в зависимости от внешнего освещения.
Также здесь можно изменть время работы RGB индикатора раздичных состояний устройства, например для его отключения в ночное время, а также отключить его совсем. 
Также на данном экране настроек можно установить часовой пояс для отображаемого времени на экране.

#### WiFi
![Настройки WiFi](/Pictures/wifi_settings1.png)
На данном экране вы можете ввести учетные данные для подключения по WiFi к вашей точке доступа, а также просмотреть информацию об активном WiFi подкючении.
![Информация о WiFi](/Pictures/wif_settings2.png)

#### Монитор ПК
![Монитор ПК](/Pictures/pc_settings.png)
На данном экране вы можете указать адрес веб сервера Libre Hardware Monitor для чтения информации о параметрах ПК, а также изменить интервал опроса датчиков.

#### Погода
![Настройки погоды](/Pictures/weather_settings.png)
На данном экране вы может настроить параметры подключения к погодному серверу Open Weather Maps. С помощью экранной клавиатуры вы можете ввести ваш API ключ для доступа к сервису, а также город и код страны для которого будт отображаться погода.
С помощью слайдера вы можете установить временной интервал обновления данных о погоде.

#### Датчик BME
![Настройки BME](/Pictures/bme_settings.png)
На данной вкладке настроек вы можете включить использование датчика BME680, для отображения различных параметров микроклимата в помещении на главном экране. Также вы можете с помощью слайдера изменить интервал опроса датчика.

#### SD карта
![Настройки SD](/Pictures/sd_settings.png)
На этом экране вы можете импортировать/экспортировать файл настроек устройства, а также плейлист радиостанций с (на) SD карты(у) во(из) внутреннюю(ей) память(и) мультиинформера.
