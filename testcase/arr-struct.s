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

	# var cls[10]

	# var t1

	# t1 = &cls
	LOD R5,(R2+58864)
	LOD R5,R2
	ADD R5,24

	# var t2

	# t2 = 5 * 1
	LOD R6,5
	LOD R7,1
	MUL R6,R7

	# var t3

	# t3 = t2 * 5884
	STO (R2+58868),R6
	LOD R8,5884
	MUL R6,R8

	# var t4

	# t4 = t1 + t3
	STO (R2+58864),R5
	STO (R2+58872),R6
	ADD R5,R6

	# *t4 = 1
	STO (R2+58876),R5
	STO (R5),R7

	# var t5

	# t5 = &cls
	LOD R9,(R2+58880)
	LOD R9,R2
	ADD R9,24

	# var t6

	# t6 = 5 * 1
	LOD R10,5
	MUL R10,R7

	# var t7

	# t7 = t6 * 5884
	STO (R2+58884),R10
	MUL R10,R8

	# var t8

	# t8 = t5 + t7
	STO (R2+58880),R9
	STO (R2+58888),R10
	ADD R9,R10

	# var t9

	# t9 = t8 + 44
	STO (R2+58892),R9
	LOD R11,44
	ADD R9,R11

	# var t10

	# t10 = 2 * 1
	LOD R12,2
	MUL R12,R7

	# var t11

	# t11 = t10 * 584
	STO (R2+58900),R12
	LOD R13,584
	MUL R12,R13

	# var t12

	# t12 = t9 + t11
	STO (R2+58896),R9
	STO (R2+58904),R12
	ADD R9,R12

	# *t12 = 2
	STO (R2+58908),R9
	LOD R14,2
	STO (R9),R14

	# var t13

	# t13 = &cls
	LOD R15,(R2+58912)
	LOD R15,R2
	ADD R15,24

	# var t14

	# t14 = 5 * 1
	LOD R5,5
	MUL R5,R7

	# var t15

	# t15 = t14 * 5884
	STO (R2+58916),R5
	MUL R5,R8

	# var t16

	# t16 = t13 + t15
	STO (R2+58912),R15
	STO (R2+58920),R5
	ADD R15,R5

	# var t17

	# t17 = t16 + 44
	STO (R2+58924),R15
	ADD R15,R11

	# var t18

	# t18 = 2 * 1
	MUL R14,R7

	# var t19

	# t19 = t18 * 584
	STO (R2+58932),R14
	MUL R14,R13

	# var t20

	# t20 = t17 + t19
	STO (R2+58928),R15
	STO (R2+58936),R14
	ADD R15,R14

	# var t21

	# t21 = t20 + 44
	STO (R2+58940),R15
	ADD R15,R11

	# var t22

	# t22 = 3 * 1
	LOD R5,3
	MUL R5,R7

	# var t23

	# t23 = t22 * 54
	STO (R2+58948),R5
	LOD R6,54
	MUL R5,R6

	# var t24

	# t24 = t21 + t23
	STO (R2+58944),R15
	STO (R2+58952),R5
	ADD R15,R5

	# var t25

	# t25 = t24 + 4
	STO (R2+58956),R15
	LOD R5,4
	ADD R15,R5

	# var t26

	# t26 = 1 * 1
	MUL R7,R7

	# var t27

	# t27 = t26 * 4
	STO (R2+58964),R7
	MUL R7,R5

	# var t28

	# t28 = t25 + t27
	STO (R2+58960),R15
	STO (R2+58968),R7
	ADD R15,R7

	# *t28 = 98
	STO (R2+58972),R15
	LOD R5,98
	STO (R15),R5

	# var t29

	# t29 = &cls
	LOD R5,(R2+58976)
	LOD R5,R2
	ADD R5,24

	# var t30

	# t30 = 5 * 1
	LOD R6,5
	LOD R7,1
	MUL R6,R7

	# var t31

	# t31 = t30 * 5884
	STO (R2+58980),R6
	MUL R6,R8

	# var t32

	# t32 = t29 + t31
	STO (R2+58976),R5
	STO (R2+58984),R6
	ADD R5,R6

	# var t33

	# t33 = t32 + 44
	STO (R2+58988),R5
	ADD R5,R11

	# var t34

	# t34 = 2 * 1
	LOD R6,2
	MUL R6,R7

	# var t35

	# t35 = t34 * 584
	STO (R2+58996),R6
	MUL R6,R13

	# var t36

	# t36 = t33 + t35
	STO (R2+58992),R5
	STO (R2+59000),R6
	ADD R5,R6

	# var t37

	# t37 = t36 + 44
	STO (R2+59004),R5
	ADD R5,R11

	# var t38

	# t38 = 3 * 1
	LOD R6,3
	MUL R6,R7

	# var t39

	# t39 = t38 * 54
	STO (R2+59012),R6
	LOD R7,54
	MUL R6,R7

	# var t40

	# t40 = t37 + t39
	STO (R2+59008),R5
	STO (R2+59016),R6
	ADD R5,R6

	# var t41

	# t41 = t40 + 4
	STO (R2+59020),R5
	LOD R6,4
	ADD R5,R6

	# var t42

	# t42 = 0 * 1
	LOD R6,0
	LOD R7,1
	MUL R6,R7

	# var t43

	# t43 = t42 * 4
	STO (R2+59028),R6
	LOD R7,4
	MUL R6,R7

	# var t44

	# t44 = t41 + t43
	STO (R2+59024),R5
	STO (R2+59032),R6
	ADD R5,R6

	# *t44 = 97
	STO (R2+59036),R5
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

	# var t45

	# t45 = &cls
	LOD R5,(R2+59040)
	LOD R5,R2
	ADD R5,24

	# var t46

	# t46 = 5 * 1
	LOD R6,5
	LOD R7,1
	MUL R6,R7

	# var t47

	# t47 = t46 * 5884
	STO (R2+59044),R6
	LOD R8,5884
	MUL R6,R8

	# var t48

	# t48 = t45 + t47
	STO (R2+59040),R5
	STO (R2+59048),R6
	ADD R5,R6

	# var t49

	# t49 = *t48
	STO (R2+59052),R5
	LOD R9,(R2+59056)
	LOD R9,(R5)

	# i = t49
	STO (R2+59056),R9

	# var t50

	# t50 = &cls
	LOD R10,(R2+59060)
	LOD R10,R2
	ADD R10,24

	# var t51

	# t51 = 5 * 1
	LOD R11,5
	MUL R11,R7

	# var t52

	# t52 = t51 * 5884
	STO (R2+59064),R11
	MUL R11,R8

	# var t53

	# t53 = t50 + t52
	STO (R2+59060),R10
	STO (R2+59068),R11
	ADD R10,R11

	# var t54

	# t54 = t53 + 44
	STO (R2+59072),R10
	LOD R12,44
	ADD R10,R12

	# var t55

	# t55 = 2 * 1
	LOD R13,2
	MUL R13,R7

	# var t56

	# t56 = t55 * 584
	STO (R2+59080),R13
	LOD R14,584
	MUL R13,R14

	# var t57

	# t57 = t54 + t56
	STO (R2+59076),R10
	STO (R2+59084),R13
	ADD R10,R13

	# var t58

	# t58 = *t57
	STO (R2+59088),R10
	LOD R15,(R2+59092)
	LOD R15,(R10)

	# j = t58
	STO (R2+59092),R15

	# var t59

	# t59 = &cls
	LOD R5,(R2+59096)
	LOD R5,R2
	ADD R5,24

	# var t60

	# t60 = 5 * 1
	LOD R6,5
	MUL R6,R7

	# var t61

	# t61 = t60 * 5884
	STO (R2+59100),R6
	MUL R6,R8

	# var t62

	# t62 = t59 + t61
	STO (R2+59096),R5
	STO (R2+59104),R6
	ADD R5,R6

	# var t63

	# t63 = t62 + 44
	STO (R2+59108),R5
	ADD R5,R12

	# var t64

	# t64 = 2 * 1
	LOD R6,2
	MUL R6,R7

	# var t65

	# t65 = t64 * 584
	STO (R2+59116),R6
	MUL R6,R14

	# var t66

	# t66 = t63 + t65
	STO (R2+59112),R5
	STO (R2+59120),R6
	ADD R5,R6

	# var t67

	# t67 = t66 + 44
	STO (R2+59124),R5
	ADD R5,R12

	# var t68

	# t68 = 3 * 1
	LOD R6,3
	MUL R6,R7

	# var t69

	# t69 = t68 * 54
	STO (R2+59132),R6
	LOD R7,54
	MUL R6,R7

	# var t70

	# t70 = t67 + t69
	STO (R2+59128),R5
	STO (R2+59136),R6
	ADD R5,R6

	# var t71

	# t71 = t70 + 4
	STO (R2+59140),R5
	LOD R6,4
	ADD R5,R6

	# var t72

	# t72 = 0 * 1
	LOD R6,0
	LOD R7,1
	MUL R6,R7

	# var t73

	# t73 = t72 * 4
	STO (R2+59148),R6
	LOD R7,4
	MUL R6,R7

	# var t74

	# t74 = t71 + t73
	STO (R2+59144),R5
	STO (R2+59152),R6
	ADD R5,R6

	# var t75

	# t75 = *t74
	STO (R2+59156),R5
	LOD R6,(R2+59160)
	LOD R6,(R5)

	# a = t75
	STO (R2+59160),R6

	# var t76

	# t76 = &cls
	LOD R5,(R2+59164)
	LOD R5,R2
	ADD R5,24

	# var t77

	# t77 = 5 * 1
	LOD R7,5
	LOD R8,1
	MUL R7,R8

	# var t78

	# t78 = t77 * 5884
	STO (R2+59168),R7
	LOD R8,5884
	MUL R7,R8

	# var t79

	# t79 = t76 + t78
	STO (R2+59164),R5
	STO (R2+59172),R7
	ADD R5,R7

	# var t80

	# t80 = t79 + 44
	STO (R2+59176),R5
	ADD R5,R12

	# var t81

	# t81 = 2 * 1
	LOD R7,2
	LOD R8,1
	MUL R7,R8

	# var t82

	# t82 = t81 * 584
	STO (R2+59184),R7
	MUL R7,R14

	# var t83

	# t83 = t80 + t82
	STO (R2+59180),R5
	STO (R2+59188),R7
	ADD R5,R7

	# var t84

	# t84 = t83 + 44
	STO (R2+59192),R5
	ADD R5,R12

	# var t85

	# t85 = 3 * 1
	LOD R7,3
	MUL R7,R8

	# var t86

	# t86 = t85 * 54
	STO (R2+59200),R7
	LOD R8,54
	MUL R7,R8

	# var t87

	# t87 = t84 + t86
	STO (R2+59196),R5
	STO (R2+59204),R7
	ADD R5,R7

	# var t88

	# t88 = t87 + 4
	STO (R2+59208),R5
	LOD R7,4
	ADD R5,R7

	# var t89

	# t89 = 1 * 1
	LOD R7,1
	MUL R7,R7

	# var t90

	# t90 = t89 * 4
	STO (R2+59216),R7
	LOD R8,4
	MUL R7,R8

	# var t91

	# t91 = t88 + t90
	STO (R2+59212),R5
	STO (R2+59220),R7
	ADD R5,R7

	# var t92

	# t92 = *t91
	STO (R2+59224),R5
	LOD R7,(R2+59228)
	LOD R7,(R5)

	# b = t92
	STO (R2+59228),R7

	# ifz 0 goto L3
	STO (R2+16),R6
	STO (R2+20),R7
	STO (R2+8),R9
	STO (R2+12),R15
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
