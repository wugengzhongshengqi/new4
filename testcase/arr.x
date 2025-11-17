
# tac list

0x5f2d5d1a61d0	label main
0x5f2d5d1a6210	begin
0x5f2d5d1a27f0	var i
0x5f2d5d1a28a0	var j
0x5f2d5d1a2a10	var arr1[10]
0x5f2d5d1a2ba0	var arr2[10][20]
0x5f2d5d1a2d50	var arr3[10][20][30]
0x5f2d5d1a2db0	input i
0x5f2d5d1a3000	var t0
0x5f2d5d1a3040	t0 = 6 * 1
0x5f2d5d1a3160	var t1
0x5f2d5d1a31a0	t1 = t0 * 4
0x5f2d5d1a3250	var t2
0x5f2d5d1a3290	t2 = &arr1
0x5f2d5d1a3340	var t3
0x5f2d5d1a3380	t3 = t2 + t1
0x5f2d5d1a33c0	*t3 = i
0x5f2d5d1a3c30	var t10
0x5f2d5d1a3c70	t10 = 6 * 20
0x5f2d5d1a3d20	var t11
0x5f2d5d1a3d60	t11 = 6 * 1
0x5f2d5d1a3e10	var t12
0x5f2d5d1a3e50	t12 = t10 + t11
0x5f2d5d1a3f00	var t13
0x5f2d5d1a3f40	t13 = t12 * 4
0x5f2d5d1a3ff0	var t14
0x5f2d5d1a4030	t14 = &arr2
0x5f2d5d1a40e0	var t15
0x5f2d5d1a4120	t15 = t14 + t13
0x5f2d5d1a35a0	var t4
0x5f2d5d1a35e0	t4 = 6 * 1
0x5f2d5d1a3690	var t5
0x5f2d5d1a36d0	t5 = t4 * 4
0x5f2d5d1a3780	var t6
0x5f2d5d1a37c0	t6 = &arr1
0x5f2d5d1a3870	var t7
0x5f2d5d1a38b0	t7 = t6 + t5
0x5f2d5d1a3960	var t8
0x5f2d5d1a39a0	t8 = *t7
0x5f2d5d1a3ad0	var t9
0x5f2d5d1a3b10	t9 = t8 + 6
0x5f2d5d1a4160	*t15 = t9
0x5f2d5d1a4c50	var t24
0x5f2d5d1a4c90	t24 = 6 * 600
0x5f2d5d1a4db0	var t25
0x5f2d5d1a4df0	t25 = 6 * 30
0x5f2d5d1a4ea0	var t26
0x5f2d5d1a4ee0	t26 = t24 + t25
0x5f2d5d1a4f90	var t27
0x5f2d5d1a4fd0	t27 = 6 * 1
0x5f2d5d1a5080	var t28
0x5f2d5d1a50c0	t28 = t26 + t27
0x5f2d5d1a5170	var t29
0x5f2d5d1a51b0	t29 = t28 * 4
0x5f2d5d1a5260	var t30
0x5f2d5d1a52a0	t30 = &arr3
0x5f2d5d1a5350	var t31
0x5f2d5d1a5390	t31 = t30 + t29
0x5f2d5d1a43e0	var t16
0x5f2d5d1a4420	t16 = 6 * 20
0x5f2d5d1a44d0	var t17
0x5f2d5d1a4510	t17 = 6 * 1
0x5f2d5d1a45c0	var t18
0x5f2d5d1a4600	t18 = t16 + t17
0x5f2d5d1a46b0	var t19
0x5f2d5d1a46f0	t19 = t18 * 4
0x5f2d5d1a47a0	var t20
0x5f2d5d1a47e0	t20 = &arr2
0x5f2d5d1a4890	var t21
0x5f2d5d1a48d0	t21 = t20 + t19
0x5f2d5d1a4980	var t22
0x5f2d5d1a49c0	t22 = *t21
0x5f2d5d1a4af0	var t23
0x5f2d5d1a4b30	t23 = t22 + 6
0x5f2d5d1a53d0	*t31 = t23
0x5f2d5d1a5670	ifz 0 goto L2
0x5f2d5d1a5540	output L1
0x5f2d5d1a5630	label L2
0x5f2d5d1a5830	var t32
0x5f2d5d1a5870	t32 = 6 * 600
0x5f2d5d1a5920	var t33
0x5f2d5d1a5960	t33 = 6 * 30
0x5f2d5d1a5a10	var t34
0x5f2d5d1a5a50	t34 = t32 + t33
0x5f2d5d1a5b00	var t35
0x5f2d5d1a5b40	t35 = 6 * 1
0x5f2d5d1a5bf0	var t36
0x5f2d5d1a5c30	t36 = t34 + t35
0x5f2d5d1a5ce0	var t37
0x5f2d5d1a5d20	t37 = t36 * 4
0x5f2d5d1a5dd0	var t38
0x5f2d5d1a5e10	t38 = &arr3
0x5f2d5d1a5ec0	var t39
0x5f2d5d1a5f00	t39 = t38 + t37
0x5f2d5d1a5fb0	var t40
0x5f2d5d1a5ff0	t40 = *t39
0x5f2d5d1a6060	j = t40
0x5f2d5d1a60c0	output j
0x5f2d5d1a6120	output L1
0x5f2d5d1a6250	end
