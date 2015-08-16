#/bin/bash

# configuration ###################################################################
binaryName="SampleApp"
folderName="SampleApp"
whoFrom="yourName@localprojects.com" << develop email goes here
emailPass="xxxxxxxxxxxx" # Fill in with your LP gmail account password - this really sucks!! I know! :(
whoTo="oriol@localprojects.net;keeli@localprojects.net" #you can have people emailed separating them with ";"
subject="$binaryName Automated Crash Report"
appLogDir="/LocalProjects/$folderName/data/logs"

###################################################################################

tempFileName="mail.tmp"

cd $HOME

#split mail recipients in array
arrayWhoTo=(${whoTo//;/ })

#count how many recipients we have
numWhoTo=${#arrayWhoTo[@]}; 

#construct curl recipient arguments string
whoToArgs="";
echo "sending emails to:";

for (( i=0; i<${numWhoTo}; i++ ));
do
	echo "   ${arrayWhoTo[$i]}";
	whoToArgs="$whoToArgs --mail-rcpt ${arrayWhoTo[$i]}"
done

#rm temp file just in case
rm $tempFileName;

#write email to from subject etc. into temp file
echo "From: <$whoFrom>\nTo: <$whoTo>\nSubject: $subject\n" > $tempFileName;

echo "This happened at: " >> $tempFileName;
date >> $tempFileName #print date in mail
echo "\n\n# OSX Crash Report ##################################################\n\n" >> $tempFileName

#fetch the newest OSX crash report for our app
logFile=`ls -t ~/Library/Logs/DiagnosticReports/ | grep $binaryName | head -1`;
logFile="$HOME/Library/Logs/DiagnosticReports/$logFile"; #get the abs path to the crash report

#append crash report to temp email file
cat $logFile >> $tempFileName  

echo "\n\n# App Crash Report ##################################################\n\n " >> $tempFileName

#fetch the newest app crash report 
logFile=`ls -t "$appLogDir" | head -1`;
logFile="$appLogDir/$logFile"; #get the abs path to the crash report

#append crash report to temp email file
cat $logFile >> $tempFileName  

echo "\n\n#####################################################################\n\n" >> $tempFileName


#send it all in an email
curl --silent --url "smtps://smtp.gmail.com:465" --ssl-reqd --mail-from $whoFrom $whoToArgs  --upload-file $tempFileName --user "$whoFrom:$emailPass" --insecure

#rem temp email file
rm $tempFileName;
