#!/bin/bash

nice -n 19 povray -D -P +WT4 +Q2 -A +W500 +H500 +Omedium_$1.png $1.pov > /dev/null 2>&1

