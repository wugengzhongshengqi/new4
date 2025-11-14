
# tac list

0x5bdd720768a0	label main
0x5bdd720768e0	begin
0x5bdd720757f0	var a
0x5bdd720758a0	var pa
0x5bdd72075950	var b
0x5bdd72075a00	var c
0x5bdd72075ab0	var d
0x5bdd72075b60	var ptr
0x5bdd72075bc0	input d
0x5bdd72075cc0	c = 99
0x5bdd72075dc0	b = 98
0x5bdd72075e20	input a
0x5bdd720760a0	ifz 0 goto L2
0x5bdd72075f90	output L1
0x5bdd72076060	label L2
0x5bdd72076100	output a
0x5bdd72076160	output b
0x5bdd720761c0	output c
0x5bdd72076220	output d
0x5bdd72076280	output L1
0x5bdd72076370	var t0
0x5bdd720763b0	t0 = &a
0x5bdd72076420	pa = t0
0x5bdd72076520	*pa = 65
0x5bdd72076580	output a
0x5bdd72076630	ptr = pa
0x5bdd72076730	*ptr = 66
0x5bdd72076790	output a
0x5bdd720767f0	output L1
0x5bdd72076920	end
