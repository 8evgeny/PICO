import board
import time
from digitalio import DigitalInOut, Direction

# Конфигурация пина со светодиодом
led = DigitalInOut(board.LED)
led.direction = Direction.OUTPUT

# Наш рабочий бесконечный цикл
while True:
    # Переключить светодиод
    print("hello!!!!")
    led.value = not led.value
    time.sleep(1.1)
