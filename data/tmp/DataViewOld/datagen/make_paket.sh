#!/bin/bash

for NAME in "PAKET_IN" "PAKET_OUT"
do
./datagen.e ../../../data/sopr/$NAME-View.xml ./u$NAME.h
done 