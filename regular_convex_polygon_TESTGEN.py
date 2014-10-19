#!/usr/bin/env python3

from random import randint, random
from math import pi, cos, sin

f = open("in", "w")
g = open("out", "w")

for i in range(5):
    n = randint(3, 1000)
    init_angle = random()*2*pi
    angle_step = 2*pi/n
    a = randint(0, n-1)
    b = randint(0, n-1)
    c = randint(0, n-1)

    while a==b:
        b = randint(0, n-1)
    while a==c or b==c:
        c = randint(0, n-1)

    a *= angle_step
    b *= angle_step
    c *= angle_step
    a += init_angle
    b += init_angle
    c += init_angle

    mul = 2 + random()*5000
    ax = cos(a)*mul
    bx = cos(b)*mul
    cx = cos(c)*mul
    ay = sin(a)*mul
    by = sin(b)*mul
    cy = sin(c)*mul
    f.write("%f %f\n"%(ax, ay))
    f.write("%f %f\n"%(bx, by))
    f.write("%f %f\n"%(cx, cy))
    g.write("%d\n"%n)
f.write("-1.0, -1.0")
f.close()
g.close()
