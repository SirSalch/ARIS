![image alt](https://github.com/SirSalch/ARIS/blob/main/Repository%20content/Logo.png?raw=true)

# ARIS
**🛠 В разработке ARIS** (Argenix RISC-V Interface Standard) представляет собой легковесный стандартизированный набор драйверов для взаимодействия с аппаратной периферией микроконтроллеров RISC-V архитектур. ARIS заменяет стандартные тяжеловесные SDK на современный C++ интерфейс, спроектированный по принципу Zero-Cost Abstractions (абстракции с нулевой стоимостью). Проект создается как базовый низкоуровневый слой для открытой экосистемы ARGENIX. https://github.com/SirSalch/Argenix

## Применение
ARIS не навязывает стиль программирования, предоставляя разработчику выбор между читаемостью и абсолютным ручным контролем.

### 1. Упрощенный API
Предназначен для чистоты кода

### Мигание светодиодом

```c++
#include <MIK32_GPIO.hpp>

enum {
  LED_PIN = 3,
  OUTPUT = 1,
  HIGH = 1,
  LOW = 0
};

void delay(volatile uint32_t count) {
  while (count--) {
    __asm__("nop");
  }
}

int main() {
  GPIO_0.setClocking(true);
  GPIO_0.setMode(LED_PIN, OUTPUT);
  while (1) {
    GPIO_0.setState(LED_PIN, HIGH);
    delay(500000);
    GPIO_0.setState(LED_PIN, LOW);
    delay(500000);
  }
}

```
```
Вес прошивки ЕЕПРОМ:124 байт, ОЗУ:0 байт
```

### 2. Прямой доступ к регистрам
Для задач, требующих предельного контроля. Разработчик работает напрямую с указателями на структуры регистров, имея полную прозрачность происходящих аппаратных процессов.

### Мигание светодиодом

```c++
#include <MIK32_GPIO.hpp>

enum {
  LED_PIN = 3,
  OUTPUT = 1,
  HIGH = 1,
  LOW = 0
};

void delay(volatile uint32_t count) {
  while (count--) {
    __asm__("nop");
  }
}

int main() {
  APB->CLK_PERIPHERY_SET = CLK_GPIO_0;
  GPIO_0_REG.DIRECTION_OUT = OUTPUT << LED_PIN;
  while (1) {
    GPIO_0_REG.STATE = 1 << LED_PIN;
    delay(500000);
    GPIO_0_REG.CLEAR = 1 << LED_PIN;
    delay(500000);
  }
}
```
```
Вес прошивки ЕЕПРОМ:124 байт, ОЗУ:0 байт
```

## Лицензия
GNU General public license v3.0
