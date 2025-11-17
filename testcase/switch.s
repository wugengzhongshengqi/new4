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

	# input i
	LOD R5,(R2+8)
	ITI
	LOD R5,R15

	# var t3

	# t3 = (i == 1)
	STO (R2+8),R5
	LOD R6,1
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t3 goto L3
	STO (R2+16),R5
	TST R5
	JEZ L3

	# var t0

	# t0 = i + 1
	LOD R7,(R2+8)
	ADD R7,R6

	# j = t0
	STO (R2+20),R7

	# output j
	STO (R2+12),R7
	LOD R15,R7
	OTI

	# goto L1
	JMP L1

	# goto L1
	JMP L1

	# label L3
L3:

	# var t4

	# t4 = (i == 2)
	LOD R5,(R2+8)
	LOD R6,2
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t4 goto L4
	STO (R2+24),R5
	TST R5
	JEZ L4

	# var t1

	# t1 = i + 2
	LOD R7,(R2+8)
	ADD R7,R6

	# j = t1
	STO (R2+28),R7

	# output j
	STO (R2+12),R7
	LOD R15,R7
	OTI

	# goto L1
	JMP L1

	# goto L1
	JMP L1

	# label L4
L4:

	# var t5

	# t5 = (i == 3)
	LOD R5,(R2+8)
	LOD R6,3
	SUB R5,R6
	TST R5
	LOD R3,R1+40
	JEZ R3
	LOD R5,0
	LOD R3,R1+24
	JMP R3
	LOD R5,1

	# ifz t5 goto L5
	STO (R2+32),R5
	TST R5
	JEZ L5

	# var t2

	# t2 = i + 3
	LOD R7,(R2+8)
	ADD R7,R6

	# j = t2
	STO (R2+36),R7

	# output j
	STO (R2+12),R7
	LOD R15,R7
	OTI

	# goto L1
	JMP L1

	# goto L1
	JMP L1

	# label L5
L5:

	# output L2
	LOD R5,L2
	LOD R15,R5
	OTS

	# goto L1
	JMP L1

	# label L1
L1:

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
L6:
	DBS 10,0
L2:
	DBS 110,111,116,32,49,32,50,32,51,0
STATIC:
	DBN 0,0
STACK:
