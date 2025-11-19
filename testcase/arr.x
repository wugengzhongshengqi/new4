
# tac list

0x5d49b4df91d0	label main
0x5d49b4df9210	begin
0x5d49b4df57f0	var i
0x5d49b4df58a0	var j
0x5d49b4df5a10	var arr1[10]
0x5d49b4df5ba0	var arr2[10][20]
0x5d49b4df5d50	var arr3[10][20][30]
0x5d49b4df5db0	input i
0x5d49b4df6000	var t0
0x5d49b4df6040	t0 = 6 * 1
0x5d49b4df6160	var t1
0x5d49b4df61a0	t1 = t0 * 4
0x5d49b4df6250	var t2
0x5d49b4df6290	t2 = &arr1
0x5d49b4df6340	var t3
0x5d49b4df6380	t3 = t2 + t1
0x5d49b4df63c0	*t3 = i
0x5d49b4df6c30	var t10
0x5d49b4df6c70	t10 = 6 * 20
0x5d49b4df6d20	var t11
0x5d49b4df6d60	t11 = 6 * 1
0x5d49b4df6e10	var t12
0x5d49b4df6e50	t12 = t10 + t11
0x5d49b4df6f00	var t13
0x5d49b4df6f40	t13 = t12 * 4
0x5d49b4df6ff0	var t14
0x5d49b4df7030	t14 = &arr2
0x5d49b4df70e0	var t15
0x5d49b4df7120	t15 = t14 + t13
0x5d49b4df65a0	var t4
0x5d49b4df65e0	t4 = 6 * 1
0x5d49b4df6690	var t5
0x5d49b4df66d0	t5 = t4 * 4
0x5d49b4df6780	var t6
0x5d49b4df67c0	t6 = &arr1
0x5d49b4df6870	var t7
0x5d49b4df68b0	t7 = t6 + t5
0x5d49b4df6960	var t8
0x5d49b4df69a0	t8 = *t7
0x5d49b4df6ad0	var t9
0x5d49b4df6b10	t9 = t8 + 6
0x5d49b4df7160	*t15 = t9
0x5d49b4df7c50	var t24
0x5d49b4df7c90	t24 = 6 * 600
0x5d49b4df7db0	var t25
0x5d49b4df7df0	t25 = 6 * 30
0x5d49b4df7ea0	var t26
0x5d49b4df7ee0	t26 = t24 + t25
0x5d49b4df7f90	var t27
0x5d49b4df7fd0	t27 = 6 * 1
0x5d49b4df8080	var t28
0x5d49b4df80c0	t28 = t26 + t27
0x5d49b4df8170	var t29
0x5d49b4df81b0	t29 = t28 * 4
0x5d49b4df8260	var t30
0x5d49b4df82a0	t30 = &arr3
0x5d49b4df8350	var t31
0x5d49b4df8390	t31 = t30 + t29
0x5d49b4df73e0	var t16
0x5d49b4df7420	t16 = 6 * 20
0x5d49b4df74d0	var t17
0x5d49b4df7510	t17 = 6 * 1
0x5d49b4df75c0	var t18
0x5d49b4df7600	t18 = t16 + t17
0x5d49b4df76b0	var t19
0x5d49b4df76f0	t19 = t18 * 4
0x5d49b4df77a0	var t20
0x5d49b4df77e0	t20 = &arr2
0x5d49b4df7890	var t21
0x5d49b4df78d0	t21 = t20 + t19
0x5d49b4df7980	var t22
0x5d49b4df79c0	t22 = *t21
0x5d49b4df7af0	var t23
0x5d49b4df7b30	t23 = t22 + 6
0x5d49b4df83d0	*t31 = t23
0x5d49b4df8670	ifz 0 goto L2
0x5d49b4df8540	output L1
0x5d49b4df8630	label L2
0x5d49b4df8830	var t32
0x5d49b4df8870	t32 = 6 * 600
0x5d49b4df8920	var t33
0x5d49b4df8960	t33 = 6 * 30
0x5d49b4df8a10	var t34
0x5d49b4df8a50	t34 = t32 + t33
0x5d49b4df8b00	var t35
0x5d49b4df8b40	t35 = 6 * 1
0x5d49b4df8bf0	var t36
0x5d49b4df8c30	t36 = t34 + t35
0x5d49b4df8ce0	var t37
0x5d49b4df8d20	t37 = t36 * 4
0x5d49b4df8dd0	var t38
0x5d49b4df8e10	t38 = &arr3
0x5d49b4df8ec0	var t39
0x5d49b4df8f00	t39 = t38 + t37
0x5d49b4df8fb0	var t40
0x5d49b4df8ff0	t40 = *t39
0x5d49b4df9060	j = t40
0x5d49b4df90c0	output j
0x5d49b4df9120	output L1
0x5d49b4df9250	end
