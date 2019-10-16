## \file ring.tcl

set data [gets stdin]
scan $data "%d %d" N k

set ns  [new Simulator]

$ns rtproto DV

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam
    exit 0
}

set colors(0) Blue
set colors(1) dodgerblue
set colors(2) violet
set colors(3) darkviolet
set colors(4) Red
set colors(5) pink
set colors(6) Yellow
set colors(7) Orange
set colors(8) green
set colors(9) darkgreen
set colors(10) magenta
set colors(11) brown

for {set i 0} {$i < $N} {incr i} {
	set n($i) [$ns node]
}

for {set i 0}  {$i < $N} {incr i} {
    $ns color $i $colors([expr {int(rand()*10)}])
}

for {set i 0} {$i < $N} {incr i} {
	$ns duplex-link $n($i) $n([expr ($i + 1) % $N]) 512Kb 5ms DropTail
}

for {set i 0} {$i < $k} {incr i} {
	set input [gets stdin]
	scan $input "%d %d" u v
	set tcp [new Agent/TCP]
	$ns attach-agent $n($u) $tcp
	$tcp set class_ $i
	set sink [new Agent/TCPSink]
	$ns attach-agent $n($v) $sink
	$ns connect $tcp $sink
	set ftp0 [new Application/FTP]
	$ftp0 attach-agent $tcp
	$ns at 0.1 "$ftp0 start"
	$ns at 1.5 "$ftp0 stop"
}

$ns at 2.0 "finish"
$ns run