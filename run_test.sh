#!/bin/bash

FUNCTIONTYPE=$1 #Gets the function type like getsections or getsyms
OBJFILE=$2 #object file being examined 
FLAGTYP=$3 # RTLD_LAZY or RTLD_NOW
 

TIME_FILE="${FUNCTIONTYPE}_${FLAGTYP}.time.log"
> "$TIME_FILE" #Clear/reset the timing log

#Run it 50 times with the first Flag
for i in {1..50}; do
    ./$FUNCTIONTYPE $OBJFILE $FLAGTYP> /dev/null 
    #redirect stdout to /dev/null to silence terminal 
    #redirect stdError to TIMINGS_FILE (stdError is where the timings are stored)
done 
echo -n "Average: " >> $TIME_FILE
awk '{ total += $1; count++ } END { print total/count }' "$TIME_FILE" >> "$TIME_FILE" #Append average 
#awk allows us to look at line by line and add the total value 


#Start at previous Line_Num + 1
#awk allows us to look at line by line and add the total value 
#This bash script will store both averages in one file 




