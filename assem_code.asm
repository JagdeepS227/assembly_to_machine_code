.data
var1: .word 0x11111111			# word1 or var1 x5
var2: .word 0xffffffff	# word2 or var2 x6 
i1: .word 16			# i1 x20
j1: .word 11			# j1 x21
i2: .word 31			# i2 x22
j2: .word 26			# j2 x23
.text
main:
lw x5 var1
lw x6 var2
lw x20 i1
lw x21 j1
lw x22 i2
lw x23 j2
jal replace_bits		#11001000001010100000001101111		10000000000000011101111
replace_bits:
addi x7 x21 -1			
srl x5 x5 x7			
# shifting right by 10 position
sub x7 x20 x21						
addi x7 x7 2			 
addi x8 x0 32				
sub x7 x8 x7 			
sll x5 x5 x7			# shifting left by 25 position    
addi x7 x0 32
sub x7 x27 x22			    
srl x5 x5 x7			### now 16-11 is at 31-26  ###
# x26 will contain the x6 temp
lw x26 var2
srl x26 x26 x22			# to get the 32nd bit
sll x26 x26 x22
addi x7 x0 32
sub x7 x7 x23
addi x7 x7 1			# making the 32 to 26 bits 0
sll x6 x6 x7
srl x6 x6 x7			### now all the 31-26 are 0###
xor x6 x6 x26
or x7 x6 x5				### result ###
exit:
