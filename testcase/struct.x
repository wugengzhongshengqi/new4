
# tac list

0x60eeb96c4e50	label main
0x60eeb96c4e90	begin
0x60eeb96c29b0	var i
0x60eeb96c2a60	var j
0x60eeb96c2b10	var k
0x60eeb96c2c00	var zs[
0x60eeb96c2c60	input i
0x60eeb96c2cc0	input j
0x60eeb96c2d20	input k
0x60eeb96c2f00	var t1
0x60eeb96c2f40	t1 = &zs
0x60eeb96c2f80	*t1 = i
0x60eeb96c3160	var t2
0x60eeb96c31a0	t2 = &zs
0x60eeb96c32c0	var t3
0x60eeb96c3300	t3 = t2 + 4
0x60eeb96c3340	*t3 = j
0x60eeb96c3520	var t4
0x60eeb96c3560	t4 = &zs
0x60eeb96c3680	var t5
0x60eeb96c36c0	t5 = t4 + 8
0x60eeb96c3700	*t5 = k
0x60eeb96c39a0	ifz 0 goto L2
0x60eeb96c3870	output L1
0x60eeb96c3960	label L2
0x60eeb96c3b30	var t6
0x60eeb96c3b70	t6 = &zs
0x60eeb96c3c20	var t7
0x60eeb96c3c60	t7 = t6 + 8
0x60eeb96c3d10	var t8
0x60eeb96c3d50	t8 = *t7
0x60eeb96c3ef0	var t9
0x60eeb96c3f30	t9 = t8 + 100
0x60eeb96c3f70	i = t9
0x60eeb96c4120	var t10
0x60eeb96c4160	t10 = &zs
0x60eeb96c4210	var t11
0x60eeb96c4250	t11 = t10 + 4
0x60eeb96c4300	var t12
0x60eeb96c4340	t12 = *t11
0x60eeb96c44e0	var t13
0x60eeb96c4520	t13 = t12 + 200
0x60eeb96c4560	j = t13
0x60eeb96c4710	var t14
0x60eeb96c4750	t14 = &zs
0x60eeb96c4800	var t15
0x60eeb96c4840	t15 = *t14
0x60eeb96c49e0	var t16
0x60eeb96c4a20	t16 = t15 + 300
0x60eeb96c4a60	k = t16
0x60eeb96c4c20	ifz 0 goto L3
0x60eeb96c4b10	output L1
0x60eeb96c4be0	label L3
0x60eeb96c4c80	output i
0x60eeb96c4ce0	output j
0x60eeb96c4d40	output k
0x60eeb96c4da0	output L1
0x60eeb96c4ed0	end
