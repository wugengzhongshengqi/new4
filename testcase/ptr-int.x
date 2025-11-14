
# tac list

0x61a99b9a5b70	label main
0x61a99b9a5bb0	begin
0x61a99b9a47f0	var a
0x61a99b9a48a0	var pa
0x61a99b9a4950	var b
0x61a99b9a4a00	var c
0x61a99b9a4ab0	var d
0x61a99b9a4b60	var ptr
0x61a99b9a4bc0	input a
0x61a99b9a4da0	var t0
0x61a99b9a4de0	t0 = a + 10
0x61a99b9a4e20	b = t0
0x61a99b9a5000	var t1
0x61a99b9a5040	t1 = b - 20
0x61a99b9a5080	c = t1
0x61a99b9a5260	var t2
0x61a99b9a52a0	t2 = c * 30
0x61a99b9a52e0	d = t2
0x61a99b9a5340	output a
0x61a99b9a53a0	output b
0x61a99b9a5400	output c
0x61a99b9a5460	output d
0x61a99b9a5510	output L1
0x61a99b9a5600	var t3
0x61a99b9a5640	t3 = &a
0x61a99b9a56b0	pa = t3
0x61a99b9a57d0	*pa = 111
0x61a99b9a5830	output a
0x61a99b9a58e0	ptr = pa
0x61a99b9a5a00	*ptr = 222
0x61a99b9a5a60	output a
0x61a99b9a5ac0	output L1
0x61a99b9a5bf0	end
