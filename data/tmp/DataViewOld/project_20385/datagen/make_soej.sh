#!/bin/bash

for NAME in "SOEJ_FromSIGMA" "SOEJ_ToSIGMA"
do
./datagen.e ../../../data/sopr/$NAME-View.xml ./u$NAME.h
done
