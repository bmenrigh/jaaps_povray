#!/bin/bash

nice -n 19 povray -D -P +WT1 +Q2 -A +W220 +H220 +Ofast_$1.png $1.pov > /dev/null 2>&1
