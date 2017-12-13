##
## 	A5Q32488.s 
##
##  The program is to simulate the following block of code:
##   switch (S) {
##        case  5: A = A + 1; break;
##       case 25: A = A - 1; break;
##       default: A = A * 2; break;
##   }
##
##
##      a0 - points to the string
##      t0 - holds the choice value (S)
##      t1 - hold the value of A
##

#################################################
#                                               #
#               text segment                    #
#                                               #
#################################################



.text
.globl __start
start:  
            # execution starts here
            ##prompt vlaue for A:
 			la $a0, promptA 
            li $v0, 4
            syscall

         	li $v0,5	            # syscall 5 reads an integer
        	syscall  	
        	move $t1, $v0           # Move A to register $t1



            la $a0, promptS         #Prompt user for choice (S)
            li $v0, 4
            syscall     

            li $v0, 5	            # syscall 5 reads an integer for choice
            syscall
            move $t0, $v0           #move choice to $t0


            beq  $t0, 5, is5        # S == 5, jump to is5
            beq  $t0, 25, is25      # S == 25, jump to is25
            j def                   # fetch the branch table entry

is5: 
            la $a0, str_is5 
            li $v0, 4
            syscall

            add $t1, $t1, 1         # A = A + 1; break;
            j print

is25: 
            la $a0, str_is25 
            li $v0, 4
            syscall

            sub $t1, $t1, 1         #A = A - 1; break;
            j print

def: 
            la $a0, str_isdef
            li $v0, 4
            syscall

            mul $t1, $t1, 2         #  A = A * 2; break;
            j print

#print result
print:
            la $a0, ans
            li $v0, 4
            syscall
            move $a0, $t1
            
            li $v0, 1
            syscall
            j end

end:

            li $v0,10	      # Exit
            syscall           # Bye!


#################################################
#                                               #
#               data segment                    #
#                                               #
#################################################

.data

promptS: .asciiz "Please enter a choice (S): "
promptA: .asciiz "Please enter the value for A: "
str_is25: .asciiz "You have entered case 25: A = A - 1\n"
str_is5: .asciiz "You have entered case 5: A = A + 1\n"
str_isdef: .asciiz "You have entered the default case: A = A * 2\n"
ans: .asciiz "The answer is: "

##
## end of file A5Q32488.s