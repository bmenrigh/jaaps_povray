#!/bin/bash

nice -n 19 povray -D -P +WT4 +Q2 -A +W440 +H440 +Ofast_$1.png $1.pov > /dev/null 2>&1

