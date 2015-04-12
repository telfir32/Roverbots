// Робот в круглом корпусе из оргстекла на основе модуля Zelectro Z- Mini Motor Sensor Shield L293D

// параметры для моторов
int I1 = 4;        // 0 – мотор 1 вращается в одну сторону, 1 – мотор 1 вращается в другую сторону
int I2 = 7;        // 0 – мотор 2 вращается в одну сторону, 1 – мотор 2 вращается в другую сторону
int E1 = 6;        // скорость вращения мотора 1 зависит от уровня напряжения
int E2 = 5;        // скорость вращения мотора 1 зависит от уровня напряжения

// параметры датчиков
int sensor_left = A7;
int sensor_right = A5;
int sensor_left_value = 0;
int sensor_right_value = 0;


// параметры езды
int level = 970;           // порог для сравнения
int speed_normal = 100;    // скорость


void setup() {
  // подключаем пины управления моторами  
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  
  // ставим E1 и E2 в состояние 1 - ехать вперед
  digitalWrite(E1, HIGH);
  digitalWrite(E2, HIGH);
}


void loop() {
  // читаем значения с обоих датчиков
  sensor_left_value = analogRead(sensor_left);
  sensor_right_value = analogRead(sensor_right);
  
  // если значение на левом датчик больше уровня - едем вправо
  if (sensor_left_value > level)
  {
    analogWrite(I1, speed_normal);
    analogWrite(I2, 0);
  }
  // иначе если значение на правом датчике больше уровня - едем влево
  else if (sensor_right_value > level)
  {
    analogWrite(I1, 0);
    analogWrite(I2, speed_normal);
  }
  // иначе едем вперед
  else
  {
    analogWrite(I1, speed_normal);
    analogWrite(I2, speed_normal);
  }
}
