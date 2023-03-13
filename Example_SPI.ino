#include "SPI.h"

// Создаём переменную байтового массива
byte data[] {'H','e','l','l','o'};

// Создаём переменную строки в формате языка Си
char* cstring = " World!";

// создаём переменную с числом 168496141 в шестнадцатеричной системе счисления
long i = 0x0A0B0C0D;

void setup()
{
    pinMode(2, OUTPUT);
    digitalWrite(2, HIGH);
    // Инициируем интерфейс SPI в режиме ведущего
    SPI.begin();
    // Устанавливаем логическую "1" на выводе Slave Select
    pinMode(SS, HIGH);
}

void loop()
{
    // Прижимаем вывод Slave Select (устанавливаем логический "0"),
    // тем самым активируя передачу данных с подключенным
    // к этому выводу ведомым
    digitalWrite(SS, LOW);

    // Начинаем передачу данных, передавая функции объект настроек шины
    // SPISettings( Скорость в Гц, Порядок передачи битов, Режим шины)
    SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

    // Передаём массив data
    for (int i = 0; i < sizeof(data); i++) {
        SPI.transfer(char(data[i]));
    }

    // Передаём один байт
    SPI.transfer(',');

    // Передаём строку в формате си
    for (char* p = cstring; char c = *p; p++) {
        SPI.transfer(c);
    }

    // Передаём один байт - заголовок начала целого числа
    // Как пример: байт 0xAD обозначает заголовок целого числа типа long
    SPI.transfer(0xAD);

    // Побайтово передаём целое число
    for (int j = 0; j < sizeof(i); j++) {
        byte b = i >> 8 * j;
        SPI.transfer(b);
    }

    // Передаём байт конца пакета
    // Как пример: байт 0xAF обозначает конец пакета
    SPI.transfer(0xAF);

    // Завершаем передачу данных
    SPI.endTransaction();

    // Завершаем работу с ведомым
    digitalWrite(SS, HIGH);
    delay(1000);
}