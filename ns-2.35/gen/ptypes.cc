static const char code[] = "\n\
global ptype pvals\n\
set ptype(error) -1\n\
set pvals(-1) error\n\
set ptype(tcp) 0\n\
set pvals(0) tcp\n\
set ptype(udp) 1\n\
set pvals(1) udp\n\
set ptype(cbr) 2\n\
set pvals(2) cbr\n\
set ptype(audio) 3\n\
set pvals(3) audio\n\
set ptype(video) 4\n\
set pvals(4) video\n\
set ptype(ack) 5\n\
set pvals(5) ack\n\
set ptype(start) 6\n\
set pvals(6) start\n\
set ptype(stop) 7\n\
set pvals(7) stop\n\
set ptype(prune) 8\n\
set pvals(8) prune\n\
set ptype(graft) 9\n\
set pvals(9) graft\n\
set ptype(graftack) 10\n\
set pvals(10) graftAck\n\
set ptype(join) 11\n\
set pvals(11) join\n\
set ptype(assert) 12\n\
set pvals(12) assert\n\
set ptype(message) 13\n\
set pvals(13) message\n\
set ptype(rtcp) 14\n\
set pvals(14) rtcp\n\
set ptype(rtp) 15\n\
set pvals(15) rtp\n\
set ptype(rtprotodv) 16\n\
set pvals(16) rtProtoDV\n\
set ptype(ctrmcast_encap) 17\n\
set pvals(17) CtrMcast_Encap\n\
set ptype(ctrmcast_decap) 18\n\
set pvals(18) CtrMcast_Decap\n\
set ptype(srm) 19\n\
set pvals(19) SRM\n\
set ptype(sa_req) 20\n\
set pvals(20) sa_req\n\
set ptype(sa_accept) 21\n\
set pvals(21) sa_accept\n\
set ptype(sa_conf) 22\n\
set pvals(22) sa_conf\n\
set ptype(sa_teardown) 23\n\
set pvals(23) sa_teardown\n\
set ptype(live) 24\n\
set pvals(24) live\n\
set ptype(sa_reject) 25\n\
set pvals(25) sa_reject\n\
set ptype(telnet) 26\n\
set pvals(26) telnet\n\
set ptype(ftp) 27\n\
set pvals(27) ftp\n\
set ptype(pareto) 28\n\
set pvals(28) pareto\n\
set ptype(exp) 29\n\
set pvals(29) exp\n\
set ptype(httpinval) 30\n\
set pvals(30) httpInval\n\
set ptype(http) 31\n\
set pvals(31) http\n\
set ptype(encap) 32\n\
set pvals(32) encap\n\
set ptype(mftp) 33\n\
set pvals(33) mftp\n\
set ptype(arp) 34\n\
set pvals(34) ARP\n\
set ptype(mac) 35\n\
set pvals(35) MAC\n\
set ptype(tora) 36\n\
set pvals(36) TORA\n\
set ptype(dsr) 37\n\
set pvals(37) DSR\n\
set ptype(aodv) 38\n\
set pvals(38) AODV\n\
set ptype(imep) 39\n\
set pvals(39) IMEP\n\
set ptype(rap_data) 40\n\
set pvals(40) rap_data\n\
set ptype(rap_ack) 41\n\
set pvals(41) rap_ack\n\
set ptype(tcpfriend) 42\n\
set pvals(42) tcpFriend\n\
set ptype(tcpfriendctl) 43\n\
set pvals(43) tcpFriendCtl\n\
set ptype(ping) 44\n\
set pvals(44) ping\n\
set ptype(pbc) 45\n\
set pvals(45) PBC\n\
set ptype(diffusion) 46\n\
set pvals(46) diffusion\n\
set ptype(rtprotols) 47\n\
set pvals(47) rtProtoLS\n\
set ptype(ldp) 48\n\
set pvals(48) LDP\n\
set ptype(gaf) 49\n\
set pvals(49) gaf\n\
set ptype(ra) 50\n\
set pvals(50) ra\n\
set ptype(pushback) 51\n\
set pvals(51) pushback\n\
set ptype(pgm) 52\n\
set pvals(52) PGM\n\
set ptype(lms) 53\n\
set pvals(53) LMS\n\
set ptype(lms_setup) 54\n\
set pvals(54) LMS_SETUP\n\
set ptype(sctp) 55\n\
set pvals(55) sctp\n\
set ptype(sctp_app1) 56\n\
set pvals(56) sctp_app1\n\
set ptype(smac) 57\n\
set pvals(57) smac\n\
set ptype(xcp) 58\n\
set pvals(58) xcp\n\
set ptype(hdlc) 59\n\
set pvals(59) HDLC\n\
set ptype(belllabstrace) 60\n\
set pvals(60) BellLabsTrace\n\
set ptype(aomdv) 61\n\
set pvals(61) AOMDV\n\
set ptype(puma) 62\n\
set pvals(62) PUMA\n\
set ptype(dccp) 63\n\
set pvals(63) DCCP\n\
set ptype(dccp_request) 64\n\
set pvals(64) DCCP_Request\n\
set ptype(dccp_response) 65\n\
set pvals(65) DCCP_Response\n\
set ptype(dccp_ack) 66\n\
set pvals(66) DCCP_Ack\n\
set ptype(dccp_data) 67\n\
set pvals(67) DCCP_Data\n\
set ptype(dccp_dataack) 68\n\
set pvals(68) DCCP_DataAck\n\
set ptype(dccp_close) 69\n\
set pvals(69) DCCP_Close\n\
set ptype(dccp_closereq) 70\n\
set pvals(70) DCCP_CloseReq\n\
set ptype(dccp_reset) 71\n\
set pvals(71) DCCP_Reset\n\
set ptype(mdart) 72\n\
set pvals(72) MDART\n\
proc ptype2val {str} {\n\
global ptype\n\
set str [string tolower $str]\n\
if ![info exists ptype($str)] {\n\
set str error\n\
}\n\
set ptype($str)\n\
}\n\
proc pval2type {val} {\n\
global pvals\n\
if ![info exists pvals($val)] {\n\
set val -1\n\
}\n\
set pvals($val)\n\
}\n\
";
#include "config.h"
EmbeddedTcl et_ns_ptypes(code);
