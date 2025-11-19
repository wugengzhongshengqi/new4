
# tac list

0x5f02bb1439e0	label main
0x5f02bb143a20	begin
0x5f02bb1417f0	var i
0x5f02bb1418a0	var j
0x5f02bb141a10	var arr1[10]
0x5f02bb141a70	input i
0x5f02bb141b90	j = 0
0x5f02bb142980	label L1
0x5f02bb141d50	var t0
0x5f02bb141d90	t0 = (j < 10)
0x5f02bb1429c0	ifz t0 goto L3
0x5f02bb1421a0	var t1
0x5f02bb1421e0	t1 = j * 1
0x5f02bb142300	var t2
0x5f02bb142340	t2 = t1 * 4
0x5f02bb1423f0	var t3
0x5f02bb142430	t3 = &arr1
0x5f02bb1424e0	var t4
0x5f02bb142520	t4 = t3 + t2
0x5f02bb142560	*t4 = i
0x5f02bb1426d0	var t5
0x5f02bb142710	t5 = i + 1
0x5f02bb142750	i = t5
0x5f02bb1428c0	var t6
0x5f02bb142900	t6 = j + 1
0x5f02bb142940	j = t6
0x5f02bb142a00	goto L1
0x5f02bb142a40	label L3
0x5f02bb142c00	ifz 0 goto L5
0x5f02bb142af0	output L4
0x5f02bb142bc0	label L5
0x5f02bb143830	label L6
0x5f02bb142d20	var t7
0x5f02bb142d60	t7 = (j > 0)
0x5f02bb143870	ifz t7 goto L8
0x5f02bb143100	var t8
0x5f02bb143140	t8 = j - 1
0x5f02bb143180	j = t8
0x5f02bb1432c0	var t9
0x5f02bb143300	t9 = j * 1
0x5f02bb1433b0	var t10
0x5f02bb1433f0	t10 = t9 * 4
0x5f02bb1434a0	var t11
0x5f02bb1434e0	t11 = &arr1
0x5f02bb143590	var t12
0x5f02bb1435d0	t12 = t11 + t10
0x5f02bb143680	var t13
0x5f02bb1436c0	t13 = *t12
0x5f02bb143730	i = t13
0x5f02bb143790	output i
0x5f02bb1437f0	output L4
0x5f02bb1438b0	goto L6
0x5f02bb1438f0	label L8
0x5f02bb143930	output L4
0x5f02bb143a60	end
