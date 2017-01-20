#!/bin/bash

nice -n 19 povray -D -P +WT1 +Q2 -A +W300 +H300 +Omedium_$1.png $1.pov > /dev/null 2>&1

