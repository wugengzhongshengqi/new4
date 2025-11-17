
# tac list

0x61317aa4d520	label main
0x61317aa4d560	begin
0x61317aa4c7f0	var i
0x61317aa4c910	i = 0
0x61317aa4d390	label L1
0x61317aa4cad0	var t0
0x61317aa4cb10	t0 = (i < 10)
0x61317aa4d3d0	ifz t0 goto L3
0x61317aa4d000	output i
0x61317aa4d1c0	var t2
0x61317aa4d200	t2 = (i == 5)
0x61317aa4d350	ifz t2 goto L4
0x61317aa4d240	goto L3
0x61317aa4d310	label L4
0x61317aa4d410	label L2
0x61317aa4ccf0	var t1
0x61317aa4cd30	t1 = i + 1
0x61317aa4cd70	i = t1
0x61317aa4d450	goto L1
0x61317aa4d490	label L3
0x61317aa4d5a0	end
