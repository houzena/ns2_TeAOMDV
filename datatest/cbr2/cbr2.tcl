#
# nodes: 30, max conn: 10, send rate: 0.25, seed: 2
#
#
# 4 connecting to 5 at time 107.69501429409489
#
set udp_(0) [new Agent/UDP]
$ns_ attach-agent $node_(4) $udp_(0)
set null_(0) [new Agent/Null]
$ns_ attach-agent $node_(5) $null_(0)
set cbr_(0) [new Application/Traffic/CBR]
$cbr_(0) set packetSize_ 512
$cbr_(0) set interval_ 0.25
$cbr_(0) set random_ 1
$cbr_(0) set maxpkts_ 10000
$cbr_(0) attach-agent $udp_(0)
$ns_ connect $udp_(0) $null_(0)
$ns_ at 107.69501429409489 "$cbr_(0) start"
#
# 4 connecting to 6 at time 112.66623783515126
#
set udp_(1) [new Agent/UDP]
$ns_ attach-agent $node_(4) $udp_(1)
set null_(1) [new Agent/Null]
$ns_ attach-agent $node_(6) $null_(1)
set cbr_(1) [new Application/Traffic/CBR]
$cbr_(1) set packetSize_ 512
$cbr_(1) set interval_ 0.25
$cbr_(1) set random_ 1
$cbr_(1) set maxpkts_ 10000
$cbr_(1) attach-agent $udp_(1)
$ns_ connect $udp_(1) $null_(1)
$ns_ at 112.66623783515126 "$cbr_(1) start"
#
# 5 connecting to 6 at time 84.456630639944521
#
set udp_(2) [new Agent/UDP]
$ns_ attach-agent $node_(5) $udp_(2)
set null_(2) [new Agent/Null]
$ns_ attach-agent $node_(6) $null_(2)
set cbr_(2) [new Application/Traffic/CBR]
$cbr_(2) set packetSize_ 512
$cbr_(2) set interval_ 0.25
$cbr_(2) set random_ 1
$cbr_(2) set maxpkts_ 10000
$cbr_(2) attach-agent $udp_(2)
$ns_ connect $udp_(2) $null_(2)
$ns_ at 84.456630639944521 "$cbr_(2) start"
#
# 7 connecting to 8 at time 121.07647335206924
#
set udp_(3) [new Agent/UDP]
$ns_ attach-agent $node_(7) $udp_(3)
set null_(3) [new Agent/Null]
$ns_ attach-agent $node_(8) $null_(3)
set cbr_(3) [new Application/Traffic/CBR]
$cbr_(3) set packetSize_ 512
$cbr_(3) set interval_ 0.25
$cbr_(3) set random_ 1
$cbr_(3) set maxpkts_ 10000
$cbr_(3) attach-agent $udp_(3)
$ns_ connect $udp_(3) $null_(3)
$ns_ at 121.07647335206924 "$cbr_(3) start"
#
# 12 connecting to 13 at time 152.51642512740401
#
set udp_(4) [new Agent/UDP]
$ns_ attach-agent $node_(12) $udp_(4)
set null_(4) [new Agent/Null]
$ns_ attach-agent $node_(13) $null_(4)
set cbr_(4) [new Application/Traffic/CBR]
$cbr_(4) set packetSize_ 512
$cbr_(4) set interval_ 0.25
$cbr_(4) set random_ 1
$cbr_(4) set maxpkts_ 10000
$cbr_(4) attach-agent $udp_(4)
$ns_ connect $udp_(4) $null_(4)
$ns_ at 152.51642512740401 "$cbr_(4) start"
#
# 15 connecting to 16 at time 125.54676921365167
#
set udp_(5) [new Agent/UDP]
$ns_ attach-agent $node_(15) $udp_(5)
set null_(5) [new Agent/Null]
$ns_ attach-agent $node_(16) $null_(5)
set cbr_(5) [new Application/Traffic/CBR]
$cbr_(5) set packetSize_ 512
$cbr_(5) set interval_ 0.25
$cbr_(5) set random_ 1
$cbr_(5) set maxpkts_ 10000
$cbr_(5) attach-agent $udp_(5)
$ns_ connect $udp_(5) $null_(5)
$ns_ at 125.54676921365167 "$cbr_(5) start"
#
# 16 connecting to 17 at time 147.12684344832172
#
set udp_(6) [new Agent/UDP]
$ns_ attach-agent $node_(16) $udp_(6)
set null_(6) [new Agent/Null]
$ns_ attach-agent $node_(17) $null_(6)
set cbr_(6) [new Application/Traffic/CBR]
$cbr_(6) set packetSize_ 512
$cbr_(6) set interval_ 0.25
$cbr_(6) set random_ 1
$cbr_(6) set maxpkts_ 10000
$cbr_(6) attach-agent $udp_(6)
$ns_ connect $udp_(6) $null_(6)
$ns_ at 147.12684344832172 "$cbr_(6) start"
#
# 18 connecting to 19 at time 69.230459699980202
#
set udp_(7) [new Agent/UDP]
$ns_ attach-agent $node_(18) $udp_(7)
set null_(7) [new Agent/Null]
$ns_ attach-agent $node_(19) $null_(7)
set cbr_(7) [new Application/Traffic/CBR]
$cbr_(7) set packetSize_ 512
$cbr_(7) set interval_ 0.25
$cbr_(7) set random_ 1
$cbr_(7) set maxpkts_ 10000
$cbr_(7) attach-agent $udp_(7)
$ns_ connect $udp_(7) $null_(7)
$ns_ at 69.230459699980202 "$cbr_(7) start"
#
# 18 connecting to 20 at time 130.34422114973151
#
set udp_(8) [new Agent/UDP]
$ns_ attach-agent $node_(18) $udp_(8)
set null_(8) [new Agent/Null]
$ns_ attach-agent $node_(20) $null_(8)
set cbr_(8) [new Application/Traffic/CBR]
$cbr_(8) set packetSize_ 512
$cbr_(8) set interval_ 0.25
$cbr_(8) set random_ 1
$cbr_(8) set maxpkts_ 10000
$cbr_(8) attach-agent $udp_(8)
$ns_ connect $udp_(8) $null_(8)
$ns_ at 130.34422114973151 "$cbr_(8) start"
#
# 19 connecting to 20 at time 78.176456409588667
#
set udp_(9) [new Agent/UDP]
$ns_ attach-agent $node_(19) $udp_(9)
set null_(9) [new Agent/Null]
$ns_ attach-agent $node_(20) $null_(9)
set cbr_(9) [new Application/Traffic/CBR]
$cbr_(9) set packetSize_ 512
$cbr_(9) set interval_ 0.25
$cbr_(9) set random_ 1
$cbr_(9) set maxpkts_ 10000
$cbr_(9) attach-agent $udp_(9)
$ns_ connect $udp_(9) $null_(9)
$ns_ at 78.176456409588667 "$cbr_(9) start"
#
#Total sources/connections: 8/10
#
