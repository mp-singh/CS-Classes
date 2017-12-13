##
## 	The program --- convertP.s 
##		
##		- will rompt the user to enter a letter indicating Celsius or Fahrenheit
##		- will ask the user for a temperature in Celsius,
##		- convert it to Fahrenheit or Celcuis
##		- print the result.
##
##		Here is the formula of the conversion:
##              F = (9*C/5)+32
##		C = (F-32)*(5/9)
##
##		v0 - reads in a bunch of things
##		t0 - holds temperature integer
##		t1 - hold users choice of Celcuis or Farenheit
##		t2 - hold the byte from t1
##      	a0 - points to output strings
##

#################################################
#                                               #
#               text segment                    #
#                                               #
#################################################

        .text
        .globl __start
__start:                # execution starts here

        la $a0,prompt   # print prompt on terminal
        li $v0,4        # system call to print
        syscall         # out a string
	
	la $a0, choice
	li $a1, 3
	li $v0, 8
	syscall
	move $t1, $a0


############ Get user Choice ###########################
	
	lb $t2, ($t1) 		# get a byte from the char
	beq $t2, 'C', Celcuis 		#jump to Celcuis if 'C'
	beq $t2, 'c', Celcuis 		#jump to Celcuis if 'c'
	beq $t2, 'F', Farhenheit 	#jump to Farhenheit if 'F'
	beq $t2, 'f', Farhenheit 	#jump to Farhenheit if 'f'
	j error # if wrong letter, 	#jump to error
	
     
	
	

############## Farhenheit to Celcuis ###################


Farhenheit:	
	la $a0, promptF
	li $v0, 4
	syscall
	
        li $v0,5	# syscall 5 reads an integer
        syscall  
        jal formulaFtoC
        move $t3, $t0 # save the value retured form the procedure call
        j printResultF  



formulaFtoC:
	sub $t0,$v0,32 # (F-32) 
	mul $t0,$t0,5 	# to convert, multiply by 5,
	div $t0,$t0,9 	# divide by 9, then
	jr $ra




############# Celcuis to Farhenheit ########################

Celcuis:
	la $a0, promptC
	li $v0, 4
	syscall	

        li $v0,5	# syscall 5 reads an integer
        syscall  
        jal formulaCtoF
        move $t3, $v0 # save the value retured form the procedure call
        j printResultC

formulaCtoF:
	mul $t0,$v0,9 	# to convert, multiply by 9,
	div $t0,$t0,5 	# divide by 5, then
	addi $t0,$t0,32  # add 32
	jr $ra


############ Error #################
error:
	la $a0, error1 #print out error statement
	li $v0, 4
	syscall
	j end #end program



######### Print Results #################
printResultC:

	la $a0,ansC	# print string before result
	li $v0,4
	syscall 

	move $a0,$t3	# print result
	li $v0,1
	syscall

	la $a0,endl	# syscal to print out
	li $v0,4	# a new line
	syscall 
	
	j end #end program

printResultF:

	la $a0,ansC	# print string before result
	li $v0,4
	syscall 

	move $a0,$t3	# print result
	li $v0,1
	syscall

	la $a0,endl	# syscal to print out
	li $v0,4	# a new line
	syscall 

	j end #end program


end:
	la $a0,endl	# syscal to print out
	li $v0,4	# a new line
	syscall 
	li $v0,10
	syscall		# Bye!


#################################################
#                                               #
#               data segment                    #
#                                               #
#################################################

        .data

	choice: .space 3
	
	prompt:.asciiz "Please enter 'C' to enter temperature in Celcuis\nand 'F' to enter temperature in Farhenheit: " 

	promptC:.asciiz "Enter temperature (Celcuis): "
	ansC:   .asciiz "The temperature in Fahrenheit is: "

	promptF:.asciiz "Enter temperature (Fahrenheit): "
	ansF:	.asciiz "The temperature in Celcuis is: "
	
	error1: .asciiz "Wrong letter! Bye!\n"
	
	endl:	.asciiz "\n"	   

##
## 	end of file convertP.s