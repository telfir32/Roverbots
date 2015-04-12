// версия для старого робота - с металлическим корпусом

// параметры для алгоритма движения
int distance_right_min = 30;        // минимальное расстояние, допустимое для правого датчика
int distance_right_max = 100;       // максимальное расстояние, допустимое для правого датчика
int distance_left_min = 20;         // минимальное расстояние, допустимое для левого датчика
int distance_left_max = 100;        // максимальное расстояние, допустимое для левого датчика

// для данной установки на плоской поверхности стандартное расстояние 120 см
int distance_down_max = 200;         // максимальное расстояние, допустимое для нижнего датчика
int distance_down_min = 25;

int forward_speed = 160;            // скорость при движении вперед
int forward_time = 300;             // время для движения вперед
int backward_speed = 160;           // скоорость при движении назад
int backward_time = 500;            // время для движения назад
int turn_speed = 120;            // скоорость поворота
int turn_time = 500;             // задержка для осуществления поворота

int ruchnoy_forward_speed = 200;            // скорость при движении вперед в ручном режиме
int ruchnoy_go_time = 500;             // задержка для вращения двигателей вперед/назад при управлении в ручном режиме
int ruchnoy_turn_time = 250;             // задержка для вращения двигателей при управлении в ручном режиме
int pause = 200;                    // просто пауза


// параметры для связи с компьютером/телефоном
int symbol = 'n';                            //здесь будет храниться принятый символ
int autobot = 0;                          // переменная режима работы: 1 - автоматический режим (по датчикам), 0 - ручной режим (управление с Bluetooth)
/* "раскладка" принятых символов:
t - переход на автоматическое управление auto = 1
r - переход на ручное управление auto = 0 (далее команды для ручного режима)
w - ехать заданное время вперед
s - ехать заданное время назад
a - ехать заданное время влево
d - ехать заданное время вправо
n - нет команды
*/


// параметры для зарядки аккумулятора
int accumulator = 0;          // переменная для измеренного АЦП напряжения с делителя от аккумулятора
float k_accum = 14.892 / 1023 ; // коэффициент, на который надо умножить значение, полученное с пина, подключенного к 
// делителю напряжения на аккумуляторе, чтобы получить значение напряжения на аккумуляторе
float voltage = 8 ;           // переменная для хранения значения напряжения на аккумуляторе
float voltage_min = 6.5;        // минимально допустимое напряжение на аккумуляторе


// светодиоды индикации
int led_green = 17;    // зеленый светодиод, подключенный к А3 (17)
int led_red = 18;      // красный светодиод, подключенный к А4 (18)


// модуль воспроизведения звуковых файлов с SD карты WTV020
#include <Wtv020sd16p.h>
int resetPin = 4;  // The pin number of the reset pin
int clockPin = 8;  // The pin number of the clock pin
int dataPin = 10;  // The pin number of the data pin
int busyPin = 7;   // The pin number of the busy pin
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);


// параметры для моторов
int In1 = 3;  // контакты моторов
int In2 = 5;
int In3 = 6;
int In4 = 9;
float k_speed_right = 1 
\;     // коэффициент, на который умножается скорость правого мотора для калибровки двигателей (чтобы робот двигался в прямом направлении)
float k_speed_left = 1;        // коэффициент, на который умножается скорость левого мотора для калибровки двигателей (у одного из моторов коэффициент =1, у другого меньше 1)
// int acceleration = 5;        // ускорение (на сколько можно прибавить/удалить скорость за такт)
// в функцию motors (fl, fr, speed) посылать для обоих моторов: 1 -  мотор вращается, двигая робота вперед, 0 - мотор вращается, двигая робота назад, 2 - не вращать (возможно, добавить 3 - тормоз)
// возможно, установить минимальную скорость вращения, если ниже нее - ничего не подавать
// возможно, сделать еще один коэффициент для скорости, зависящий от напряжения на аккумуляторе


// Ультразвуковые датчики расстояния HC-SR04
#include "Ultrasonic.h"
Ultrasonic ultrasonic_right (16, 15);  // Контакты (Trig, Echo) правого датчика (номер 1, дальний от угла платы)
Ultrasonic ultrasonic_left (14, 13);   // Контакты (Trig, Echo) левого датчика (номер 2, средний)
Ultrasonic ultrasonic_down (11, 12);   // Контакты (Trig, Echo) нижнего датчика (номер 3, ближний к углу платы)
float distance_right = 0;            // переменная для хранения расстояния с правого датчика (в сантиметрах)
float distance_left = 0;             // переменная для хранения расстояния со левого датчика (в сантиметрах)
float distance_down = 0;             // переменная для хранения расстояния с нижнего датчика (в сантиметрах)



void setup() {
  // подключаем пины моторов и устанавливаем на них нулевое значение  
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
  digitalWrite(In1, LOW);
  digitalWrite(In2, LOW);
  digitalWrite(In3, LOW);
  digitalWrite(In4, LOW);
      
  // подключаемся к Bluetooth модулю, соединенному с 0 и 1 (не забыть установить ту скорость соединения, которую требует модуль)
  Serial.begin(9600); // Примечание: если нужно будет прошить робота - вынуть Bluetooth или отключить питание перемычкой, он мешает прошивке
  
  // включаем пины светодиодов как выходные
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  
  // Включаем модуль вопроизведения звуковых файлов с SD карты WTV020
  wtv020sd16p.reset();
}



void loop() {
  // меряем значение напряжения на аккумуляторе и выдаем в Serial порт (на Bluetooth или USB - что подключено) и на сигнальные светодиоды
  accumulator = analogRead(A7);
  voltage = k_accum * accumulator;
  Serial.print("Voltage");
  Serial.print("\t");
  Serial.print(voltage);
  Serial.print("\t");
  
  if (voltage < voltage_min) {  // если напряжение ниже допустимого уровня - горит красный светодиод, если нет - зеленый
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, LOW);
  } 
  else {
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
  }
  
  // прием управляющего символа с Bluetooth  
  if (Serial.available()) {         //если есть принятый символ,
    symbol = Serial.read();            //  то читаем его и сохраняем в val
  }
  else {
    symbol = 'n';                      // если ничего не принято, записываем "нет команды" (чтобы робот не выполнял постоянно последнюю принятую команду)
  }
    
  // обрабатываем принятый символ - проверка режима
  if (symbol == 'r') {               //  если принят симовол 'r'
    autobot = 0;                     //  переход на ручной режим
    motors (2, 2, 0);                // остановка на случай, если раньше робот ехал в автоматическом режиме
    wtv020sd16p.asyncPlayVoice(0001);   // сказать о переходе на ручной режим работы (проиграть соответствующий файл с именем 0001, записанный на SD карту)
  }
  if (symbol == 't') {               //  если принят симовол 't',
    autobot = 1;                     //  переход на автоматический режим
    wtv020sd16p.asyncPlayVoice(0002);   // сказать о переходе на автоматический режим работы
  }
  
  // обрабатываем принятый символ - в случае ручного режима
  if (autobot == 0) {               // если включен ручной режим
    switch (symbol) {               // выполняем команду в соответствии с принятым символом (если он есть)
      case 'w':
        motors (1, 1, ruchnoy_forward_speed / 2);  // выполняется разгон и торможение, чтобы колеса не проскальзывали по гладкой поверхности
        delay (ruchnoy_go_time / 4);
        motors (1, 1, ruchnoy_forward_speed);
        delay (ruchnoy_go_time / 2);
        motors (1, 1, ruchnoy_forward_speed / 2);
        delay (ruchnoy_go_time / 4);
        motors (2, 2, 0);
        break;
        
      case 's':
        motors (0, 0, ruchnoy_forward_speed / 2);  // выполняется разгон и торможение, чтобы колеса не проскальзывали по гладкой поверхности
        delay (ruchnoy_go_time / 4);
        motors (0, 0, ruchnoy_forward_speed);
        delay (ruchnoy_go_time / 2);
        motors (0, 0, ruchnoy_forward_speed / 2);
        delay (ruchnoy_go_time / 4);
        motors (0, 0, 0);
        break;
      case 'a':
      
        motors (0, 1, ruchnoy_forward_speed);
        delay (ruchnoy_turn_time);
        motors (2, 2, 0);
        break; 
      case 'd':
        motors (1, 0, ruchnoy_forward_speed);
        delay (ruchnoy_turn_time);
        motors (2, 2, 0);
        break;
        // команды для воспроизведения звуковых файлов
      case 'y':
        wtv020sd16p.asyncPlayVoice(1002);  // РТФ круче всех
        break;
      case 'u':
        wtv020sd16p.asyncPlayVoice(1003);  // Клуб робототехники – лаборатория 410 третьего корпуса ПГТУ
        break;
      case 'i':
        wtv020sd16p.asyncPlayVoice(1001);  // Приветствую
        break;
      case 'o':
        wtv020sd16p.asyncPlayVoice(0000);  // Обнаружено препятствие
        break;  
      case 'p':
        wtv020sd16p.asyncPlayVoice(1000);  // Привет
        break;
      case 'm':
        wtv020sd16p.asyncPlayVoice(0006);  // Проиграть музыку
        break;
    }
  }
  
  
  // снимаем данные с ультразвуковых датчиков расстояния HC-SR04 и выдаем в Serial порт
  /*
  distance_right = ultrasonic_right.Ranging(CM);
  Serial.print("Right dist");
  Serial.print("\t");
  Serial.print(distance_right);
  Serial.print("\t");
  
  distance_left = ultrasonic_left.Ranging(CM);
  Serial.print("Left dist");
  Serial.print("\t");
  Serial.print(distance_left);
  Serial.print("\t");
  */
  distance_down = ultrasonic_down.Ranging(CM);
  Serial.print("Down dist");
  Serial.print("\t");
  Serial.print(distance_down);
  Serial.println("\t");
  
  
  // в случае автоматического режима обрабатываем информацию с датчиков и двигаемся в соответствии с ней
  if (autobot == 1) {
    // если нижний датчик показывает число, большее заданного, необходимо отъехать назад, развернуться и ехать вперед
    if (distance_down > distance_down_max) {       
      motors (0, 0, backward_speed);
      delay (turn_time);
      motors (1, 0, turn_speed);
      delay (turn_time);
    }
    else {
      if (distance_down < distance_down_min) {
//      wtv020sd16p.asyncPlayVoice(0000);       // Сказать "обнаружено препятствие"     
      motors (0, 0, backward_speed);
      delay (turn_time);
      motors (1, 0, turn_speed);
      delay (turn_time);
      }
    }
     //проверять остальные датчики. Пока - просто ехать дальше
     motors (1, 1, forward_speed);
  }
  
  // пауза
  delay(pause);
}



void motors (int forward_left, int forward_right, int bot_speed) {
// forward_right: 1 - правый мотор вращается, двигая робота вперед, 0 - мотор вращается, двигая робота назад, 2 - не вращать (возможно, добавить 3 - тормоз)
// forward_left:  1 - левый мотор вращается, двигая робота вперед, 0 - мотор вращается, двигая робота назад, 2 - не вращать (возможно, добавить 3 - тормоз)
  // расчет скоростей моторов с учетом калибровочного коэффициента
  float speed_right = k_speed_right * bot_speed;    // расчет скорости правого двигателя с учетом коэффициента калибровки
  float speed_left = k_speed_left * bot_speed;      // расчет скорости левого двигателя с учетом коэффициента калибровки
  // проверка направления, в котором нужно вращать правый мотор и подача управляющего сигнала на него. Номера контактов заданы условно, перепроверить
  if (forward_right == 1) { 
    analogWrite(In2, 0);
    analogWrite(In1, speed_right);
  }
  if (forward_right == 0) { 
    analogWrite(In1, 0);
    analogWrite(In2, speed_right);
  }
  if (forward_right == 2) { 
    analogWrite(In1, 0);
    analogWrite(In2, 0);
  }
  // проверка направления, в котором нужно вращать левый мотор и подача управляющего сигнала на него
  if (forward_left == 1) { 
    analogWrite(In4, 0);
    analogWrite(In3, speed_left);
  }
  if (forward_left == 0) { 
    analogWrite(In3, 0);
    analogWrite(In4, speed_left);
  }
  if (forward_left == 2) { 
    analogWrite(In3, 0);
    analogWrite(In4, 0);
  }
}
