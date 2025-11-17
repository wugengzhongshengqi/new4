	# head
	LOD R2,STACK
	STO (R2),0
	LOD R4,EXIT
	STO (R2+4),R4

	# label main
main:

	# begin

	# var i

	# i = 0
	LOD R5,0

	# label L1
	STO (R2+8),R5
L1:

	# var t0

	# t0 = (i < 10)
	LOD R5,(R2+8)
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
	STO (R2+12),R5
	TST R5
	JEZ L3

	# output i
	LOD R7,(R2+8)
	LOD R15,R7
	OTI

	# var t2

	# t2 = (i == 5)
	LOD R8,5
	SUB R7,R8
	TST R7
	LOD R3,R1+40
	JEZ R3
	LOD R7,0
	LOD R3,R1+24
	JMP R3
	LOD R7,1

	# ifz t2 goto L4
	STO (R2+16),R7
	TST R7
	JEZ L4

	# goto L3
	JMP L3

	# label L4
L4:

	# label L2
L2:

	# var t1

	# t1 = i + 1
	LOD R5,(R2+8)
	LOD R6,1
	ADD R5,R6

	# i = t1
	STO (R2+20),R5

	# goto L1
	STO (R2+8),R5
	JMP L1

	# label L3
L3:

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
