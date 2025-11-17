
# tac list

0x590ecbdd2290	label main
0x590ecbdd22d0	begin
0x590ecbdd07f0	var i
0x590ecbdd08a0	var j
0x590ecbdd0900	input j
0x590ecbdd0a20	i = 0
0x590ecbdd14e0	label L1
0x590ecbdd0b70	var t0
0x590ecbdd0bb0	t0 = (i < j)
0x590ecbdd1520	ifz t0 goto L3
0x590ecbdd1200	var t2
0x590ecbdd1240	t2 = (i > 10)
0x590ecbdd1440	ifz t2 goto L5
0x590ecbdd12f0	output L4
0x590ecbdd1330	goto L3
0x590ecbdd1400	label L5
0x590ecbdd14a0	output i
0x590ecbdd1560	label L2
0x590ecbdd0d90	var t1
0x590ecbdd0dd0	t1 = i + 1
0x590ecbdd0e10	i = t1
0x590ecbdd15a0	goto L1
0x590ecbdd15e0	label L3
0x590ecbdd1670	output L6
0x590ecbdd16f0	i = 0
0x590ecbdd20a0	label L7
0x590ecbdd1810	var t3
0x590ecbdd1850	t3 = (i < j)
0x590ecbdd20e0	ifz t3 goto L9
0x590ecbdd1dc0	var t5
0x590ecbdd1e00	t5 = (i == 10)
0x590ecbdd2000	ifz t5 goto L11
0x590ecbdd1eb0	output L10
0x590ecbdd1ef0	goto L8
0x590ecbdd1fc0	label L11
0x590ecbdd2060	output i
0x590ecbdd2120	label L8
0x590ecbdd19c0	var t4
0x590ecbdd1a00	t4 = i + 1
0x590ecbdd1a40	i = t4
0x590ecbdd2160	goto L7
0x590ecbdd21a0	label L9
0x590ecbdd21e0	output L6
0x590ecbdd2310	end
