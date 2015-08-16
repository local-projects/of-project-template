#/bin/bash

#run actual program

$1;

#upon exit, see exit status. Do something if exit wasn't clean

if [ $? -ne 0 ]; then #exited crashing

	sleep 3 #wait a bit for crash reports to be written...	

	#send crash report
	/LocalProjects/Scripts/sendCrashReport.sh 
	
else #clean exit

	#say "exit ok!"
	
fi

