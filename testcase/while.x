
# tac list

0x59ac518be1f0	label main
0x59ac518be230	begin
0x59ac518bd7f0	var i
0x59ac518bd8a0	var j
0x59ac518bd9c0	i = 0
0x59ac518bda20	input j
0x59ac518bdf40	label L1
0x59ac518bdb70	var t0
0x59ac518bdbb0	t0 = (i < j)
0x59ac518be090	ifz t0 goto L2
0x59ac518bdc10	output i
0x59ac518bddf0	var t1
0x59ac518bde30	t1 = i + 1
0x59ac518bde70	i = t1
0x59ac518bdf80	goto L1
0x59ac518be050	label L2
0x59ac518be140	output L3
0x59ac518be270	end
