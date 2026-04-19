![image alt](https://github.com/SirSalch/ARIS/blob/main/Repository%20content/Logo.png?raw=true)

**🛠 В разработке ARIS** (Argentix RISC-V Interface Standard) представляет собой легковесный стандартизированный фреймворк для взаимодействия с аппаратной периферией отечественных микроконтроллеров, таких как MIK32 Амур и Baikal-U1000 (в будущем). Фреймворк заменяет стандартные тяжеловесные SDK на современный C++ интерфейс, спроектированный по принципу Zero-Cost Abstractions (абстракции с нулевой стоимостью). Проект создается как базовый низкоуровневый слой для открытой экосистемы ARGENTIX.

[ENG] *🛠 In development ARIS (Argentix RISC-V Interface Standard) is a lightweight, standardized framework for interacting with hardware peripherals of Russian microcontrollers  such as the MIK32 Amur and Baikal-U1000 (in the future). The framework replaces the standard heavyweight SDKs with a modern C++ interface designed on the principle of Zero-Cost Abstractions (zero-cost abstractions). The project is being created as a basic low-level layer for the ARGENTIX open ecosystem.*

## Применение *(Usage)*
ARIS не навязывает стиль программирования, предоставляя разработчику выбор между читаемостью и абсолютным ручным контролем.

[ENG] *ARIS does not impose a programming style, giving the developer a choice between readability and absolute manual control.*

### 1. Упрощенный API *(Simplified API)*
Предназначен для базовой инициализации периферии и чистоты кода. Функции inline скрывают рутинные битовые операции, но компилируются в максимально эффективный машинный код без вызовов подпрограмм.

[ENG] *It is intended for basic initialization of peripherals and code purity. Inline functions hide routine bit operations, but are compiled into the most efficient machine code without subroutine calls.*

### Мигание светодиода *(Led Blink)*

```c++
#include <GPIO.hpp>
#include <APB.hpp>

#define LED_PIN 1

void delay(volatile uint32_t count) {
  while (count--) {
    __asm__("nop");
  }
}

int main(void) {
  Apb::setPeripheryClocking(CLK_GPIO_0, true);
  Gpio::setMode(GPIO_0, LED_PIN, GPIO_OUTPUT);

  while (1) {
    Gpio::setState(GPIO_0, LED_PIN, HIGH);
    delay(500000);
    Gpio::setState(GPIO_0, LED_PIN, LOW);
    delay(500000);
  }
}
```
```
Вес прошивки   FLASH:148 байт,  ОЗУ:0 байт
Program weight FLASH:148 bytes, RAM:0 bytes 
```

### 2. Прямой доступ к регистрам *(Direct access to registers)*
Для задач, требующих предельного контроля. Разработчик работает напрямую с указателями на структуры регистров, имея полную прозрачность происходящих аппаратных процессов.

[ENG] *For tasks that require extreme control. The developer works directly with pointers to register structures, having full transparency of the hardware processes taking place.*

### Мигание светодиода *(Led Blink)*

```c++
#include <GPIO.hpp>
#include <APB.hpp>

#define LED_PIN 1

void delay(volatile uint32_t count) {
  while (count--) {
    __asm__("nop");
  }
}

int main(void) {
  APB->CLK_PERIPHERY_SET = CLK_GPIO_0;
  GPIO_0->DIRECTION_OUT = 1 << LED_PIN;

  while (1) {
    GPIO_0->STATE = (1 << LED_PIN);
    delay(500000);
    GPIO_0->CLEAR = (1 << LED_PIN);
    delay(500000);
  }
}
```
```
Вес прошивки   FLASH:148 байт,  ОЗУ:0 байт
Program weight FLASH:148 bytes, RAM:0 bytes 
```

## Лицензия *(License)*
GNU General public license v3.0
