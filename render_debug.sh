#!/bin/bash

nice -n 19 povray -P -D +WT1 +Q2 -A +W550 +H550 +Oslow_$1.png $1.pov > /tmp/debug.txt 2>&1

