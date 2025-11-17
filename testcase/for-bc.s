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

	# input j
	LOD R5,(R2+12)
	ITI
	LOD R5,R15

	# i = 0
	LOD R6,0

	# label L1
	STO (R2+12),R5
	STO (R2+8),R6
L1:

	# var t0

	# t0 = (i < j)
	LOD R5,(R2+8)
	LOD R6,(R2+12)
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t0 goto L3
	STO (R2+16),R5
	TST R5
	JEZ L3

	# var t2

	# t2 = (i > 10)
	LOD R7,(R2+8)
	LOD R8,10
	SUB R7,R8
	TST R7
	LOD R3,R1+40
	JGZ R3
	LOD R7,0
	LOD R3,R1+24
	JMP R3
	LOD R7,1

	# ifz t2 goto L5
	STO (R2+20),R7
	TST R7
	JEZ L5

	# output L4
	LOD R9,L4
	LOD R15,R9
	OTS

	# goto L3
	JMP L3

	# label L5
L5:

	# output i
	LOD R5,(R2+8)
	LOD R15,R5
	OTI

	# label L2
L2:

	# var t1

	# t1 = i + 1
	LOD R5,(R2+8)
	LOD R6,1
	ADD R5,R6

	# i = t1
	STO (R2+24),R5

	# goto L1
	STO (R2+8),R5
	JMP L1

	# label L3
L3:

	# output L6
	LOD R5,L6
	LOD R15,R5
	OTS

	# i = 0
	LOD R6,0

	# label L7
	STO (R2+8),R6
L7:

	# var t3

	# t3 = (i < j)
	LOD R5,(R2+8)
	LOD R6,(R2+12)
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JLZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t3 goto L9
	STO (R2+28),R5
	TST R5
	JEZ L9

	# var t5

	# t5 = (i == 10)
	LOD R7,(R2+8)
	LOD R8,10
	SUB R7,R8
	TST R7
	LOD R3,R1+40
	JEZ R3
	LOD R7,0
	LOD R3,R1+24
	JMP R3
	LOD R7,1

	# ifz t5 goto L11
	STO (R2+32),R7
	TST R7
	JEZ L11

	# output L10
	LOD R9,L10
	LOD R15,R9
	OTS

	# goto L8
	JMP L8

	# label L11
L11:

	# output i
	LOD R5,(R2+8)
	LOD R15,R5
	OTI

	# label L8
L8:

	# var t4

	# t4 = i + 1
	LOD R5,(R2+8)
	LOD R6,1
	ADD R5,R6

	# i = t4
	STO (R2+36),R5

	# goto L7
	STO (R2+8),R5
	JMP L7

	# label L9
L9:

	# output L6
	LOD R5,L6
	LOD R15,R5
	OTS

	# end
	LOD R3,(R2+4)
	LOD R2,(R2)
	JMP R3

	# tail
EXIT:
	END
L10:
	DBS 99,111,110,116,105,110,117,101,0
L6:
	DBS 10,0
L4:
	DBS 98,114,101,97,107,0
STATIC:
	DBN 0,0
STACK:
