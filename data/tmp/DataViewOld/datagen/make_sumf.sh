#!/bin/bash

for NAME in "SUMF_IP1" "SUMF_IP3" "SUMF_IP4" "SUMF_IP6" "SUMF_IP8"\
  "SUMF_IP10" "SUMF_IP11" "SUMF_IP12" "SUMF_IP34"\
  "SUMF_IP41" "SUMF_IP44" "SUMF_IP45"
do
./datagen.e ../../../data/sopr/$NAME-View.xml ./u$NAME.h
done
