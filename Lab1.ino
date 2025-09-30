#include "Arduino.h"

#define Vin 12  // 定义GPIO 12为PWM输出引脚（对应公式中的Vin输出端）
#define Vout 27   // 定义GPIO 27为电压测量引脚（对应低通滤波器输出）
//#define Cal 14  // 电流计算节点（Task2及以后使用）

//float R = 2; // 电阻值，Task2中会用到（单位：kΩ）

float x;  // 用于存储占空比（Task1）
float y;  // 用于存储Vout电压（Task1）
// float c;  // 用于存储电流（Task2及以后）

void setup() {

  Serial.begin(115200); // 初始化串口通信，波特率115200
  pinMode(Vin, OUTPUT); // 设置Vin为输出模式（输出PWM信号）
  pinMode(Vout, INPUT); // 设置Vout为输入模式（读取滤波后的电压）
  // pinMode(Cal, INPUT); // 电流测量节点设置为输入（Task2及以后）
  
  delay(100);   // 100ms延迟，等待电路稳定
  Serial.println("Duty Cycle (%),Vout (V)"); // 输出表头
  for (int onPeriod = 0; onPeriod < 256; onPeriod++) 
    {
    // 输出PWM信号：onPeriod范围0~255，对应占空比0%~100%
    analogWrite(Vin, onPeriod);      
    // 读取Vout引脚的AD值（0~4095，对应0~3.3V）
    int Vout_value = analogRead(Vout); 
    
    // 计算占空比（x）：onPeriod/255*100%
    x = (onPeriod / 255.0) * 100; 
    // 计算Vout电压（y）：AD值转换为实际电压（0~3.3V）
    y = (Vout_value / 4095.0) * 3.3; 
    
    Serial.print(x); 
    Serial.print(","); 
    Serial.println(y);
  }
}

void loop() {
  // 循环中无需代码，一次测量完成后结束
}
