#!/bin/bash

date >testdata.txt
echo "----------------------------------" >>testdata.txt
cd /home/houzena/test1228/test
echo "0 m node:" >>testdata.txt



./de.sh

sed -i "s/1!=1/index==16||index==17/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test
echo "----------------------------------" >>testdata.txt

echo "2 m node:" >>testdata.txt

./de.sh

sed -i "s/index==16||index==17/index==16||index==27/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "2 m node:" >>testdata.txt

./de.sh

sed -i "s/index==16||index==27/index==31||index==32/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "2 m node:" >>testdata.txt



./de.sh

sed -i "s/index==31||index==32/index==16||index==17||index==18||index==19/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test
echo "----------------------------------" >>testdata.txt

echo "4 m node:" >>testdata.txt

./de.sh

sed -i "s/index==16||index==17||index==18||index==19/index==16||index==27||index==7||index==35/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "4 m node:" >>testdata.txt

./de.sh

sed -i "s/index==16||index==27||index==7||index==35/index==31||index==32||index==23||index==24/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "4 m node:" >>testdata.txt

./de.sh



sed -i "s/index==31||index==32||index==23||index==24/index==16||index==17||index==18||index==19||index==23||index==24/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "----------------------------------" >>testdata.txt

echo "6 m node:" >>testdata.txt

./de.sh

sed -i "s/index==16||index==17||index==18||index==19||index==23||index==24/index==7||index==17||index==27||index==37||index==25||index==35/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "6 m node:" >>testdata.txt

./de.sh

sed -i "s/index==7||index==17||index==27||index==37||index==25||index==35/index==31||index==35||index==38||index==29||index==27||index==19/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "6 m node:" >>testdata.txt

./de.sh



sed -i "s/index==31||index==35||index==38||index==29||index==27||index==19/index==15||index==16||index==17||index==28||index==29||index==30||index==33||index==34/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "----------------------------------" >>testdata.txt

echo "8 m node:" >>testdata.txt

./de.sh

sed -i "s/index==15||index==16||index==17||index==28||index==29||index==30||index==33||index==34/index==12||index==14||index==16||index==18||index==20||index==22||index==24||index==26/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "8 m node:" >>testdata.txt

./de.sh

sed -i "s/index==12||index==14||index==16||index==18||index==20||index==22||index==24||index==26/index==1||index==7||index==6||index==9||index==21||index==23||index==29||index==32/" /home/houzena/Downloads/ns-allinone-2.35/ns-2.35/aomdv/aomdv.cc

cd /home/houzena/Downloads/ns-allinone-2.35/ns-2.35
make all

cd /home/houzena/test1228/test

echo "8 m node:" >>testdata.txt

./de.sh

echo "----------------------------------" >>testdata.txt
date >>testdata.txt






