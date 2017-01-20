#!/bin/bash

nice -n 19 povray -D -P +WT1 +Q11 +A0.1 +W800 +H800 +AM1 +R4 -J +Ojob_$1.png $1.pov > /dev/null 2>&1
