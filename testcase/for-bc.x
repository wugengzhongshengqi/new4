
# tac list

0x5e1f23cb3290	label main
0x5e1f23cb32d0	begin
0x5e1f23cb17f0	var i
0x5e1f23cb18a0	var j
0x5e1f23cb1900	input j
0x5e1f23cb1a20	i = 0
0x5e1f23cb24e0	label L1
0x5e1f23cb1b70	var t0
0x5e1f23cb1bb0	t0 = (i < j)
0x5e1f23cb2520	ifz t0 goto L3
0x5e1f23cb2200	var t2
0x5e1f23cb2240	t2 = (i > 10)
0x5e1f23cb2440	ifz t2 goto L5
0x5e1f23cb22f0	output L4
0x5e1f23cb2330	goto L3
0x5e1f23cb2400	label L5
0x5e1f23cb24a0	output i
0x5e1f23cb2560	label L2
0x5e1f23cb1d90	var t1
0x5e1f23cb1dd0	t1 = i + 1
0x5e1f23cb1e10	i = t1
0x5e1f23cb25a0	goto L1
0x5e1f23cb25e0	label L3
0x5e1f23cb2670	output L6
0x5e1f23cb26f0	i = 0
0x5e1f23cb30a0	label L7
0x5e1f23cb2810	var t3
0x5e1f23cb2850	t3 = (i < j)
0x5e1f23cb30e0	ifz t3 goto L9
0x5e1f23cb2dc0	var t5
0x5e1f23cb2e00	t5 = (i == 10)
0x5e1f23cb3000	ifz t5 goto L11
0x5e1f23cb2eb0	output L10
0x5e1f23cb2ef0	goto L8
0x5e1f23cb2fc0	label L11
0x5e1f23cb3060	output i
0x5e1f23cb3120	label L8
0x5e1f23cb29c0	var t4
0x5e1f23cb2a00	t4 = i + 1
0x5e1f23cb2a40	i = t4
0x5e1f23cb3160	goto L7
0x5e1f23cb31a0	label L9
0x5e1f23cb31e0	output L6
0x5e1f23cb3310	end
