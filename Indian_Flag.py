import pyfiglet
from rich import print

title1 = pyfiglet.figlet_format('Happy', font='slant')
title2 = pyfiglet.figlet_format('Independence', font='slant')
title3 = pyfiglet.figlet_format('Day', font='slant')

title4 = pyfiglet.figlet_format('studytonight')
print(f'[magenta]{title1}[/magenta][blue]{title2}[/blue][magenta]{title3}[/magenta][orange]{title4}[/orange]')

import turtle
from turtle import *

import time
time.sleep(1)

screen = turtle.Screen()
t = turtle.Turtle()
t.speed(2)

t.penup()
t.goto(-200, 125)
t.pendown()

t.color("orange")
t.begin_fill()
t.forward(400)
t.right(90)
t.forward(84)
t.right(90)
t.forward(400)
t.end_fill()
t.left(90)
t.forward(84)


t.color("green")
t.begin_fill()
t.forward(84)
t.left(90)
t.forward(400)
t.left(90)
t.forward(84)
t.end_fill()

t.penup()
t.goto(35, 0)
t.pendown()
t.color("navy")
t.begin_fill()
t.circle(35)
t.end_fill()

t.penup()
t.goto(30, 0)
t.pendown()
t.color("white")
t.begin_fill()
t.circle(30)
t.end_fill()

t.speed(20)

t.penup()
t.goto(-27, -4)
t.pendown()
t.color("navy")
for i in range(24):
    t.begin_fill()
    t.circle(2)
    t.end_fill()
    t.penup()
    t.forward(7)
    t.right(15)
    t.pendown()

t.color("navy")
t.penup()
t.goto(10, 0)
t.pendown()
t.begin_fill()
t.circle(10)
t.end_fill()


t.penup()
t.goto(0, 0)
t.pendown()
t.pensize(1)
for i in range(24):
    t.forward(30)
    t.backward(30)
    t.left(15)

t.speed(2)

t.color("Brown")
t.pensize(10)
t.penup()
t.goto(-200,125)
t.right(180)
t.pendown()
t.forward(800)

turtle.done()
