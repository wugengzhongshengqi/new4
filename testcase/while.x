
# tac list

0x605405ac7220	label main
0x605405ac7260	begin
0x605405ac67f0	var i
0x605405ac68a0	var j
0x605405ac69c0	i = 0
0x605405ac6a20	input j
0x605405ac7020	label L1
0x605405ac6b70	var t0
0x605405ac6bb0	t0 = (i < j)
0x605405ac7060	ifz t0 goto L2
0x605405ac6c10	output i
0x605405ac6df0	var t1
0x605405ac6e30	t1 = i + 1
0x605405ac6e70	i = t1
0x605405ac70a0	goto L1
0x605405ac70e0	label L2
0x605405ac7170	output L3
0x605405ac72a0	end
