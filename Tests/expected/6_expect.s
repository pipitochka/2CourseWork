## Generated by codeGenerator
.data
.text
.global main

main:
addi sp, sp, -12
addi a4, sp, 4
addi a5, sp, 8
sw a5, 0(a4)
li a5, 4
sw a5, -4(a4)
addi sp, sp, -12
addi a4, sp, 4
addi a5, sp, 8
sw a5, 0(a4)
li a5, 4
sw a5, -4(a4)
# start OP
li a0, 10
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 28
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

sw a3, 0(a1)

# end OP
loop0:
# start OP
li a0, 7
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 28
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

bgt a0, a3, loop2
li a0 0
j loop3

loop2:
li a0 1

loop3:

# end OP
beq a0, x0, loop1
# start OP
li a0, 1
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 28
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

sub a0, a0, a3
sw a0, 0(a1)

# end OP
j loop0
loop1:
# start OP
li a0, 0
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 16
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

sw a3, 0(a1)

# end OP
loop4:
# start OP
li a0, 3
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 16
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

blt a0, a3, loop6
li a0 0
j loop7

loop6:
li a0 1

loop7:

# end OP
beq a0, x0, loop5
# start OP
li a0, 1
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 28
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

sub a0, a0, a3
sw a0, 0(a1)

# end OP
# start OP
li a0, 1
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 16
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

add a0, a0, a3
sw a0, 0(a1)

# end OP
j loop4
loop5:
# start OP
li a0, 5
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 28
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

blt a0, a3, loop8
li a0 0
j loop9

loop8:
li a0 1

loop9:

# end OP
beq a0, x0, loop10
# start OP
li a0, 8
li a1, 0
li a2, 0
addi sp, sp, -4
sw a0, 0(sp)
addi sp, sp, -4
sw a1, 0(sp)
addi sp, sp, -4
sw a2, 0(sp)

addi a4, sp, 28
mv a1, a4
lw a1, 0(a1)
lw a0, 0(a1)
lw a2, -4(a4)
lw a5, 0(sp)
addi sp, sp, 4
lw a4, 0(sp)
addi sp, sp, 4
lw a3, 0(sp)
addi sp, sp, 4

sw a3, 0(a1)

# end OP
j loop11
loop10:
loop11:
addi sp, sp, 24
## end function main

li a7, 10
ecall
