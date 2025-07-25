ESP32 四驱避障机器人

本项目是基于 ESP32 的四轮驱动智能车，具备超声波避障、LED 状态指示、蜂鸣器报警、舵机定位、网络远程控制和 WebSerial 电机校准等功能。
适合 K6–K12 学生编程、物联网和机器人课程演示，也可作为 IoT 入门级项目的参考范例。

⸻

功能概述
• 超声波避障：检测障碍物距离，自动停车防撞。
• LED 指示灯：绿色代表安全，红色表示前方有障碍。
• 蜂鸣器报警：遇障碍时发出警报声。
• 舵机驱动：支持探头转向（如需拓展多点测距）。
• 四轮独立电机驱动：支持前进、后退、原地左右转。
• 按钮控制：一键启停小车。
• WebSerial 控制台：网页串口调试和电机校准。
• WiFi 联网：支持 OTA 远程固件升级。
• EEPROM 校准存储：支持断电后保存电机校准参数。

⸻

硬件清单
• 主控板：ESP32 DevKit v1 或兼容开发板
• 电机：4 路直流电机 + L298N/其他H桥电机驱动板
• 舵机：1 路（SG90/类似）
• 超声波测距模块：1 路（HC-SR04）
• 蜂鸣器：1 路有源/无源皆可
• LED：红、绿各 1 颗
• 按钮：1 路
• 其他：杜邦线、充电宝/锂电池、面包板/车身底盘等

⸻

引脚连接表

模块 引脚名 ESP32 GPIO
绿LED LED_GREEN_PIN 22
红LED LED_RED_PIN 4
按钮 BUTTON_PIN 2
超声波 TRIG 1
超声波 ECHO 3
舵机 SERVO_PIN 21
蜂鸣器 BUZZER_PIN 13
电机1 FL_PWM_A / B 27 / 26
电机2 FR_PWM_A / B 32 / 16
电机3 RL_PWM_A / B 25 / 33
电机4 RR_PWM_A / B 17 / 18

⚠️ 部分引脚(如GPIO1/3)与ESP32默认串口复用，量产建议更换。

⸻

软件环境
• 开发工具：PlatformIO IDE / Arduino IDE 2.x
• 依赖库（PlatformIO示例）：

lib_deps =
madhephaestus/ESP32Servo@^3.0.6
lorol/AsyncTCP@^1.1.2
me-no-dev/ESP Async WebServer@^1.2.3
HdrHistogram/AsyncWebSerial@^1.1.1
arduino-libraries/EEPROM@^2.0.0

    •	Arduino核心：espressif32，推荐2.0.5及以上

⸻

使用方法

1. 烧录与OTA配置
   • 修改代码顶部的 WiFi 名称与密码 NETWORK_WIFI_SSID、NETWORK_WIFI_PASS。
   • 连接ESP32到电脑，烧录程序。
   • 首次启动后可在同一局域网用 OTA 方式无线升级固件。

2. 车辆控制
   • 按下按键，车辆启动，自动前行/避障。
   • 再按一次按键，车辆停止。

3. WebSerial调试/校准
   • 连接同一WiFi，浏览器访问 http://<ESP32的IP地址>/webserial。
   • 可输入如下命令：
   • start/stop：启动/停止车辆
   • forward/backward：前进/后退
   • left/right：左/右转
   • status/info/hello：查看状态
   • calibrate <fl|fr|rl|rr> <值>：设置电机偏置（例：calibrate fl 5）
   • calibrate status：查询当前电机偏置

⸻

指令说明（WebSerial 控制台）

指令 作用
start 启动车辆
stop 停止车辆
forward 手动前进
backward 手动后退
left 手动画左转
right 手动画右转
status/info/hello 显示车辆状态及帮助
calibrate <轮位> <偏置值> 设置单个轮电机校准
calibrate status 查询当前所有轮偏置

⸻

进阶与拓展
• 可扩展多点测距（舵机分时扫描）实现“环视避障”
• 增加蓝牙/手机遥控
• 引入更多传感器（温湿度、循迹、陀螺仪等）
• 与云平台（如 ThingsBoard/AWS IoT）对接，实现远程数据可视化

⸻

致谢与声明

本代码适用于教学与个人学习，若引用请注明出处。
硬件引脚如有调整请同步修改代码参数定义。

⸻

作者：Your Name
日期：2024

### 核心功能

- **四轮驱动控制** - 精确的电机控制和方向校正
- **智能避障** - 超声波传感器自动检测障碍物
- **多控制方式** - 物理按键 + 网页界面 + 蓝牙控制
- **无线更新** - OTA固件在线升级
- **状态反馈** - LED指示灯和蜂鸣器音频提醒

### 通信功能

- **WiFi连接** - 连接到指定网络
- **WebSerial界面** - 基于网页的远程控制
- **BLE蓝牙** - Nordic UART Service，兼容iPhone应用
- **OTA更新** - 无线固件升级

## 🔧 硬件配置

### 引脚定义

```cpp
// 超声波传感器
TrigPin = 1     // 触发引脚
EchoPin = 3     // 回声引脚

// LED指示灯
GreenLedPin = 22  // 绿色LED（安全状态）
RedLedPin = 4     // 红色LED（警告状态）

// 音响设备
BuzzerPin = 13    // 蜂鸣器
ServoPin = 21     // 伺服电机

// 用户控制
ButtonPin = 2     // 启停按键

// 电机控制（H桥接口）
FL_PWM_A = 27, FL_PWM_B = 26  // 前左电机
FR_PWM_A = 32, FR_PWM_B = 16  // 前右电机
RL_PWM_A = 25, RL_PWM_B = 33  // 后左电机
RR_PWM_A = 17, RR_PWM_B = 18  // 后右电机
```

### PWM通道分配

```cpp
// LEDC通道映射
SERVO_CH = 0        // 伺服电机（自动分配）
FL_CH_A/B = 4/5     // 前左电机
FR_CH_A/B = 6/7     // 前右电机
RL_CH_A/B = 8/9     // 后左电机
RR_CH_A/B = 10/11   // 后右电机
BUZZER_CH = 12      // 蜂鸣器
```

## 📦 依赖库

### PlatformIO配置（platformio.ini）

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
    madhephaestus/ESP32Servo@^3.0.6
    mathieucarbou/Async TCP @ 3.1.4
    ayushsharma82/WebSerial@^2.1.1
    mathieucarbou/ESP Async WebServer @ 3.0.6
    h2zero/NimBLE-Arduino@^2.3.0
```

## 🛠️ 安装与配置

### 1. WiFi配置

```cpp
const char *WIFI_SSID = "WiFi_TEST";
const char *WIFI_PASSWORD = "16032390";
```

### 2. OTA配置

```cpp
const int OTA_PORT = 3232;
const char *OTA_HOSTNAME = "ESP32-241c4fb7b3f8";
```

### 3. 编译和上传

```bash
# 编译项目
pio run

# 上传到设备
pio run --target upload

# 监控串口输出
pio device monitor
```

## 🎮 控制方式

### 1. 物理按键

- **按键功能**: 启动/停止车辆
- **位置**: GPIO 2（内置上拉）
- **反馈**: LED闪烁确认

### 2. WebSerial网页控制

- **访问地址**: `http://[ESP32_IP_ADDRESS]`
- **功能**: 完整的车辆控制界面
- **实时状态**: 显示车辆运行状态和WiFi信息

### 3. BLE蓝牙控制

- **设备名称**: "ESP32-RobotCar"
- **服务**: Nordic UART Service
- **兼容应用**: Bluefruit Connect, nRF Toolbox等

## 📱 控制命令

### 通用命令（WebSerial & BLE）

```
start     - 启动车辆
stop      - 停止车辆
forward   - 前进
backward  - 后退
left      - 左转
right     - 右转
status    - 查看状态信息
hello     - 显示帮助信息
```

### 响应格式

```
[OK] Vehicle started
[OK] Moving forward
[WARNING] Vehicle not started. Send 'start' first.
[ERROR] Unknown command: xyz
```

## 🤖 工作原理

### 初始化序列

1. **WiFi连接** - LED交替闪烁，连接成功绿灯亮
2. **OTA服务** - 启动无线更新服务
3. **WebSerial** - 启动网页控制界面
4. **BLE服务** - 开始蓝牙广播
5. **硬件初始化** - 伺服归中，电机停止
6. **系统就绪** - 双音调蜂鸣提示

### 主循环逻辑

```cpp
1. OTA更新检查
2. 按键状态检测
3. 伺服位置刷新（每1秒）
4. 如果车辆启动：
   - 超声波测距
   - 距离 > 10cm：绿灯亮，前进
   - 距离 ≤ 10cm：红灯亮，停止，蜂鸣报警
5. 如果车辆停止：
   - 所有电机停止
   - LED关闭
   - 蜂鸣器静音
```

### 障碍物检测

- **检测距离**: 10cm阈值
- **传感器类型**: 超声波（HC-SR04）
- **响应动作**: 自动停车 + 红灯警告 + 蜂鸣器报警
- **蜂鸣模式**: 高低音交替（300ms间隔）

## 🔄 电机控制

### 方向修正

```cpp
// 原始发现：FL和RR正转，FR和RL反转
// 解决方案：交换FR和RL电机的A/B通道

// 前进时的正确配置：
FL: A=0, B=255  // 前左正转
FR: A=255, B=0  // 前右正转（通道已交换）
RL: A=0, B=255  // 后左正转（通道已交换）
RR: A=255, B=0  // 后右正转
```

### 速度设置

```cpp
const int SPD_NORMAL = 200;  // 正常前进速度
const int SPD_TURN = 180;    // 转弯速度
```

## 📡 网络功能

### WebSerial界面特性

- **实时状态显示** - WiFi信号、IP地址、设备ID
- **命令历史** - 显示执行的命令和响应
- **车辆状态** - 运行状态、当前动作
- **帮助信息** - 完整的命令列表

### BLE Nordic UART Service

```cpp
Service UUID: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
RX Char UUID: 6E400002-B5A3-F393-E0A9-E50E24DCCA9E  // 接收命令
TX Char UUID: 6E400003-B5A3-F393-E0A9-E50E24DCCA9E  // 发送响应
```

## 🚨 状态指示

### LED指示说明

| 状态       | 绿灯      | 红灯      | 含义               |
| ---------- | --------- | --------- | ------------------ |
| WiFi连接中 | 闪烁      | 交替闪烁  | 正在连接WiFi       |
| WiFi成功   | 常亮300ms | 关闭      | 连接成功           |
| WiFi失败   | 关闭      | 常亮300ms | 连接失败           |
| 车辆安全   | 常亮      | 关闭      | 无障碍物，正常行驶 |
| 障碍警告   | 关闭      | 常亮      | 检测到障碍物       |
| 按键确认   | 闪烁120ms | -         | 启动确认           |
| 按键确认   | -         | 闪烁120ms | 停止确认           |

### 蜂鸣器模式

- **初始化完成**: 高-低-高三音调
- **障碍物警告**: 高低音交替（300Hz/100Hz）
- **音量控制**: 10%占空比（较安静）

## 🔧 参数配置

### 可调节常量

```cpp
// 检测阈值
const float OBSTACLE_TH = 10.0;  // 障碍物距离阈值(cm)

// 电机速度
const int SPD_NORMAL = 200;      // 前进速度(0-255)
const int SPD_TURN = 180;        // 转弯速度(0-255)

// 伺服设置
const int SERVO_CENTER = 100;    // 伺服中心角度
const unsigned long SERVO_REFRESH = 1000;  // 刷新间隔(ms)

// 蜂鸣器设置
const int BUZZ_HIGH = 300;       // 高音频率(Hz)
const int BUZZ_LOW = 100;        // 低音频率(Hz)
const int BUZZ_DUTY = 100;       // 音量(0-1023)

// 按键防抖
const unsigned long DEBOUNCE = 250;  // 防抖延时(ms)
```

## 🐛 故障排除

### 常见问题

1. **车轮转向错误**

   - 检查电机接线
   - 确认A/B通道连接正确

2. **WiFi连接失败**

   - 检查SSID和密码
   - 确认网络可用性

3. **BLE无法连接**

   - 重启ESP32
   - 检查手机蓝牙设置

4. **超声波检测异常**
   - 检查传感器接线
   - 确认引脚配置

### 调试方法

- 使用WebSerial查看实时状态
- 观察LED指示灯状态
- 监听蜂鸣器提示音

## 📊 性能指标

- **WiFi连接时间**: < 10秒
- **超声波检测范围**: 2cm - 400cm
- **检测精度**: ±1cm
- **响应延迟**: < 50ms
- **电机PWM频率**: 2kHz
- **蜂鸣器频率范围**: 100Hz - 300Hz

## 🔮 扩展功能

### 可能的改进

1. **摄像头模块** - 视觉导航
2. **GPS模块** - 位置定位
3. **IMU传感器** - 姿态检测
4. **更多传感器** - 温湿度、光照等
5. **机械臂** - 物体操作能力

## 📝 版本历史

### v1.0.0 (当前版本)

- ✅ 基础四轮驱动控制
- ✅ 超声波障碍检测
- ✅ WiFi和WebSerial控制
- ✅ BLE蓝牙支持
- ✅ LED和蜂鸣器反馈
- ✅ OTA无线更新
- ✅ 电机方向修正

## 👥 贡献

### 开发团队

- **硬件设计**: ESP32开发板 + 传感器模块
- **软件开发**: Arduino框架 + PlatformIO
- **通信协议**: WiFi + BLE Nordic UART Service

### 技术栈

- **平台**: ESP32 (Espressif)
- **开发环境**: PlatformIO + VS Code
- **编程语言**: C++ (Arduino框架)
- **通信协议**: WiFi, BLE, HTTP, WebSocket
- **库依赖**: ESP32Servo, AsyncWebServer, NimBLE-Arduino

## 📄 许可证

本项目采用开源许可证，允许自由使用、修改和分发。

---

**最后更新**: 2025年
**项目状态**: 功能完整，可直接部署使用
**兼容性**: ESP32全系列开发板

H桥驱动原理：
你的小车上，每个电机都由一个叫做“H桥”的电路模块驱动。H桥有两个控制输入端（在你的代码里就是 A 和 B 两个PWM通道，比如 FL_CH_A 和 FL_CH_B）。
给这两个输入端不同的电平组合，电机就会正转、反转或停止。
比如，可能 A通道低电平(0)，B通道高电平(或PWM脉冲) 时，电机正转。
那么，A通道高电平(或PWM脉冲)，B通道低电平(0) 时，电机就会反转。
你车子前进的代码逻辑：
左边轮子 (FL, RL):
CH_A 通道设置为 0 (PWM_OFF)。
CH_B 通道设置为 计算后的速度值 (PWM_SET)。
这个组合 (A=0, B=速度) 使得左轮向前转动。
右边轮子 (FR, RR):
CH_A 通道设置为 计算后的速度值 (PWM_SET)。
CH_B 通道设置为 0 (PWM_OFF)。
这个组合 (A=速度, B=0) 使得右轮也向前转动。
为什么左右两边前进的“指令”在代码里看起来相反？
这是最关键的一点。代码里左右两边前进的指令模式不同，是因为你的小车在物理层面，左右两边的电机相对于H桥的连接方式很可能是不一样的。
镜像安装： 比如，左边的电机和右边的电机可能是镜像对称安装的。
接线反了： 或者，右边电机的正负极接到H桥输出端的时候，和左边电机是反过来的。
由于这种物理上的“反向”，才导致了你需要用“相反”的电信号指令（一个用B通道驱动，一个用A通道驱动），最终才能让所有轮子都朝着同一个能让小车前进的方向旋转。
如果你强行把代码改成一样会怎么样？
假设你把右边轮子的前进代码改成和左边一样，都用 CH_A = 0, CH_B = 速度：
Apply to README.md
速度
因为右边电机物理接线（或安装方式）决定了它对电信号的“理解”和左边是反的，所以当你给它和左轮一样的 (A=0, B=速度) 指令时，右轮实际上会向后转（相对于车身前进方向）。
结果就是： 你命令小车前进，左轮向前滚，右轮向后滚，小车很可能会原地打转，或者根本无法正常前进。
总结：
你代码里前进时左右轮PWM控制模式的“不对称”是故意且正确的，它是为了适应你小车电机在物理安装或接线上的实际情况。如果你不改变物理接线，只在代码层面把控制逻辑改成对称的，那么小车的前进功能就会出问题。
简单说：代码的“不对称”是为了达到最终车轮实际转动方向的“一致向前”。
