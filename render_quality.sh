#!/bin/bash

nice -n 19 povray -D -P +WT2 +Q11 +A0.2 +W1200 +H1200 +AM1 +R5 +J1 +Ojob_$1.png $1.pov > /dev/null 2>&1
