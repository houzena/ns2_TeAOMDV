# -*-	Mode:tcl -*-
#
# Copyright (c) 1997 University of Southern California.
# All rights reserved.                                            
#                                                                
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation, advertising
# materials, and other materials related to such distribution and use
# acknowledge that the software was developed by the University of
# Southern California, Information Sciences Institute.  The name of the
# University may not be used to endorse or promote products derived from
# this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITHOUT ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#

# This file should contain variables changed only by autoconf.

proc checkout_executable {exe_var best alternate text} {
	global $exe_var
	set $exe_var $best
	if {"$best" == "" || ![file executable $best]} {
		puts stderr $text
		set $exe_var $alternate
	}
}

#
# Keep track of where the good perl is.
#
checkout_executable PERL "/usr/bin/perl" perl "\
	When configured, ns found the right version of perl in\
	/usr/bin/perl
	but it doesn't seem to be there anymore, so\
	ns will fall back on running the first perl in your path.\
	The wrong version of perl may break the test suites.\
	Reconfigure and rebuild ns if this is a problem.\
"
checkout_executable TCLSH "/home/houzena/Downloads/ns-allinone-2.35/bin/tclsh8.5" tclsh "\
	When configured, ns found the right version of tclsh in\
	/home/houzena/Downloads/ns-allinone-2.35/bin/tclsh8.5
	but it doesn't seem to be there anymore, so\
	ns will fall back on running the first tclsh in your path.\
	The wrong version of tclsh may break the test suites.\
	Reconfigure and rebuild ns if this is a problem.\
"
