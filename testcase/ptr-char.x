
# tac list

0x6218cf3f78a0	label main
0x6218cf3f78e0	begin
0x6218cf3f67f0	var a
0x6218cf3f68a0	var pa
0x6218cf3f6950	var b
0x6218cf3f6a00	var c
0x6218cf3f6ab0	var d
0x6218cf3f6b60	var ptr
0x6218cf3f6bc0	input d
0x6218cf3f6cc0	c = 99
0x6218cf3f6dc0	b = 98
0x6218cf3f6e20	input a
0x6218cf3f70a0	ifz 0 goto L2
0x6218cf3f6f90	output L1
0x6218cf3f7060	label L2
0x6218cf3f7100	output a
0x6218cf3f7160	output b
0x6218cf3f71c0	output c
0x6218cf3f7220	output d
0x6218cf3f7280	output L1
0x6218cf3f7370	var t0
0x6218cf3f73b0	t0 = &a
0x6218cf3f7420	pa = t0
0x6218cf3f7520	*pa = 65
0x6218cf3f7580	output a
0x6218cf3f7630	ptr = pa
0x6218cf3f7730	*ptr = 66
0x6218cf3f7790	output a
0x6218cf3f77f0	output L1
0x6218cf3f7920	end
