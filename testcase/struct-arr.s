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

	# var a

	# var b

	# var c1 /* struct class */

	# var t1

	# t1 = &c1
	LOD R5,(R2+5908)
	LOD R5,R2
	ADD R5,24

	# *t1 = 1
	STO (R2+5908),R5
	LOD R6,1
	STO (R5),R6

	# var t2

	# t2 = &c1
	LOD R7,(R2+5912)
	LOD R7,R2
	ADD R7,24

	# var t3

	# t3 = t2 + 44
	STO (R2+5912),R7
	LOD R8,44
	ADD R7,R8

	# var t4

	# t4 = 2 * 1
	LOD R9,2
	MUL R9,R6

	# var t5

	# t5 = t4 * 584
	STO (R2+5920),R9
	LOD R10,584
	MUL R9,R10

	# var t6

	# t6 = t3 + t5
	STO (R2+5916),R7
	STO (R2+5924),R9
	ADD R7,R9

	# *t6 = 2
	STO (R2+5928),R7
	LOD R11,2
	STO (R7),R11

	# var t7

	# t7 = &c1
	LOD R12,(R2+5932)
	LOD R12,R2
	ADD R12,24

	# var t8

	# t8 = t7 + 44
	STO (R2+5932),R12
	ADD R12,R8

	# var t9

	# t9 = 2 * 1
	MUL R11,R6

	# var t10

	# t10 = t9 * 584
	STO (R2+5940),R11
	MUL R11,R10

	# var t11

	# t11 = t8 + t10
	STO (R2+5936),R12
	STO (R2+5944),R11
	ADD R12,R11

	# var t12

	# t12 = t11 + 44
	STO (R2+5948),R12
	ADD R12,R8

	# var t13

	# t13 = 3 * 1
	LOD R13,3
	MUL R13,R6

	# var t14

	# t14 = t13 * 54
	STO (R2+5956),R13
	LOD R14,54
	MUL R13,R14

	# var t15

	# t15 = t12 + t14
	STO (R2+5952),R12
	STO (R2+5960),R13
	ADD R12,R13

	# var t16

	# t16 = t15 + 4
	STO (R2+5964),R12
	LOD R15,4
	ADD R12,R15

	# var t17

	# t17 = 1 * 1
	MUL R6,R6

	# var t18

	# t18 = t17 * 4
	STO (R2+5972),R6
	MUL R6,R15

	# var t19

	# t19 = t16 + t18
	STO (R2+5968),R12
	STO (R2+5976),R6
	ADD R12,R6

	# *t19 = 98
	STO (R2+5980),R12
	LOD R5,98
	STO (R12),R5

	# var t20

	# t20 = &c1
	LOD R5,(R2+5984)
	LOD R5,R2
	ADD R5,24

	# var t21

	# t21 = t20 + 44
	STO (R2+5984),R5
	ADD R5,R8

	# var t22

	# t22 = 2 * 1
	LOD R6,2
	LOD R7,1
	MUL R6,R7

	# var t23

	# t23 = t22 * 584
	STO (R2+5992),R6
	MUL R6,R10

	# var t24

	# t24 = t21 + t23
	STO (R2+5988),R5
	STO (R2+5996),R6
	ADD R5,R6

	# var t25

	# t25 = t24 + 44
	STO (R2+6000),R5
	ADD R5,R8

	# var t26

	# t26 = 3 * 1
	LOD R6,3
	MUL R6,R7

	# var t27

	# t27 = t26 * 54
	STO (R2+6008),R6
	MUL R6,R14

	# var t28

	# t28 = t25 + t27
	STO (R2+6004),R5
	STO (R2+6012),R6
	ADD R5,R6

	# var t29

	# t29 = t28 + 4
	STO (R2+6016),R5
	ADD R5,R15

	# var t30

	# t30 = 0 * 1
	LOD R6,0
	MUL R6,R7

	# var t31

	# t31 = t30 * 4
	STO (R2+6024),R6
	MUL R6,R15

	# var t32

	# t32 = t29 + t31
	STO (R2+6020),R5
	STO (R2+6028),R6
	ADD R5,R6

	# *t32 = 97
	STO (R2+6032),R5
	LOD R6,97
	STO (R5),R6

	# ifz 0 goto L2
	LOD R5,0
	TST R5
	JEZ L2

	# output L1
	LOD R5,L1
	LOD R15,R5
	OTS

	# label L2
L2:

	# var t33

	# t33 = &c1
	LOD R5,(R2+6036)
	LOD R5,R2
	ADD R5,24

	# var t34

	# t34 = *t33
	STO (R2+6036),R5
	LOD R6,(R2+6040)
	LOD R6,(R5)

	# i = t34
	STO (R2+6040),R6

	# var t35

	# t35 = &c1
	LOD R7,(R2+6044)
	LOD R7,R2
	ADD R7,24

	# var t36

	# t36 = t35 + 44
	STO (R2+6044),R7
	LOD R8,44
	ADD R7,R8

	# var t37

	# t37 = 2 * 1
	LOD R9,2
	LOD R10,1
	MUL R9,R10

	# var t38

	# t38 = t37 * 584
	STO (R2+6052),R9
	LOD R11,584
	MUL R9,R11

	# var t39

	# t39 = t36 + t38
	STO (R2+6048),R7
	STO (R2+6056),R9
	ADD R7,R9

	# var t40

	# t40 = *t39
	STO (R2+6060),R7
	LOD R12,(R2+6064)
	LOD R12,(R7)

	# j = t40
	STO (R2+6064),R12

	# var t41

	# t41 = &c1
	LOD R13,(R2+6068)
	LOD R13,R2
	ADD R13,24

	# var t42

	# t42 = t41 + 44
	STO (R2+6068),R13
	ADD R13,R8

	# var t43

	# t43 = 2 * 1
	LOD R14,2
	MUL R14,R10

	# var t44

	# t44 = t43 * 584
	STO (R2+6076),R14
	MUL R14,R11

	# var t45

	# t45 = t42 + t44
	STO (R2+6072),R13
	STO (R2+6080),R14
	ADD R13,R14

	# var t46

	# t46 = t45 + 44
	STO (R2+6084),R13
	ADD R13,R8

	# var t47

	# t47 = 3 * 1
	LOD R15,3
	MUL R15,R10

	# var t48

	# t48 = t47 * 54
	STO (R2+6092),R15
	LOD R5,54
	MUL R15,R5

	# var t49

	# t49 = t46 + t48
	STO (R2+6088),R13
	STO (R2+6096),R15
	ADD R13,R15

	# var t50

	# t50 = t49 + 4
	STO (R2+6100),R13
	LOD R5,4
	ADD R13,R5

	# var t51

	# t51 = 0 * 1
	LOD R5,0
	MUL R5,R10

	# var t52

	# t52 = t51 * 4
	STO (R2+6108),R5
	LOD R7,4
	MUL R5,R7

	# var t53

	# t53 = t50 + t52
	STO (R2+6104),R13
	STO (R2+6112),R5
	ADD R13,R5

	# var t54

	# t54 = *t53
	STO (R2+6116),R13
	LOD R5,(R2+6120)
	LOD R5,(R13)

	# a = t54
	STO (R2+6120),R5

	# var t55

	# t55 = &c1
	LOD R7,(R2+6124)
	LOD R7,R2
	ADD R7,24

	# var t56

	# t56 = t55 + 44
	STO (R2+6124),R7
	ADD R7,R8

	# var t57

	# t57 = 2 * 1
	LOD R8,2
	MUL R8,R10

	# var t58

	# t58 = t57 * 584
	STO (R2+6132),R8
	MUL R8,R11

	# var t59

	# t59 = t56 + t58
	STO (R2+6128),R7
	STO (R2+6136),R8
	ADD R7,R8

	# var t60

	# t60 = t59 + 44
	STO (R2+6140),R7
	LOD R8,44
	ADD R7,R8

	# var t61

	# t61 = 3 * 1
	LOD R8,3
	MUL R8,R10

	# var t62

	# t62 = t61 * 54
	STO (R2+6148),R8
	LOD R9,54
	MUL R8,R9

	# var t63

	# t63 = t60 + t62
	STO (R2+6144),R7
	STO (R2+6152),R8
	ADD R7,R8

	# var t64

	# t64 = t63 + 4
	STO (R2+6156),R7
	LOD R8,4
	ADD R7,R8

	# var t65

	# t65 = 1 * 1
	MUL R10,R10

	# var t66

	# t66 = t65 * 4
	STO (R2+6164),R10
	MUL R10,R8

	# var t67

	# t67 = t64 + t66
	STO (R2+6160),R7
	STO (R2+6168),R10
	ADD R7,R10

	# var t68

	# t68 = *t67
	STO (R2+6172),R7
	LOD R8,(R2+6176)
	LOD R8,(R7)

	# b = t68
	STO (R2+6176),R8

	# ifz 0 goto L3
	STO (R2+16),R5
	STO (R2+8),R6
	STO (R2+20),R8
	STO (R2+12),R12
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

	# output a
	LOD R7,(R2+16)
	LOD R15,R7
	OTC

	# output b
	LOD R8,(R2+20)
	LOD R15,R8
	OTC

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
