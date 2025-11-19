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

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15

	# j = 0
	LOD R6,0

	# label L1
	STO (R2+8),R5
	STO (R2+12),R6
L1:

	# var t0

	# t0 = (j < 10)
	LOD R5,(R2+12)
	LOD R6,10
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t0 goto L3
	STO (R2+56),R5
	TST R5
	JEZ L3

	# var t1

	# t1 = j * 1
	LOD R7,(R2+12)
	LOD R8,1
	MUL R7,R8

	# var t2

	# t2 = t1 * 4
	STO (R2+60),R7
	LOD R9,4
	MUL R7,R9

	# var t3

	# t3 = &arr1
	LOD R10,(R2+68)
	LOD R10,R2
	ADD R10,16

	# var t4

	# t4 = t3 + t2
	STO (R2+68),R10
	STO (R2+64),R7
	ADD R10,R7

	# *t4 = i
	STO (R2+72),R10
	LOD R11,(R2+8)
	STO (R10),R11

	# var t5

	# t5 = i + 1
	ADD R11,R8

	# i = t5
	STO (R2+76),R11

	# var t6

	# t6 = j + 1
	LOD R12,(R2+12)
	ADD R12,R8

	# j = t6
	STO (R2+80),R12

	# goto L1
	STO (R2+8),R11
	STO (R2+12),R12
	JMP L1

	# label L3
L3:

	# ifz 0 goto L5
	LOD R5,0
	TST R5
	JEZ L5

	# output L4
	LOD R6,L4
	LOD R15,R6
	OTS

	# label L5
L5:

	# label L6
L6:

	# var t7

	# t7 = (j > 0)
	LOD R5,(R2+12)
	LOD R6,0
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JGZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t7 goto L8
	STO (R2+84),R5
	TST R5
	JEZ L8

	# var t8

	# t8 = j - 1
	LOD R7,(R2+12)
	LOD R8,1
	SUB R7,R8

	# j = t8
	STO (R2+88),R7

	# var t9

	# t9 = j * 1
	STO (R2+12),R7
	MUL R7,R8

	# var t10

	# t10 = t9 * 4
	STO (R2+92),R7
	LOD R9,4
	MUL R7,R9

	# var t11

	# t11 = &arr1
	LOD R10,(R2+100)
	LOD R10,R2
	ADD R10,16

	# var t12

	# t12 = t11 + t10
	STO (R2+100),R10
	STO (R2+96),R7
	ADD R10,R7

	# var t13

	# t13 = *t12
	STO (R2+104),R10
	LOD R11,(R2+108)
	LOD R11,(R10)

	# i = t13
	STO (R2+108),R11

	# output i
	STO (R2+8),R11
	LOD R15,R11
	OTI

	# output L4
	LOD R12,L4
	LOD R15,R12
	OTS

	# goto L6
	JMP L6

	# label L8
L8:

	# output L4
	LOD R5,L4
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L4:
	DBS 10,0
STATIC:
	DBN 0,0
STACK:
