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

	# var k

	# var zs /* struct student */

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15

	# input j
	LOD R6,(R2+12)
	ITI
	LOD R6,R15

	# input k
	LOD R7,(R2+16)
	ITI
	LOD R7,R15

	# var t1

	# t1 = &zs
	LOD R8,(R2+32)
	LOD R8,R2
	ADD R8,20

	# *t1 = i
	STO (R2+32),R8
	STO (R2+8),R5
	STO (R8),R5

	# var t2

	# t2 = &zs
	LOD R9,(R2+36)
	LOD R9,R2
	ADD R9,20

	# var t3

	# t3 = t2 + 4
	STO (R2+36),R9
	LOD R10,4
	ADD R9,R10

	# *t3 = j
	STO (R2+40),R9
	STO (R2+12),R6
	STO (R9),R6

	# var t4

	# t4 = &zs
	LOD R11,(R2+44)
	LOD R11,R2
	ADD R11,20

	# var t5

	# t5 = t4 + 8
	STO (R2+44),R11
	LOD R12,8
	ADD R11,R12

	# *t5 = k
	STO (R2+48),R11
	STO (R2+16),R7
	STO (R11),R7

	# ifz 0 goto L2
	LOD R13,0
	TST R13
	JEZ L2

	# output L1
	LOD R14,L1
	LOD R15,R14
	OTS

	# label L2
L2:

	# var t6

	# t6 = &zs
	LOD R5,(R2+52)
	LOD R5,R2
	ADD R5,20

	# var t7

	# t7 = t6 + 8
	STO (R2+52),R5
	LOD R6,8
	ADD R5,R6

	# var t8

	# t8 = *t7
	STO (R2+56),R5
	LOD R7,(R2+60)
	LOD R7,(R5)

	# var t9

	# t9 = t8 + 100
	STO (R2+60),R7
	LOD R8,100
	ADD R7,R8

	# i = t9
	STO (R2+64),R7

	# var t10

	# t10 = &zs
	LOD R9,(R2+68)
	LOD R9,R2
	ADD R9,20

	# var t11

	# t11 = t10 + 4
	STO (R2+68),R9
	LOD R10,4
	ADD R9,R10

	# var t12

	# t12 = *t11
	STO (R2+72),R9
	LOD R11,(R2+76)
	LOD R11,(R9)

	# var t13

	# t13 = t12 + 200
	STO (R2+76),R11
	LOD R12,200
	ADD R11,R12

	# j = t13
	STO (R2+80),R11

	# var t14

	# t14 = &zs
	LOD R13,(R2+84)
	LOD R13,R2
	ADD R13,20

	# var t15

	# t15 = *t14
	STO (R2+84),R13
	LOD R14,(R2+88)
	LOD R14,(R13)

	# var t16

	# t16 = t15 + 300
	STO (R2+88),R14
	LOD R15,300
	ADD R14,R15

	# k = t16
	STO (R2+92),R14

	# ifz 0 goto L3
	STO (R2+8),R7
	STO (R2+12),R11
	STO (R2+16),R14
	LOD R5,0
	TST R5
	JEZ L3

	# output L1
	LOD R5,L1
	LOD R15,R5
	OTS

	# label L3
L3:

	# output i
	LOD R5,(R2+8)
	LOD R15,R5
	OTI

	# output j
	LOD R6,(R2+12)
	LOD R15,R6
	OTI

	# output k
	LOD R7,(R2+16)
	LOD R15,R7
	OTI

	# output L1
	LOD R8,L1
	LOD R15,R8
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
