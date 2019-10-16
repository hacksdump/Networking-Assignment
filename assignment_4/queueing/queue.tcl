## \file queue.tcl

set ns  [new Simulator]
$ns color 1 Blue

set namFile [open namFile.nam w]
$ns namtrace-all $namFile
set traceFile [open traceFile.tr w]
set trace-al $traceFile
proc finish {} {
    global ns namFile traceFile
    $ns flush-trace
    close $namFile
    close $traceFile
    exec gawk -f packet_drops.awk namFile.nam &
    exec nam namFile.nam &
    exit 0
}
set n(0) [$ns node]
set n(1) [$ns node]
set n(2) [$ns node]
$ns duplex-link $n(0) $n(1) 10Mb 1ms DropTail
$ns duplex-link $n(1) $n(2) 1Mb 1ms DropTail
$ns queue-limit $n(0) $n(1) 40
$ns queue-limit $n(1) $n(2) 7
set tcp [new Agent/TCP]
$ns attach-agent $n(0) $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n(2) $sink
$ns connect $tcp $sink
$tcp set fid_ 1
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP
$ns at 0.1 "$ftp start"
$ns at 1.9 "$ftp stop"

$ns at 2.0 "finish"

$ns run