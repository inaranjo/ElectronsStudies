ls AntiEMVATrees* | awk -F ":" '{print "nohup ./checkTask.sh  "$1" noforce  nopub > "$1"/log/launcher.txt &"}'  | grep "AntiEMVATrees" > checkAll.sh
ls AntiEMVATrees* | awk -F ":" '{print "nohup ./checkTask.sh  "$1" force  nopub > "$1"/log/launcher.txt &"}'    | grep "AntiEMVATrees" > checkAllForce.sh
ls AntiEMVATrees* | awk -F ":" '{print "nohup ./checkTask.sh  "$1" forceAll  nopub > "$1"/log/launcher.txt &"}' | grep "AntiEMVATrees" > checkAllForceAll.sh
chmod u+x checkAll*.sh 
