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

	# var pi

	# var a

	# var b

	# var pc

	# var c1 /* struct class */

	# var t3

	# t3 = &c1
	LOD R5,(R2+5916)
	LOD R5,R2
	ADD R5,32

	# var t4

	# t4 = t3 + 44
	STO (R2+5916),R5
	LOD R6,44
	ADD R5,R6

	# var t5

	# t5 = 2 * 1
	LOD R7,2
	LOD R8,1
	MUL R7,R8

	# var t6

	# t6 = t5 * 584
	STO (R2+5924),R7
	LOD R9,584
	MUL R7,R9

	# var t7

	# t7 = t4 + t6
	STO (R2+5920),R5
	STO (R2+5928),R7
	ADD R5,R7

	# var t8

	# t8 = t7 + 44
	STO (R2+5932),R5
	ADD R5,R6

	# var t9

	# t9 = 3 * 1
	LOD R10,3
	MUL R10,R8

	# var t10

	# t10 = t9 * 54
	STO (R2+5940),R10
	LOD R11,54
	MUL R10,R11

	# var t11

	# t11 = t8 + t10
	STO (R2+5936),R5
	STO (R2+5944),R10
	ADD R5,R10

	# var t1

	# t1 = &c1
	LOD R12,(R2+5952)
	LOD R12,R2
	ADD R12,32

	# *t11 = t1
	STO (R2+5948),R5
	STO (R2+5952),R12
	STO (R5),R12

	# var t12

	# t12 = &c1
	LOD R5,(R2+5956)
	LOD R5,R2
	ADD R5,32

	# var t13

	# t13 = t12 + 44
	STO (R2+5956),R5
	ADD R5,R6

	# var t14

	# t14 = 2 * 1
	LOD R7,2
	MUL R7,R8

	# var t15

	# t15 = t14 * 584
	STO (R2+5964),R7
	MUL R7,R9

	# var t16

	# t16 = t13 + t15
	STO (R2+5960),R5
	STO (R2+5968),R7
	ADD R5,R7

	# var t17

	# t17 = t16 + 44
	STO (R2+5972),R5
	ADD R5,R6

	# var t18

	# t18 = 3 * 1
	LOD R10,3
	MUL R10,R8

	# var t19

	# t19 = t18 * 54
	STO (R2+5980),R10
	MUL R10,R11

	# var t20

	# t20 = t17 + t19
	STO (R2+5976),R5
	STO (R2+5984),R10
	ADD R5,R10

	# var t21

	# t21 = *t20
	STO (R2+5988),R5
	LOD R12,(R2+5992)
	LOD R12,(R5)

	# pi = t21
	STO (R2+5992),R12

	# *pi = 999
	STO (R2+16),R12
	LOD R13,999
	STO (R12),R13

	# var t22

	# t22 = &c1
	LOD R5,(R2+5996)
	LOD R5,R2
	ADD R5,32

	# var t23

	# t23 = *t22
	STO (R2+5996),R5
	LOD R7,(R2+6000)
	LOD R7,(R5)

	# i = t23
	STO (R2+6000),R7

	# output i
	STO (R2+8),R7
	LOD R15,R7
	OTI

	# output L1
	LOD R10,L1
	LOD R15,R10
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
