// Версия для старого робота - с мателлическим корпусом


// параметры для моторов
int In1 = 3;  // контакты моторов
int In2 = 5;
int In3 = 6;
int In4 = 9;
float k_speed_right = 1;     // коэффициент, на который умножается скорость правого мотора для калибровки двигателей (чтобы робот двигался в прямом направлении)
float k_speed_left = 1;        // коэффициент, на который умножается скорость левого мотора для калибровки двигателей (у одного из моторов коэффициент =1, у другого меньше 1)
// возможно, установить минимальную скорость вращения, если ниже нее - ничего не подавать
// возможно, сделать еще один коэффициент для скорости, зависящий от напряжения на аккумуляторе

// параметры для алгоритма движения
int distance_right_min = 30;        // минимальное расстояние, допустимое для правого датчика
int distance_right_max = 100;       // максимальное расстояние, допустимое для правого датчика
int distance_left_min = 20;         // минимальное расстояние, допустимое для левого датчика
int distance_left_max = 100;        // максимальное расстояние, допустимое для левого датчика

// для данной установки на плоской поверхности стандартное расстояние 120 см
int distance_down_max = 200;         // максимальное расстояние, допустимое для нижнего датчика
int distance_down_min = 25;

int forward_speed = 150;            // скорость при движении вперед по умолчанию (максмум 255)
int forward_time = 300;             // время для движения вперед
int backward_speed = 120;           // скоорость при движении назад по умолчанию (максмум 255)
int backward_time = 200;            // время для движения назад
int turn_speed = 120;            // скоорость поворота по умолчанию (максмум 255)
int turn_time = 500;             // задержка для осуществления поворота

int ruchnoy_speed = 100;            // скорость при движении в ручном режиме по умолчанию (максмум 255)
int ruchnoy_go_time = 50;             // задержка для вращения двигателей вперед/назад при управлении в ручном режиме
int ruchnoy_turn_time = 50;             // задержка для вращения двигателей при повороте при управлении в ручном режиме
int pause = 200;                    // просто пауза


// параметры для связи с компьютером/телефоном
int symbol = 'n';                            //здесь будет храниться принятый символ
int autobot = 0;                          // переменная режима работы: 1 - автоматический режим (по датчикам), 0 - ручной режим (управление с Bluetooth)
/* "раскладка" принятых символов в соответствии с приложением на Android "Arduino Bluetooth RC Car":
(в приложении выбран вариант Continuous Stream, т.е. символ передается каждые 50 мс, пока нажата кнопка на экране) 
F – Forward, вперед
B – Backward, назад
L – Left, влево
R – Right, вправо
S – Stop, остановка
I – Forward Right
J – Backward Right
G – Forward Left
­H – Backward Left

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


// светодиоды индикации (на плате уже есть резисторы 300 Ом, светодиоды можно подключать без них)
int led_green = 17;    // зеленый светодиод, подключенный к А3 (17)
int led_red = 18;      // красный светодиод, подключенный к А4 (18)
// те же контакты, но для режима передних/задних фар
int led_front = 17; 
int led_back = 18; 


// модуль воспроизведения звуковых файлов с SD карты WTV020
#include <Wtv020sd16p.h>
int resetPin = 4;  // The pin number of the reset pin
int clockPin = 8;  // The pin number of the clock pin
int dataPin = 10;  // The pin number of the data pin
int busyPin = 7;   // The pin number of the busy pin
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);




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
  pinMode(led_front, OUTPUT);
  pinMode(led_back, OUTPUT);
  digitalWrite (led_front, LOW); // изначально фары выключены
  digitalWrite (led_back, LOW); // изначально фары выключены
  
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

  // в этой версии прошивки индикацию заряда аккумуляторов светодиодами не делаем
  /*
  if (voltage < voltage_min) {  // если напряжение ниже допустимого уровня - горит красный светодиод, если нет - зеленый
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, LOW);
  } 
  else {
    digitalWrite(led_green, HIGH);
    digitalWrite(led_red, LOW);
  }
  */
  
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
    motors_stop ();                  // остановка на случай, если раньше робот ехал в автоматическом режиме
    wtv020sd16p.asyncPlayVoice(0001);   // сказать о переходе на ручной режим работы (проиграть соответствующий файл с именем 0001, записанный на SD карту)
  }
  if (symbol == 't') {               //  если принят симовол 't',
    autobot = 1;                     //  переход на автоматический режим
    wtv020sd16p.asyncPlayVoice(0002);   // сказать о переходе на автоматический режим работы
  }
  
  // обрабатываем принятый символ - в случае ручного режима
  if (autobot == 0) {               // если включен ручной режим
    switch (symbol) {               // выполняем команду в соответствии с принятым символом (если он есть)
    
    // движения вперед/назад, вправо/влево
      case 'F':     // Вперед
        motor_right (1, ruchnoy_speed);
        motor_left (1, ruchnoy_speed);
        delay (ruchnoy_go_time);
        motors_stop ();
        break;
        
      case 'B':      // Назад
        motor_right (0, ruchnoy_speed);
        motor_left (0, ruchnoy_speed);
        delay (ruchnoy_go_time);
        motors_stop ();
        break;
        
      case 'L':      // Влево
        motor_right (1, ruchnoy_speed);
        motor_left (0, ruchnoy_speed);
        delay (ruchnoy_turn_time);
        motors_stop ();
        break;
        
      case 'R':        // Вправо
        motor_right (0, ruchnoy_speed);
        motor_left (1, ruchnoy_speed);
        delay (ruchnoy_turn_time);
        motors_stop ();
        break;
         
      // движения вперед+вправо, назад+вправо, вперед+влево, назад+влево
     case 'I':  // Вперед+вправо
        motor_right (1, ruchnoy_speed / 2);     // правый мотор включаем на половину скорости
        motor_left (1, ruchnoy_speed);          // левый мотор включаем на всю скорость  
        delay (ruchnoy_turn_time);
        motors_stop ();
        break;
        
      case 'J':  // Назад+вправо
        motor_right (0, ruchnoy_speed / 2);     // правый мотор включаем на половину скорости
        motor_left (0, ruchnoy_speed);          // левый мотор включаем на всю скорость  
        delay (ruchnoy_turn_time);
        motors_stop ();
        break;
        
      case 'G':  // Вперед+влево
        motor_right (1, ruchnoy_speed);         // правый мотор включаем на всю скорость 
        motor_left (1, ruchnoy_speed / 2);      // левый мотор включаем на половину скорости 
        delay (ruchnoy_turn_time);
        motors_stop ();
        break;
        
      case 'H':  // Назад+влево
        motor_right (0, ruchnoy_speed);         // правый мотор включаем на всю скорость 
        motor_left (0, ruchnoy_speed / 2);      // левый мотор включаем на половину скорости 
        delay (ruchnoy_turn_time);
        motors_stop ();
        break;
        
        
        
      case 'W':     //включить передние фары
        digitalWrite (led_front, HIGH);
        break;
      case 'w':     //выключить передние фары
        digitalWrite (led_front, LOW);
        break;
      case 'U':     //включить задние фары
        digitalWrite (led_front, HIGH);
        break;
      case 'u':     //выключить задние фары
        digitalWrite (led_front, LOW);
        break;
      
        
         /*    
        // команды для воспроизведения звуковых файлов (остались от управления в режиме командной строки)
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
        */
    }    // конец case, но все еще отрабатываем if autobot = 0 
    
    
     // регулировка скорости в ручном режиме
        if (symbol=='q'){
          ruchnoy_speed = 255;  // максимальная скорость
        }
        if ( (symbol >= 48) && (symbol <= 57) )
          { 
            //преобразуем диапазон 48-57 в 0-9 - скорости
            //затем преобразуем 0-9 в напряжение, подаваемое на двигатели, 0-225
            ruchnoy_speed = (symbol - 48)*25;
          }
  } // закрываем проверку if autobot = 0 
  
  
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
      motor_right (0, backward_speed);
      motor_left (0, backward_speed);
      delay (backward_time);
      motor_right (1, turn_speed);
      motor_left (0, turn_speed);
      delay (turn_time);
    }
    else {
      if (distance_down < distance_down_min) {
//      wtv020sd16p.asyncPlayVoice(0000);       // Сказать "обнаружено препятствие"
      motor_right (0, backward_speed);
      motor_left (0, backward_speed);
      delay (backward_time);
      motor_right (1, turn_speed);
      motor_left (0, turn_speed);
      delay (turn_time);
      }
    }
     //проверять остальные датчики. Пока - просто ехать дальше
     motor_right (1, forward_speed);
     motor_left (1, forward_speed);
  }
  
  // пауза
  delay(pause);
}



void motor_right (int forward_right, float bot_speed) {
// forward: 1 -  мотор вращается, двигая робота вперед, 0 - мотор вращается, двигая робота назад, 2 - не вращать
float speed_right = k_speed_right * bot_speed;
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
}



void motor_left (int forward_left, float bot_speed) {
// forward: 1 -  мотор вращается, двигая робота вперед, 0 - мотор вращается, двигая робота назад, 2 - не вращать
float speed_left = k_speed_left * bot_speed; 
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

void motors_stop () {
  analogWrite(In1, 0);
  analogWrite(In2, 0);
  analogWrite(In3, 0);
  analogWrite(In4, 0);
}
