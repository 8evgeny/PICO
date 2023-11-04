from machine import Pin, PWM
from time import sleep
from time import time
from random import randint
import _thread

pwm1 = PWM(Pin(25))
pwm2 = PWM(Pin(2))
pwm3 = PWM(Pin(3))
pwm4 = PWM(Pin(13))
pwm5 = PWM(Pin(14))
pwm6 = PWM(Pin(15))
pwm1.freq(1000)
pwm2.freq(1000)
pwm3.freq(1000)
pwm4.freq(1000)
pwm5.freq(1000)
pwm6.freq(1000)
duty1 = 0
duty2 = 0
duty3 = 0
duty4 = 0
duty5 = 0
duty6 = 0
direction1 = 1
direction2 = 1
direction3 = 1
direction4 = 1
direction5 = 1
direction6 = 1

# Время старта
start1 = int(round(time())) + randint(1,20)
start2 = int(round(time())) + randint(1,20)
start3 = int(round(time())) + randint(1,20)
start4 = int(round(time())) + randint(1,20)
start5 = int(round(time())) + randint(1,20)
start6 = int(round(time())) + randint(1,20)

while True:
    sleep(0.05)
    if round(time()) > start1 :
        if direction1 == 1 :
            duty1 = duty1 + 1
            if duty1 > 250 :
                duty1 = 250
                direction1 = 0
        if direction1 == 0:
            duty1 = duty1 - 1
            if duty1 < 0 :
                duty1 = 0
                direction1 = 1
                start1 = int(round(time())) + randint(1,20)
    if round(time()) > start2 :
        if direction2 == 1 :
            duty2 = duty2 + 1
            if duty2 > 250 :
                duty2 = 250
                direction2 = 0
        if direction2 == 0:
            duty2 = duty2 - 1
            if duty2 < 0 :
                duty2 = 0
                direction2 = 1
                start2 = int(round(time())) + randint(1,20)
    if round(time()) > start3 :
        if direction3 == 1 :
            duty3 = duty3 + 1
            if duty3 > 250 :
                duty3 = 250
                direction3 = 0
        if direction3 == 0:
            duty3 = duty3 - 1
            if duty3 < 0 :
                duty3 = 0
                direction3 = 1
                start3 = int(round(time())) + randint(1,20)
    pwm1.duty_u16(duty1 * duty1)
    pwm2.duty_u16(duty2 * duty2)
    pwm3.duty_u16(duty3 * duty3)





#
# def led1(pwm):
#     pwm.freq(1000)
#     for duty in range(250):
#         pwm.duty_u16(duty * duty)
#         sleep(0.05)
#     for duty in range(250, 0, -1):
#         pwm.duty_u16(duty * duty)
#         sleep(0.05)
#     seconds = int(round(time()))
#     print(seconds)
#     sleep(randint(1,8))
#    return int(round(time())) + randint(1,20)
        


# while True:
#
#
#
#
#     if(int(round(time())) > start1)
#         start 1 = led(pwm1)


   




