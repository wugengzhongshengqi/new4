	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var a

	# var b

	# input a
	LOD R5,(R2+8)
	ITC
	LOD R5,R15

	# output a
	STO (R2+8),R5
	LOD R15,R5
	OTC

	# a = 65
	LOD R6,65

	# output a
	STO (R2+8),R6
	LOD R15,R6
	OTC

	# b = 10
	LOD R5,10

	# output b
	STO (R2+12),R5
	LOD R15,R5
	OTC

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
