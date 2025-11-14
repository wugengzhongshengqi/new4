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

	# var i

	# var pi

	# var j

	# input a
	LOD R5,(R2+8)
	ITC
	LOD R5,R15

	# input i
	LOD R6,(R2+20)
	ITI
	LOD R6,R15

	# ifz 0 goto L2
	STO (R2+8),R5
	STO (R2+20),R6
	LOD R7,0
	TST R7
	JEZ L2

	# output L1
	LOD R8,L1
	LOD R15,R8
	OTS

	# label L2
L2:

	# var t0

	# t0 = &a
	LOD R5,(R2+32)
	LOD R5,R2
	ADD R5,8

	# pa = t0
	STO (R2+32),R5

	# var t1

	# t1 = &i
	LOD R6,(R2+36)
	LOD R6,R2
	ADD R6,20

	# pi = t1
	STO (R2+36),R6

	# var t2

	# t2 = *pa
	STO (R2+12),R5
	LOD R7,(R2+40)
	LDC R7,(R5)

	# b = t2
	STO (R2+40),R7

	# var t3

	# t3 = *pi
	STO (R2+24),R6
	LOD R8,(R2+44)
	LOD R8,(R6)

	# j = t3
	STO (R2+44),R8

	# ifz 0 goto L3
	STO (R2+16),R7
	STO (R2+28),R8
	LOD R9,0
	TST R9
	JEZ L3

	# output L1
	LOD R10,L1
	LOD R15,R10
	OTS

	# label L3
L3:

	# output b
	LOD R5,(R2+16)
	LOD R15,R5
	OTC

	# output j
	LOD R6,(R2+28)
	LOD R15,R6
	OTI

	# output L1
	LOD R7,L1
	LOD R15,R7
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
