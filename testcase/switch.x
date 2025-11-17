
# tac list

0x5d1a730d0cf0	label main
0x5d1a730d0d30	begin
0x5d1a730cf7f0	var i
0x5d1a730cf8a0	var j
0x5d1a730cf900	input i
0x5d1a730d0560	var t3
0x5d1a730d05a0	t3 = (i == 1)
0x5d1a730d0670	ifz t3 goto L3
0x5d1a730cfc00	var t0
0x5d1a730cfc40	t0 = i + 1
0x5d1a730cfc80	j = t0
0x5d1a730cfce0	output j
0x5d1a730cfd20	goto L1
0x5d1a730d06b0	goto L1
0x5d1a730d06f0	label L3
0x5d1a730d07a0	var t4
0x5d1a730d07e0	t4 = (i == 2)
0x5d1a730d08b0	ifz t4 goto L4
0x5d1a730cff40	var t1
0x5d1a730cff80	t1 = i + 2
0x5d1a730cffc0	j = t1
0x5d1a730d0020	output j
0x5d1a730d0060	goto L1
0x5d1a730d08f0	goto L1
0x5d1a730d0930	label L4
0x5d1a730d09e0	var t5
0x5d1a730d0a20	t5 = (i == 3)
0x5d1a730d0af0	ifz t5 goto L5
0x5d1a730d0280	var t2
0x5d1a730d02c0	t2 = i + 3
0x5d1a730d0300	j = t2
0x5d1a730d0360	output j
0x5d1a730d03a0	goto L1
0x5d1a730d0b30	goto L1
0x5d1a730d0b70	label L5
0x5d1a730d0470	output L2
0x5d1a730d04b0	goto L1
0x5d1a730d0bb0	label L1
0x5d1a730d0c40	output L6
0x5d1a730d0d70	end
