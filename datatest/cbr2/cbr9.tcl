#
# nodes: 30, max conn: 10, send rate: 0.25, seed: 16
#
#
# 1 connecting to 2 at time 40.898983655916055
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
$ns_ at 40.898983655916055 "$cbr_(0) start"
#
# 1 connecting to 3 at time 73.782854459147359
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
$ns_ at 73.782854459147359 "$cbr_(1) start"
#
# 3 connecting to 4 at time 1.3232595200293042
#
set udp_(2) [new Agent/UDP]
$ns_ attach-agent $node_(3) $udp_(2)
set null_(2) [new Agent/Null]
$ns_ attach-agent $node_(4) $null_(2)
set cbr_(2) [new Application/Traffic/CBR]
$cbr_(2) set packetSize_ 512
$cbr_(2) set interval_ 0.25
$cbr_(2) set random_ 1
$cbr_(2) set maxpkts_ 10000
$cbr_(2) attach-agent $udp_(2)
$ns_ connect $udp_(2) $null_(2)
$ns_ at 1.3232595200293042 "$cbr_(2) start"
#
# 3 connecting to 5 at time 11.441538646557152
#
set udp_(3) [new Agent/UDP]
$ns_ attach-agent $node_(3) $udp_(3)
set null_(3) [new Agent/Null]
$ns_ attach-agent $node_(5) $null_(3)
set cbr_(3) [new Application/Traffic/CBR]
$cbr_(3) set packetSize_ 512
$cbr_(3) set interval_ 0.25
$cbr_(3) set random_ 1
$cbr_(3) set maxpkts_ 10000
$cbr_(3) attach-agent $udp_(3)
$ns_ connect $udp_(3) $null_(3)
$ns_ at 11.441538646557152 "$cbr_(3) start"
#
# 4 connecting to 5 at time 39.924021046573301
#
set udp_(4) [new Agent/UDP]
$ns_ attach-agent $node_(4) $udp_(4)
set null_(4) [new Agent/Null]
$ns_ attach-agent $node_(5) $null_(4)
set cbr_(4) [new Application/Traffic/CBR]
$cbr_(4) set packetSize_ 512
$cbr_(4) set interval_ 0.25
$cbr_(4) set random_ 1
$cbr_(4) set maxpkts_ 10000
$cbr_(4) attach-agent $udp_(4)
$ns_ connect $udp_(4) $null_(4)
$ns_ at 39.924021046573301 "$cbr_(4) start"
#
# 4 connecting to 6 at time 170.14673779259749
#
set udp_(5) [new Agent/UDP]
$ns_ attach-agent $node_(4) $udp_(5)
set null_(5) [new Agent/Null]
$ns_ attach-agent $node_(6) $null_(5)
set cbr_(5) [new Application/Traffic/CBR]
$cbr_(5) set packetSize_ 512
$cbr_(5) set interval_ 0.25
$cbr_(5) set random_ 1
$cbr_(5) set maxpkts_ 10000
$cbr_(5) attach-agent $udp_(5)
$ns_ connect $udp_(5) $null_(5)
$ns_ at 170.14673779259749 "$cbr_(5) start"
#
# 6 connecting to 7 at time 123.23504031786464
#
set udp_(6) [new Agent/UDP]
$ns_ attach-agent $node_(6) $udp_(6)
set null_(6) [new Agent/Null]
$ns_ attach-agent $node_(7) $null_(6)
set cbr_(6) [new Application/Traffic/CBR]
$cbr_(6) set packetSize_ 512
$cbr_(6) set interval_ 0.25
$cbr_(6) set random_ 1
$cbr_(6) set maxpkts_ 10000
$cbr_(6) attach-agent $udp_(6)
$ns_ connect $udp_(6) $null_(6)
$ns_ at 123.23504031786464 "$cbr_(6) start"
#
# 8 connecting to 9 at time 136.00722813792862
#
set udp_(7) [new Agent/UDP]
$ns_ attach-agent $node_(8) $udp_(7)
set null_(7) [new Agent/Null]
$ns_ attach-agent $node_(9) $null_(7)
set cbr_(7) [new Application/Traffic/CBR]
$cbr_(7) set packetSize_ 512
$cbr_(7) set interval_ 0.25
$cbr_(7) set random_ 1
$cbr_(7) set maxpkts_ 10000
$cbr_(7) attach-agent $udp_(7)
$ns_ connect $udp_(7) $null_(7)
$ns_ at 136.00722813792862 "$cbr_(7) start"
#
# 8 connecting to 10 at time 140.12950276961993
#
set udp_(8) [new Agent/UDP]
$ns_ attach-agent $node_(8) $udp_(8)
set null_(8) [new Agent/Null]
$ns_ attach-agent $node_(10) $null_(8)
set cbr_(8) [new Application/Traffic/CBR]
$cbr_(8) set packetSize_ 512
$cbr_(8) set interval_ 0.25
$cbr_(8) set random_ 1
$cbr_(8) set maxpkts_ 10000
$cbr_(8) attach-agent $udp_(8)
$ns_ connect $udp_(8) $null_(8)
$ns_ at 140.12950276961993 "$cbr_(8) start"
#
# 9 connecting to 10 at time 91.119901179857521
#
set udp_(9) [new Agent/UDP]
$ns_ attach-agent $node_(9) $udp_(9)
set null_(9) [new Agent/Null]
$ns_ attach-agent $node_(10) $null_(9)
set cbr_(9) [new Application/Traffic/CBR]
$cbr_(9) set packetSize_ 512
$cbr_(9) set interval_ 0.25
$cbr_(9) set random_ 1
$cbr_(9) set maxpkts_ 10000
$cbr_(9) attach-agent $udp_(9)
$ns_ connect $udp_(9) $null_(9)
$ns_ at 91.119901179857521 "$cbr_(9) start"
#
#Total sources/connections: 6/10
#
