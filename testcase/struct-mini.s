	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var zs[

	# var i

	# var t1

	# t1 = &zs
	LOD R5,(R2+20)
	LOD R5,R2
	ADD R5,8

	# *t1 = 100
	STO (R2+20),R5
	LOD R6,100
	STO (R5),R6

	# var t2

	# t2 = &zs
	LOD R7,(R2+24)
	LOD R7,R2
	ADD R7,8

	# var t3

	# t3 = *t2
	STO (R2+24),R7
	LOD R8,(R2+28)
	LOD R8,(R7)

	# i = t3
	STO (R2+28),R8

	# output i
	STO (R2+16),R8
	LOD R15,R8
	OTI

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
STATIC:
	DBN 0,0
STACK:
