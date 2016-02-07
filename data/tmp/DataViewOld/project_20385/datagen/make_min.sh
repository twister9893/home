#!/bin/bash

for NAME in "MINOTAVR_1001" "MINOTAVR_1002" "MINOTAVR_1003" "MINOTAVR_1004" "MINOTAVR_1005" "MINOTAVR_1006" "MINOTAVR_1007" "MINOTAVR_2001" "MINOTAVR_2002" "MINOTAVR_2003" "MINOTAVR_2004" "MINOTAVR_2005" "MINOTAVR_2006" "MINOTAVR_2007" "MINOTAVR_2008" "MINOTAVR_2009"
do
./datagen.e ../../../data/sopr/$NAME-View.xml ./u$NAME.h
done