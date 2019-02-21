#!/bin/bash
sed -i "s/AODV/TEAOMDV/g" test1.tcl
sed -i "s/AODV/TEAOMDV/g" test2.tcl
sed -i "s/AODV/TEAOMDV/g" test3.tcl
sed -i "s/AODV/TEAOMDV/g" test4.tcl
sed -i "s/AODV/TEAOMDV/g" test5.tcl
sed -i "s/AODV/TEAOMDV/g" test6.tcl
sed -i "s/AODV/TEAOMDV/g" test7.tcl

sed -i "s/AODV/TEAOMDV/g" test8.tcl
sed -i "s/AODV/TEAOMDV/g" test9.tcl
sed -i "s/AODV/TEAOMDV/g" test10.tcl

ns test1.tcl
gawk -f d1.awk out.tr >temp1.txt
gawk -f la.awk out.tr >temp2.txt
ns test2.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test3.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test4.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test5.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test6.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test7.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test8.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test9.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
ns test10.tcl
gawk -f d1.awk out.tr >>temp1.txt
gawk -f la.awk out.tr >>temp2.txt
gawk -f ave.awk temp1.txt 
gawk -f ave2.awk temp2.txt 

