#
# nodes: 30, max conn: 2, send rate: 1.0, seed: 222
#
#
# 3 connecting to 4 at time 169.0824179766152
#
set udp_(0) [new Agent/UDP]
$ns_ attach-agent $node_(3) $udp_(0)
set null_(0) [new Agent/Null]
$ns_ attach-agent $node_(4) $null_(0)
set cbr_(0) [new Application/Traffic/CBR]
$cbr_(0) set packetSize_ 512
$cbr_(0) set interval_ 1.0
$cbr_(0) set random_ 1
$cbr_(0) set maxpkts_ 10000
$cbr_(0) attach-agent $udp_(0)
$ns_ connect $udp_(0) $null_(0)
$ns_ at 169.0824179766152 "$cbr_(0) start"
#
# 8 connecting to 9 at time 110.78207208345739
#
set udp_(1) [new Agent/UDP]
$ns_ attach-agent $node_(8) $udp_(1)
set null_(1) [new Agent/Null]
$ns_ attach-agent $node_(9) $null_(1)
set cbr_(1) [new Application/Traffic/CBR]
$cbr_(1) set packetSize_ 512
$cbr_(1) set interval_ 1.0
$cbr_(1) set random_ 1
$cbr_(1) set maxpkts_ 10000
$cbr_(1) attach-agent $udp_(1)
$ns_ connect $udp_(1) $null_(1)
$ns_ at 110.78207208345739 "$cbr_(1) start"
#
#Total sources/connections: 2/2
#
