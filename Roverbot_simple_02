// версия для старого робота - с металлическим корпусом

// параметры для моторов
int In1 = 3;  // контакты моторов
int In2 = 5;
int In3 = 6;
int In4 = 9;
float k_speed_right = 0.9;     // коэффициент, на который умножается скорость правого мотора для калибровки двигателей (чтобы робот двигался в прямом направлении)
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

int ruchnoy_speed = 200;            // скорость при движении в ручном режиме по умолчанию (максмум 255)
int ruchnoy_turn_speed = 140;
int ruchnoy_go_time = 80;             // задержка для вращения двигателей вперед/назад при управлении в ручном режиме
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
}



void loop() { 
  // прием управляющего символа с Bluetooth  
  if (Serial.available()) {         //если есть принятый символ,
    symbol = Serial.read();            //  то читаем его и сохраняем в val
  }
  else {
    symbol = 'n';                      // если ничего не принято, записываем "нет команды" (чтобы робот не выполнял постоянно последнюю принятую команду)
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
      
  
    }    // конец case, но все еще отрабатываем if autobot = 0 
    
    
  } // закрываем проверку if autobot = 0 
  
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
