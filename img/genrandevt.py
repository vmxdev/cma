#!/usr/bin/env python

import random

lim = 200
i = 0
while i < lim:
    dist = random.randint(0, 5)
    if dist > 0:
        x = 0
        while (x < dist) and ((i + x) < lim):
            print '%d\t0' % ((i + x) - lim)
            x += 1
        i += x
    print '%d\t1' % (i - lim)
    i += 1
