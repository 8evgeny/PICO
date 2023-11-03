from machine import Pin, PWM
from time import sleep
from time import time
from random import randint
import _thread

pwm = PWM(Pin(25))
pwm1 = PWM(Pin(2))
pwm2 = PWM(Pin(3))
pwm3 = PWM(Pin(4))
pwm4 = PWM(Pin(5))
pwm5 = PWM(Pin(6))
pwm.freq(1000)
pwm1.freq(500)
pwm2.freq(1000)
pwm3.freq(1000)
pwm4.freq(1000)
pwm5.freq(1000)

def led(num):
    while True:
        pwm = PWM(Pin(num))
        pwm.freq(1000)
        for duty in range(65025):
            pwm.duty_u16(duty)
            sleep(0.0001)
        for duty in range(65025, 0, -1):
            pwm.duty_u16(duty)
            sleep(0.0001)
        seconds = int(round(time()))
        print(seconds)
        sleep(randint(1,8))
led(3)
   




