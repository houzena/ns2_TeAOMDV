#
# nodes: 30, max conn: 10, send rate: 0.25, seed: 88
#
#
# 1 connecting to 2 at time 44.94108882031454
#
set udp_(0) [new Agent/UDP]
$ns_ attach-agent $node_(1) $udp_(0)
set null_(0) [new Agent/Null]
$ns_ attach-agent $node_(2) $null_(0)
set cbr_(0) [new Application/Traffic/CBR]
$cbr_(0) set packetSize_ 512
$cbr_(0) set interval_ 0.25
$cbr_(0) set random_ 1
$cbr_(0) set maxpkts_ 10000
$cbr_(0) attach-agent $udp_(0)
$ns_ connect $udp_(0) $null_(0)
$ns_ at 44.94108882031454 "$cbr_(0) start"
#
# 1 connecting to 3 at time 135.80142894564264
#
set udp_(1) [new Agent/UDP]
$ns_ attach-agent $node_(1) $udp_(1)
set null_(1) [new Agent/Null]
$ns_ attach-agent $node_(3) $null_(1)
set cbr_(1) [new Application/Traffic/CBR]
$cbr_(1) set packetSize_ 512
$cbr_(1) set interval_ 0.25
$cbr_(1) set random_ 1
$cbr_(1) set maxpkts_ 10000
$cbr_(1) attach-agent $udp_(1)
$ns_ connect $udp_(1) $null_(1)
$ns_ at 135.80142894564264 "$cbr_(1) start"
#
# 2 connecting to 3 at time 58.570191459064461
#
set udp_(2) [new Agent/UDP]
$ns_ attach-agent $node_(2) $udp_(2)
set null_(2) [new Agent/Null]
$ns_ attach-agent $node_(3) $null_(2)
set cbr_(2) [new Application/Traffic/CBR]
$cbr_(2) set packetSize_ 512
$cbr_(2) set interval_ 0.25
$cbr_(2) set random_ 1
$cbr_(2) set maxpkts_ 10000
$cbr_(2) attach-agent $udp_(2)
$ns_ connect $udp_(2) $null_(2)
$ns_ at 58.570191459064461 "$cbr_(2) start"
#
# 2 connecting to 4 at time 97.273656948131332
#
set udp_(3) [new Agent/UDP]
$ns_ attach-agent $node_(2) $udp_(3)
set null_(3) [new Agent/Null]
$ns_ attach-agent $node_(4) $null_(3)
set cbr_(3) [new Application/Traffic/CBR]
$cbr_(3) set packetSize_ 512
$cbr_(3) set interval_ 0.25
$cbr_(3) set random_ 1
$cbr_(3) set maxpkts_ 10000
$cbr_(3) attach-agent $udp_(3)
$ns_ connect $udp_(3) $null_(3)
$ns_ at 97.273656948131332 "$cbr_(3) start"
#
# 3 connecting to 4 at time 116.06328028070892
#
set udp_(4) [new Agent/UDP]
$ns_ attach-agent $node_(3) $udp_(4)
set null_(4) [new Agent/Null]
$ns_ attach-agent $node_(4) $null_(4)
set cbr_(4) [new Application/Traffic/CBR]
$cbr_(4) set packetSize_ 512
$cbr_(4) set interval_ 0.25
$cbr_(4) set random_ 1
$cbr_(4) set maxpkts_ 10000
$cbr_(4) attach-agent $udp_(4)
$ns_ connect $udp_(4) $null_(4)
$ns_ at 116.06328028070892 "$cbr_(4) start"
#
# 3 connecting to 5 at time 39.580217674179103
#
set udp_(5) [new Agent/UDP]
$ns_ attach-agent $node_(3) $udp_(5)
set null_(5) [new Agent/Null]
$ns_ attach-agent $node_(5) $null_(5)
set cbr_(5) [new Application/Traffic/CBR]
$cbr_(5) set packetSize_ 512
$cbr_(5) set interval_ 0.25
$cbr_(5) set random_ 1
$cbr_(5) set maxpkts_ 10000
$cbr_(5) attach-agent $udp_(5)
$ns_ connect $udp_(5) $null_(5)
$ns_ at 39.580217674179103 "$cbr_(5) start"
#
# 5 connecting to 6 at time 80.001556230709681
#
set udp_(6) [new Agent/UDP]
$ns_ attach-agent $node_(5) $udp_(6)
set null_(6) [new Agent/Null]
$ns_ attach-agent $node_(6) $null_(6)
set cbr_(6) [new Application/Traffic/CBR]
$cbr_(6) set packetSize_ 512
$cbr_(6) set interval_ 0.25
$cbr_(6) set random_ 1
$cbr_(6) set maxpkts_ 10000
$cbr_(6) attach-agent $udp_(6)
$ns_ connect $udp_(6) $null_(6)
$ns_ at 80.001556230709681 "$cbr_(6) start"
#
# 6 connecting to 7 at time 58.639456740878273
#
set udp_(7) [new Agent/UDP]
$ns_ attach-agent $node_(6) $udp_(7)
set null_(7) [new Agent/Null]
$ns_ attach-agent $node_(7) $null_(7)
set cbr_(7) [new Application/Traffic/CBR]
$cbr_(7) set packetSize_ 512
$cbr_(7) set interval_ 0.25
$cbr_(7) set random_ 1
$cbr_(7) set maxpkts_ 10000
$cbr_(7) attach-agent $udp_(7)
$ns_ connect $udp_(7) $null_(7)
$ns_ at 58.639456740878273 "$cbr_(7) start"
#
# 6 connecting to 8 at time 2.6476869744470748
#
set udp_(8) [new Agent/UDP]
$ns_ attach-agent $node_(6) $udp_(8)
set null_(8) [new Agent/Null]
$ns_ attach-agent $node_(8) $null_(8)
set cbr_(8) [new Application/Traffic/CBR]
$cbr_(8) set packetSize_ 512
$cbr_(8) set interval_ 0.25
$cbr_(8) set random_ 1
$cbr_(8) set maxpkts_ 10000
$cbr_(8) attach-agent $udp_(8)
$ns_ connect $udp_(8) $null_(8)
$ns_ at 2.6476869744470748 "$cbr_(8) start"
#
# 7 connecting to 8 at time 50.712265442457173
#
set udp_(9) [new Agent/UDP]
$ns_ attach-agent $node_(7) $udp_(9)
set null_(9) [new Agent/Null]
$ns_ attach-agent $node_(8) $null_(9)
set cbr_(9) [new Application/Traffic/CBR]
$cbr_(9) set packetSize_ 512
$cbr_(9) set interval_ 0.25
$cbr_(9) set random_ 1
$cbr_(9) set maxpkts_ 10000
$cbr_(9) attach-agent $udp_(9)
$ns_ connect $udp_(9) $null_(9)
$ns_ at 50.712265442457173 "$cbr_(9) start"
#
#Total sources/connections: 6/10
#
