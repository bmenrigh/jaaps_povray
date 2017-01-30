#!/bin/bash

nice -n 19 povray -P -D +WT4 +Q2 -A +W800 +H800 +Oslow_$1.png $1.pov > /dev/null 2>&1

