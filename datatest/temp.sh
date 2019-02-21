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

gawk -f ave.awk temp1.txt
gawk -f ave2.awk temp2.txt
