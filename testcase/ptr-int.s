	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var a

	# var pa

	# var b

	# var c

	# var d

	# var ptr

	# input a
	LOD R5,(R2+8)
	ITI
	LOD R5,R15

	# var t0

	# t0 = a + 10
	STO (R2+8),R5
	LOD R6,10
	ADD R5,R6

	# b = t0
	STO (R2+32),R5

	# var t1

	# t1 = b - 20
	STO (R2+16),R5
	LOD R7,20
	SUB R5,R7

	# c = t1
	STO (R2+36),R5

	# var t2

	# t2 = c * 30
	STO (R2+20),R5
	LOD R8,30
	MUL R5,R8

	# d = t2
	STO (R2+40),R5

	# output a
	LOD R9,(R2+8)
	LOD R15,R9
	OTI

	# output b
	LOD R10,(R2+16)
	LOD R15,R10
	OTI

	# output c
	LOD R11,(R2+20)
	LOD R15,R11
	OTI

	# output d
	STO (R2+24),R5
	LOD R15,R5
	OTI

	# output L1
	LOD R12,L1
	LOD R15,R12
	OTS

	# var t3

	# t3 = &a
	LOD R13,(R2+44)
	LOD R13,R2
	ADD R13,8

	# pa = t3
	STO (R2+44),R13

	# *pa = 111
	STO (R2+12),R13
	LOD R14,111
	STO (R13),R14

	# output a
	LOD R15,R9
	OTI

	# ptr = pa

	# *ptr = 222
	STO (R2+28),R13
	LOD R15,222
	STO (R13),R15

	# output a
	LOD R15,R9
	OTI

	# output L1
	LOD R15,R12
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
