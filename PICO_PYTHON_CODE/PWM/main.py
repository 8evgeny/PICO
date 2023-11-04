from machine import Pin, PWM
from time import sleep
from time import time
from random import randint
import _thread

pwm = [
    PWM(Pin(25)),
    PWM(Pin(2)),
    PWM(Pin(3)),
    PWM(Pin(13)),
    PWM(Pin(14)),
    PWM(Pin(15))
]
freq = [
    pwm[0].freq(1000),
    pwm[1].freq(1000),
    pwm[2].freq(1000),
    pwm[3].freq(1000),
    pwm[4].freq(1000),
    pwm[5].freq(1000)
]
duty = [0,0,0,0,0,0]
direction = [1,1,1,1,1,1]

# Время старта
start = [
    int(round(time())) + randint(1,30),
    int(round(time())) + randint(1,30),
    int(round(time())) + randint(1,30),
    int(round(time())) + randint(1,30),
    int(round(time())) + randint(1,30),
    int(round(time())) + randint(1,30)
]

def isStart(num):
    if round(time()) > start[num]:
        return 1
    else :
        return 0

def setDuty(num):
    if direction[num] == 1:
        duty[num] +=1
        if duty[num] > 250:
            duty[num] = 250
            direction[num] = 0
    if direction[num] == 0:
        duty[num] -=1
    if duty[num] < 0:
        duty[num] = 0
        direction[num] = 1
        start[num] = int(round(time())) + randint(1,30)

def setPwn(num):
    pwm[num].duty_u16(duty[num] * duty[num])

while True:
    sleep(0.01)
    for i in [0, 1, 2, 3, 4, 5]:
        if isStart(i) == 1:
            setDuty(i)
            setPwn(i)
