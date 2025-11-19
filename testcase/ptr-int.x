
# tac list

0x585dfbaa6b70	label main
0x585dfbaa6bb0	begin
0x585dfbaa57f0	var a
0x585dfbaa58a0	var pa
0x585dfbaa5950	var b
0x585dfbaa5a00	var c
0x585dfbaa5ab0	var d
0x585dfbaa5b60	var ptr
0x585dfbaa5bc0	input a
0x585dfbaa5da0	var t0
0x585dfbaa5de0	t0 = a + 10
0x585dfbaa5e20	b = t0
0x585dfbaa6000	var t1
0x585dfbaa6040	t1 = b - 20
0x585dfbaa6080	c = t1
0x585dfbaa6260	var t2
0x585dfbaa62a0	t2 = c * 30
0x585dfbaa62e0	d = t2
0x585dfbaa6340	output a
0x585dfbaa63a0	output b
0x585dfbaa6400	output c
0x585dfbaa6460	output d
0x585dfbaa6510	output L1
0x585dfbaa6600	var t3
0x585dfbaa6640	t3 = &a
0x585dfbaa66b0	pa = t3
0x585dfbaa67d0	*pa = 111
0x585dfbaa6830	output a
0x585dfbaa68e0	ptr = pa
0x585dfbaa6a00	*ptr = 222
0x585dfbaa6a60	output a
0x585dfbaa6ac0	output L1
0x585dfbaa6bf0	end
