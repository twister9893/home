#!/bin/bash

for NAME in "MUS_IP1" "MUS_IP2" "MUS_IP3" "MUS_IP4"\
  "MUS_IP11" "MUS_IP12" "MUS_IP37" "MUS_IP40"\
  "MUS_IP60" "MUS_IP61"
do
./datagen.e ../../../data/sopr/$NAME-View.xml ./u$NAME.h
done
