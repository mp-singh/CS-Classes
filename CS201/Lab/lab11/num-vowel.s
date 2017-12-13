
##
## 	The program --- num-vowel.s will count the number of vowels entered in a given sentence.
##
##		- It will ask the user for a letter (character),
##		  
##		- then call a procedure ("vowelp") to check if it is a vowel.
##		- It will return a value to the calling function, 
##		  0 means no, and 1 means yes,
##		- and then print a message from the calling program.
##		
##		v0 - used for syscalls
##		   - holds 0 or 1 after the call to "vowelp"
##		t0 - holds the returned value from the procedure call
## 		a0 - points to strings to be printed 
##		   - also used to pass a letter to "vowelp" 
##
##

#################################################
#												#
#               text segment					#
#												#
#################################################

	.text
	.globl __start
__start:                # execution starts here

	la $a0,prompt1  # print prompt on terminal
	li $v0,4        # system call to print
	syscall         # out a string

	la $a0,letter
	li $a1,5
	li $v0, 8	# syscall 8 reads string/letter
	syscall

	la $a1, letter	# prepare for passing a letter to the procedure
	lb $a0,($a1)

	jal vowelp	# procedure call

	move $t0,$v0	# save the value returned from the procedure call

	beqz $t0, NotVowel
	

	la $a0,ans1	# syscall to print out
	li $v0,4	# the message - is vowel
	syscall 
	j End

NotVowel:
	la $a0,message	# syscall to print out
	li $v0,4	# the message - not vowel
	syscall 

End:	la $a0,endl	# syscall to print out
	li $v0,4	# a new line
	syscall 

	li $v0,10
	syscall		# Bye!

##############################################################
## Define the procedure vowelp
##############################################################

vowelp:

	li $v0, 0	# initialize $v0 to 0
	beq $a0,'a',yes
	beq $a0,'e',yes
	beq $a0,'i',yes
	beq $a0,'o',yes
	beq $a0,'u',yes
	jr $ra
yes:	li $v0,1
	jr $ra
	

#################################################
#												#
#               data segment					#
#												#
#################################################

        .data
	letter:		.space 5
	prompt1:	.asciiz "Enter a letter: "
	
	message:	.asciiz "The character entered is not a vowel."
	ans1:		.asciiz "The number of vowels in the sentence is: "
	endl:		.asciiz "\n"	   

##
## 	end of file num-vowel.s