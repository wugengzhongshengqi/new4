	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var i

	# var j

	# var arr1[10]

	# var arr2[10][20]

	# var arr3[10][20][30]

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15

	# var t0

	# t0 = 6 * 1
	LOD R6,6
	LOD R7,1
	MUL R6,R7

	# var t1

	# t1 = t0 * 4
	STO (R2+24856),R6
	LOD R8,4
	MUL R6,R8

	# var t2

	# t2 = &arr1
	LOD R9,(R2+24864)
	LOD R9,R2
	ADD R9,16

	# var t3

	# t3 = t2 + t1
	STO (R2+24864),R9
	STO (R2+24860),R6
	ADD R9,R6

	# *t3 = i
	STO (R2+24868),R9
	STO (R2+8),R5
	STO (R9),R5

	# var t10

	# t10 = 6 * 20
	LOD R10,6
	LOD R11,20
	MUL R10,R11

	# var t11

	# t11 = 6 * 1
	LOD R12,6
	MUL R12,R7

	# var t12

	# t12 = t10 + t11
	STO (R2+24872),R10
	STO (R2+24876),R12
	ADD R10,R12

	# var t13

	# t13 = t12 * 4
	STO (R2+24880),R10
	MUL R10,R8

	# var t14

	# t14 = &arr2
	LOD R13,(R2+24888)
	LOD R13,R2
	ADD R13,56

	# var t15

	# t15 = t14 + t13
	STO (R2+24888),R13
	STO (R2+24884),R10
	ADD R13,R10

	# var t4

	# t4 = 6 * 1
	LOD R14,6
	MUL R14,R7

	# var t5

	# t5 = t4 * 4
	STO (R2+24896),R14
	MUL R14,R8

	# var t6

	# t6 = &arr1
	LOD R15,(R2+24904)
	LOD R15,R2
	ADD R15,16

	# var t7

	# t7 = t6 + t5
	STO (R2+24904),R15
	STO (R2+24900),R14
	ADD R15,R14

	# var t8

	# t8 = *t7
	STO (R2+24908),R15
	LOD R5,(R2+24912)
	LOD R5,(R15)

	# var t9

	# t9 = t8 + 6
	STO (R2+24912),R5
	LOD R6,6
	ADD R5,R6

	# *t15 = t9
	STO (R2+24892),R13
	STO (R2+24916),R5
	STO (R13),R5

	# var t24

	# t24 = 6 * 600
	LOD R5,600
	MUL R6,R5

	# var t25

	# t25 = 6 * 30
	LOD R5,6
	LOD R7,30
	MUL R5,R7

	# var t26

	# t26 = t24 + t25
	STO (R2+24920),R6
	STO (R2+24924),R5
	ADD R6,R5

	# var t27

	# t27 = 6 * 1
	LOD R5,6
	LOD R7,1
	MUL R5,R7

	# var t28

	# t28 = t26 + t27
	STO (R2+24928),R6
	STO (R2+24932),R5
	ADD R6,R5

	# var t29

	# t29 = t28 * 4
	STO (R2+24936),R6
	MUL R6,R8

	# var t30

	# t30 = &arr3
	LOD R5,(R2+24944)
	LOD R5,R2
	ADD R5,856

	# var t31

	# t31 = t30 + t29
	STO (R2+24944),R5
	STO (R2+24940),R6
	ADD R5,R6

	# var t16

	# t16 = 6 * 20
	LOD R6,6
	MUL R6,R11

	# var t17

	# t17 = 6 * 1
	LOD R7,6
	LOD R8,1
	MUL R7,R8

	# var t18

	# t18 = t16 + t17
	STO (R2+24952),R6
	STO (R2+24956),R7
	ADD R6,R7

	# var t19

	# t19 = t18 * 4
	STO (R2+24960),R6
	LOD R7,4
	MUL R6,R7

	# var t20

	# t20 = &arr2
	LOD R7,(R2+24968)
	LOD R7,R2
	ADD R7,56

	# var t21

	# t21 = t20 + t19
	STO (R2+24968),R7
	STO (R2+24964),R6
	ADD R7,R6

	# var t22

	# t22 = *t21
	STO (R2+24972),R7
	LOD R6,(R2+24976)
	LOD R6,(R7)

	# var t23

	# t23 = t22 + 6
	STO (R2+24976),R6
	LOD R7,6
	ADD R6,R7

	# *t31 = t23
	STO (R2+24948),R5
	STO (R2+24980),R6
	STO (R5),R6

	# ifz 0 goto L2
	LOD R5,0
	TST R5
	JEZ L2

	# output L1
	LOD R5,L1
	LOD R15,R5
	OTS

	# label L2
L2:

	# var t32

	# t32 = 6 * 600
	LOD R5,6
	LOD R6,600
	MUL R5,R6

	# var t33

	# t33 = 6 * 30
	LOD R7,6
	LOD R8,30
	MUL R7,R8

	# var t34

	# t34 = t32 + t33
	STO (R2+24984),R5
	STO (R2+24988),R7
	ADD R5,R7

	# var t35

	# t35 = 6 * 1
	LOD R9,6
	LOD R10,1
	MUL R9,R10

	# var t36

	# t36 = t34 + t35
	STO (R2+24992),R5
	STO (R2+24996),R9
	ADD R5,R9

	# var t37

	# t37 = t36 * 4
	STO (R2+25000),R5
	LOD R11,4
	MUL R5,R11

	# var t38

	# t38 = &arr3
	LOD R12,(R2+25008)
	LOD R12,R2
	ADD R12,856

	# var t39

	# t39 = t38 + t37
	STO (R2+25008),R12
	STO (R2+25004),R5
	ADD R12,R5

	# var t40

	# t40 = *t39
	STO (R2+25012),R12
	LOD R13,(R2+25016)
	LOD R13,(R12)

	# j = t40
	STO (R2+25016),R13

	# output j
	STO (R2+12),R13
	LOD R15,R13
	OTI

	# output L1
	LOD R14,L1
	LOD R15,R14
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L1:
	DBS 10,0
STATIC:
	DBN 0,0
STACK:
