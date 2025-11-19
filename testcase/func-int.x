
# tac list

0x5a025619a780	var i
0x5a025619b2d0	label main
0x5a025619b310	begin
0x5a025619a8a0	var a
0x5a025619a950	var b
0x5a025619aa00	var c
0x5a025619aa60	input a
0x5a025619aac0	input b
0x5a025619ac50	var t0
0x5a025619ac90	actual b
0x5a025619acd0	actual a
0x5a025619ad30	t0 = call max
0x5a025619ada0	c = t0
0x5a025619ae00	output c
0x5a025619aeb0	output L1
0x5a025619b090	var t1
0x5a025619b0d0	t1 = i + 1
0x5a025619b110	i = t1
0x5a025619b170	output i
0x5a025619b220	output L2
0x5a025619b350	end
0x5a025619bb70	label max
0x5a025619bbb0	begin
0x5a025619b470	formal x
0x5a025619b520	formal y
0x5a025619b670	var t2
0x5a025619b6b0	t2 = (x > y)
0x5a025619b9f0	ifz t2 goto L3
0x5a025619b760	i = x
0x5a025619ba30	goto L4
0x5a025619b8e0	label L3
0x5a025619b810	i = y
0x5a025619b9b0	label L4
0x5a025619bac0	return i
0x5a025619bbf0	end
