
# tac list

0x5b1aacdcbcf0	label main
0x5b1aacdcbd30	begin
0x5b1aacdca7f0	var i
0x5b1aacdca8a0	var j
0x5b1aacdca900	input i
0x5b1aacdcb580	var t3
0x5b1aacdcb5c0	t3 = (i == 1)
0x5b1aacdcb690	ifz t3 goto L3
0x5b1aacdcac20	var t0
0x5b1aacdcac60	t0 = i + 1
0x5b1aacdcaca0	j = t0
0x5b1aacdcad00	output j
0x5b1aacdcad40	goto L1
0x5b1aacdcb6d0	goto L1
0x5b1aacdcb710	label L3
0x5b1aacdcb7c0	var t4
0x5b1aacdcb800	t4 = (i == 2)
0x5b1aacdcb8d0	ifz t4 goto L4
0x5b1aacdcaf60	var t1
0x5b1aacdcafa0	t1 = i + 2
0x5b1aacdcafe0	j = t1
0x5b1aacdcb040	output j
0x5b1aacdcb080	goto L1
0x5b1aacdcb910	goto L1
0x5b1aacdcb950	label L4
0x5b1aacdcba00	var t5
0x5b1aacdcba40	t5 = (i == 3)
0x5b1aacdcbb10	ifz t5 goto L5
0x5b1aacdcb2a0	var t2
0x5b1aacdcb2e0	t2 = i + 3
0x5b1aacdcb320	j = t2
0x5b1aacdcb380	output j
0x5b1aacdcb3c0	goto L1
0x5b1aacdcbb50	goto L1
0x5b1aacdcbb90	label L5
0x5b1aacdcb490	output L2
0x5b1aacdcb4d0	goto L1
0x5b1aacdcbbd0	label L1
0x5b1aacdcbc60	output L6
0x5b1aacdcbd70	end
