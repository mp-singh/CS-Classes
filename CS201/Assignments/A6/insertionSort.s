##############################
#  CS 201 MIPS Boilerplate   #
#  University of Regina      #
##############################

.text
.globl __start

__start:	# execution starts here
###### Your code goes here ###### 

la $a0,ans1
li $v0,4
syscall                         # print 

la      $a0, array             #$a0 contains the base address
la      $t0, length
lw      $t0, ($t0)
sll     $t0, $t0, 2
addi    $t0, $t0, -4
add     $a1, $a0, $t0          # $a1 contains the address of the last memory location of the array
jal     print

la $a0, newline                 # print newline
li $v0, 4
syscall

la      $a0, array 
jal     isort                    #insert

la $a0,ans2
li $v0,4
syscall                         # print 

la      $a0, array              #$a0 contains the base address
jal     print


li $v0, 10                 # done
syscall




li $v0,10		# Exit
syscall		# Bye!

insert: lw $t1, ($a1)
addi $t2, $a1, -4

loop1: blt $t2, $a0, done
lw $t3, ($t2)
blt $t3, $t1, done
sw $t3, 4 ($t2)
addi $t2, $t2, -4
j loop1

done: 	sw $t1, 4 ($t2)
jr $ra


isort: beq $a0, $a1, done1
addi $sp, $sp, -8
sw   $ra, 4 ($sp)
sw   $a1, ($sp)
addi $a1, $a1, -4
jal isort
lw  $a1, ($sp)
jal insert
lw $ra, 4 ($sp)
lw $a1, ($sp)
addi $sp, $sp, 8
done1:jr $ra


print: 	move $t0, $a0
loop: 	blt $a1,$t0,end                # if $t0 > $a1 exit

lw $a0,($t0)
li $v0,1
syscall

la $a0, space                    # print comma
li $v0,4
syscall

addi $t0, $t0, 4                  # move to the next array element
j loop

end:  jr $ra


.data
###### Your data goes here ###### 
array: .word 9, 4, 12, -6, 11, 27, 314, 0, 0, 41, -245, 409
length: .word 12
space:  .asciiz " "
newline: .asciiz "\n"
ans1:   .asciiz "The input array is "
ans2: .asciiz "The sorted array is "

