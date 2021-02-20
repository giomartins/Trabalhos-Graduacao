# BINARY SEARCH RECURSIVA
# Arquitetura e Organizacao de Computadores - Trabalho Pratico 01 - 22/02/2020

.data
    Array:		.space 80  # 20 espaços sendo alocados na RAM
    linhas:		.asciiz "\n ========================================================\n"
    mensagem1:		.asciiz " Entre com a quantidade de elementos do Array (MAX  = 20 ):  "
    mensagem2:		.asciiz "=========================== \n Entre com os elementos:  \n===========================\n"
    mensagem3:		.asciiz "\n Entre com o valor a ser pesquisado:  "
    mensagem4: 		.asciiz "\n Posicao: "
    mensagem5: 		.asciiz "\n Tamanho invalido    "
    mensagemFalha:	.asciiz "\n  O elemento esta FORA do exemplo \n "
    mensagemSucesso:	.asciiz "\n O elemento ESTA no exemplo \n"

.text
	main:
    	# Pegando do usuario a quantidade de elementos do array
	li $v0,4
    	la $a0,mensagem1
    	syscall
	li $v0,5 
    	syscall
    	
    	# Armazenando o número de elementos em $s0, multiplicando por 4 e guardando em $t0  
    	move $s0,$v0
   	add $s4, $zero, 4 	# s4 so serve pra armazenar 4 
	mul $t0,$s0,$s4
	add $s1,$zero, 1	# s1 so serve pra armazenar 1 
	
	# Avaliando se o tamanho do array e aceitavel
	blt $t0,$s1,tamanhoInvalido
	bgt $t0,$s1,tamanhoValido
	
		tamanhoInvalido: # Executada apenas quando o usuário entra com um tamanho menor ou igual a zero
		li $v0,4
    		la $a0,mensagem5
    		syscall
    		li $v0,1
    		add $a0,$zero,-1
    		syscall
		li $v0,10
    		syscall
	
		tamanhoValido:
		# Pegando e armazenando os elementos no array (processo que ocorre dentro do while)
    		li $v0,4
    		la $a0,mensagem2
    		syscall
    		jal while
    		
			while:    
    			beq $t0,$t1,exit # Esse exit e executado ao fim do while
   			li $v0,5
    			syscall
    			sw $v0,Array($t1) # store word
    			add $t1,$t1,4
    			j while
   		
   				# O exit fica responsavel por definir os primeiros argumentos L, R e X
    				exit: 
				li $v0,4
    				la $a0,mensagem3
    				syscall
				li $v0,5
    				syscall	
    				move $a3,$v0		# X e guardado em $a3
   				add $a1,$zero,$zero 	# L e guardado em $a1
   				sub $t1,$t1,4
   				move $a2,$t1 		# R e guardado em a2
   	 
 				jal binarySearch
   	
   # -----------------------------------------------------------------------
   # IMPLEMENTACAO DA BINARY SEARCH RECURSIVA
   
   	binarySearch:
   	# Definindo MID e o guardando em $t2
   	sub $t2,$a2,$a1
   	div $t2,$t2,2
   	add $t2,$t2,$a1
   	
   	# Verificando se o MID e multiplo impar ou par de 4
   	div $t2,$s4
   	mfhi $t6
   	
   	# definindo se vou ter que tratar ou nao o endereço do MID
   	beq $t6,0,impar
   	bne $t6,0,par
   	
   		# Armazenando o elemento do meio em $t3, sem precisar tratar o MID
   		impar: 
   		lw $t3,Array($t2)
   		jal avaliacond	
   	
   		# Armazenando o elemento do meio em $t3, tratando o MID
   		par:
   		sub $t2,$t2,2
   		lw $t3,Array($t2)
   		jal avaliacond
   	
   			# Avaliando onde esta o X
   			avaliacond:
   			beq $t3,$a3,Condicao1	# O elemento do meio e o proprio X
   			bgt $t3,$a3,Condicao2	# O X possivelmente esta na primeira metade
   			blt $t3,$a3,Condicao3	# O X possivelmente esta na segunda metade
   			
 				Condicao1:
 				blt $t2,0,finaliza # Se ele por acaso achar um indíce menor que zero
 				bgt $t2,-1, continua 
 				
 					continua:
 					move $v1,$t3
 					li $v0,4
    					la $a0,linhas
    					syscall
 					li $v0,4
    					la $a0,mensagemSucesso
    					syscall
    					div $t2,$t2,$s4
    					li $v0,4
    					la $a0,mensagem4
    					syscall
    					li $v0,1
    					move $a0,$t2
    					syscall
    					li $v0,4
    					la $a0, linhas
    					syscall
 					li $v0,10
 					syscall
 	
 				Condicao2:
 				beq $a1,$a2,finaliza
 				sub $a2,$t2,4
 				blt $a2,0,finaliza
 				jal binarySearch
 	
 				Condicao3:  
 				beq $a1,$a2,finaliza		
   				add $a1,$t2,4
 				jal binarySearch
   	
   					finaliza: # So e executada quando X nao esta no array
   					li $v0,4
    					la $a0,linhas
    					syscall
   					li $v0,4
    					la $a0,mensagemFalha
    					syscall
    					li $v0,4
    					la $a0,linhas
    					syscall
   					li $v0,10
 					syscall
 # --------------------------------------------------------------------------------
 # FIM DO PROGRAMA 
