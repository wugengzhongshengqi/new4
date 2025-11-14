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

	# var l

	# var a

	# var b

	# var c

	# var d

	# input d
	LOD R5,(R2+36)
	ITC
	LOD R5,R15

	# c = 99
	LOD R6,99

	# b = 98
	LOD R7,98

	# input a
	LOD R8,(R2+24)
	ITC
	LOD R8,R15

	# ifz 0 goto L2
	STO (R2+36),R5
	STO (R2+32),R6
	STO (R2+28),R7
	STO (R2+24),R8
	LOD R9,0
	TST R9
	JEZ L2

	# output L1
	LOD R10,L1
	LOD R15,R10
	OTS

	# label L2
L2:

	# output a
	LOD R5,(R2+24)
	LOD R15,R5
	OTC

	# output b
	LOD R6,(R2+28)
	LOD R15,R6
	OTC

	# output c
	LOD R7,(R2+32)
	LOD R15,R7
	OTC

	# output d
	LOD R8,(R2+36)
	LOD R15,R8
	OTC

	# output L1
	LOD R9,L1
	LOD R15,R9
	OTS

	# i = a

	# j = b

	# k = c

	# l = d

	# ifz 0 goto L3
	STO (R2+8),R5
	STO (R2+12),R6
	STO (R2+16),R7
	STO (R2+20),R8
	LOD R10,0
	TST R10
	JEZ L3

	# output L1
	LOD R15,R9
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

	# output l
	LOD R8,(R2+20)
	LOD R15,R8
	OTI

	# output L1
	LOD R9,L1
	LOD R15,R9
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
