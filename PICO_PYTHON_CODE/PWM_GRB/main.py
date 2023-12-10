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

#Звезда включена (1) или выключена (0) (всего 5 шт)
starsOnOff = [1, 1, 1, 1, 1]

#Скорость нарастания яркости каждой звездыь  (всего 5 шт)
speed = [1, 1, 1, 1, 1]

####################################################################################

stars = [
    [0,0,0],
    [0,0,0],
    [0,0,0],
    [0,0,0],
    [0,0,0]
]
duty = [
    [0,0,0],
    [0,0,0],
    [0,0,0],
    [0,0,0],
    [0,0,0]
]
pwm = [
#LED_1_RGB
    PWM(Pin(0)),
    PWM(Pin(1)),
    PWM(Pin(2)),
#LED_2_BGR    
    PWM(Pin(3)),
    PWM(Pin(4)),
    PWM(Pin(5)),
#LED_3_BGR    
    PWM(Pin(6)),
    PWM(Pin(7)),
    PWM(Pin(8)),
#LED_4_BGR    
    PWM(Pin(11)),
    PWM(Pin(12)),
    PWM(Pin(13)),
#LED_5_RGB   
    PWM(Pin(18)),
    PWM(Pin(19)),
    PWM(Pin(20))  
]
# freq = [
#     pwm[0].freq(1000),
#     pwm[1].freq(1000),
#     pwm[2].freq(1000),
#     pwm[3].freq(1000),
#     pwm[4].freq(1000),
#     pwm[5].freq(1000),
#     pwm[6].freq(1000),
#     pwm[7].freq(1000),
#     pwm[8].freq(1000),
#     pwm[9].freq(1000),
#     pwm[10].freq(1000),
#     pwm[11].freq(1000),
#     pwm[12].freq(1000),
#     pwm[13].freq(1000),
#     pwm[14].freq(1000)
# ]

direction = [1, 1, 1, 1, 1]
starStarted = [0, 0, 0, 0, 0]

# Время старта
startFromDown = [
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
    if starStarted[num] == 1: #Если уже запущена
        if stars[num][0] == 1:
            duty[num][0] += speed[num]
        if stars[num][1] == 1:
            duty[num][1] += speed[num]
        if stars[num][2] == 1:
            duty[num][2] += speed[num]
        if duty[num][0] > 300:
            duty[num][0] = 300
            direction[num] = 0
            startFromUp[num] = int(round(time())) + randint(timeInUpMin, timeInUpMax)
        if duty[num][1] > 300:
            duty[num][1] = 300
            direction[num] = 0
            startFromUp[num] = int(round(time())) + randint(timeInUpMin, timeInUpMax)
        if duty[num][2] > 300:
            duty[num][2] = 300
            direction[num] = 0
            startFromUp[num] = int(round(time())) + randint(timeInUpMin, timeInUpMax)            

    if starStarted[num] == 0: #Запускаем звезду
        starStarted[num] = 1
        stars[num][0] = randint(0, 1)
        stars[num][1] = randint(0, 1)
        stars[num][2] = randint(0, 1)
        if stars[num][0] == 1:
            duty[num][0] += speed[num]
        if stars[num][1] == 1:
            duty[num][1] += speed[num]
        if stars[num][2] == 1:
            duty[num][2] += speed[num]

def minus(num):
    if stars[num][0] == 1:
        duty[num][0] += speed[num]
    if stars[num][1] == 1:
        duty[num][1] += speed[num]
    if stars[num][2] == 1:
        duty[num][2] += speed[num]

    if duty[num][0] < 0:
        duty[num][0] = 0
        stars[num][0] = 0
        starStarted[num] = 0 #остановили звезду
        direction[num] = 1
        startFromDown[num] = int(round(time())) + randint(timeInDownMin, timeInDownMax)
    if duty[num][1] < 0:
        duty[num][1] = 0
        stars[num][1] = 0
        starStarted[num] = 0 #остановили звезду
        direction[num] = 1
        startFromDown[num] = int(round(time())) + randint(timeInDownMin, timeInDownMax)
    if duty[num][2] < 0:
        duty[num][2] = 0
        stars[num][2] = 0
        starStarted[num] = 0 #остановили звезду
        direction[num] = 1
        startFromDown[num] = int(round(time())) + randint(timeInDownMin, timeInDownMax)

def setDuty(num):
    if direction[num] == 1:
        plus(num)
    if direction[num] == 0:
        minus(num)

def setPwn(num):
    if num == 0:
            pwm[0].duty_u16(duty[0][0] * duty[0][0])
            pwm[1].duty_u16(duty[0][1] * duty[0][1])
            pwm[2].duty_u16(duty[0][2] * duty[0][2])
    elif num == 1:
            pwm[3].duty_u16(duty[1][0] * duty[1][0])
            pwm[4].duty_u16(duty[1][1] * duty[1][1])
            pwm[5].duty_u16(duty[1][2] * duty[1][2])
    elif num == 2:
            pwm[6].duty_u16(duty[2][0] * duty[2][0])
            pwm[7].duty_u16(duty[2][1] * duty[2][1])
            pwm[8].duty_u16(duty[2][2] * duty[2][2])
    elif num == 3:
            pwm[9].duty_u16(duty[3][0] * duty[3][0])
            pwm[10].duty_u16(duty[3][1] * duty[3][1])
            pwm[11].duty_u16(duty[3][2] * duty[3][2])
    else:   
            pwm[12].duty_u16(duty[4][0] * duty[4][0])
            pwm[13].duty_u16(duty[4][1] * duty[4][1])
            pwm[14].duty_u16(duty[4][2] * duty[4][2])


for j in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 12, 14]:
    pwm[j].freq(1000)

while True:
    sleep(0.006)
    for i in [0, 1, 2, 3, 4]:
        if isStart(i) == 1:
            setDuty(i)
            setPwn(i)

