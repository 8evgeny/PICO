from machine import Pin, PWM
from time import sleep
from time import time
from random import randint


########  ПАРАМЕТРЫ ДЛЯ КОРРЕКТИРОВКИ  ##########################################
#Время ожидания запуска одной звезды в секундах (случайная величина от и до)
timeInDownMin = 1
timeInDownMax = 30

#Время максимальной яркости одной звезды в секундах (случайная величина от и до)
timeInUpMin = 2
timeInUpMax = 4

#Звезда включена (1) или выключена (0) (всего 16 шт)
starsOnOff = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]

#Скорость нарастания яркости каждой звездыь  (всего 16 шт)
speed = [1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 3, 1, 2, 3, 4]

#Максимальное число одновременно запущенных звезд
numMaxStars=5


####################################################################################









pwm = [
    PWM(Pin(0)),
    PWM(Pin(1)),
    PWM(Pin(2)),
    PWM(Pin(3)),
    PWM(Pin(4)),
    PWM(Pin(5)),
    PWM(Pin(6)),
    PWM(Pin(7)),
    PWM(Pin(8)),
    PWM(Pin(9)),
    PWM(Pin(10)),
    PWM(Pin(11)),
    PWM(Pin(12)),
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
    pwm[5].freq(1000),
    pwm[6].freq(1000),
    pwm[7].freq(1000),
    pwm[8].freq(1000),
    pwm[9].freq(1000),
    pwm[10].freq(1000),
    pwm[11].freq(1000),
    pwm[12].freq(1000),
    pwm[13].freq(1000),
    pwm[14].freq(1000),
    pwm[15].freq(1000)
]
duty = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
direction = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
numStarStarted = 0
starStarted = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

# Время старта
startFromDown = [
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax),
    int(round(time())) + randint(timeInDownMin, timeInDownMax)
]

startFromUp = [
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax),
    int(round(time())) + randint(timeInUpMin, timeInUpMax)
]


def isStart(num):
    if round(time()) > startFromDown[num]:
        if round(time()) > startFromUp[num]:
            return 1
        else :
            return 0
    else :
        return 0

def plus(num):
    global numStarStarted
    if starStarted[num] == 1: #Если уже запущена
        duty[num] +=speed[num]
        if duty[num] > 250:
            duty[num] = 250
            direction[num] = 0
            startFromUp[num] = int(round(time())) + randint(timeInUpMin, timeInUpMax)
    if starStarted[num] == 0: #Запускаем звезду
        if  numStarStarted <= numMaxStars:
            numStarStarted +=1
            duty[num] +=speed[num]

def minus(num):
    global numStarStarted
    duty[num] -=speed[num]
    if duty[num] < 0:
        duty[num] = 0
        numStarStarted -= 1
        starStarted[num] = 0 #остановили звезду
        direction[num] = 1
        startFromDown[num] = int(round(time())) + randint(timeInDownMin, timeInDownMax)

def setDuty(num):
    if direction[num] == 1:
        plus(num)
    if direction[num] == 0:
        minus(num)

def setPwn(num):
    pwm[num].duty_u16(duty[num] * duty[num])

while True:
    sleep(0.06)
    for i in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]:
        if starsOnOff[i] == 1:
            if isStart(i) == 1:
                setDuty(i)
                setPwn(i)
        if starsOnOff[i] == 0:
            pwm[i].duty_u16(0)
