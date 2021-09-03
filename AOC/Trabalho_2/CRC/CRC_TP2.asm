# CRC - até 8 bits
# Arquitetura e Organização de Computadores - Trabalho Prático 02 - 15/03/2021
# Professor Ricardo Duarte

.data
   dividendo:		.space 128  # 32 espaços sendo alocados na RAM (cada byte comportará um bit)
   gerador:		.space 32 # 8 espaços sendo alocados na RAM (cada espaço comportará um bit)
   selecao:		.space 32 # 8 espaços sendo alocados na RAM (cada espaço comportará um bit)
   resto:		.space 32 # 8 espaços sendo alocados na RAM (cada espaço comportará um bit)	
   linhas:		.asciiz "\n ========================================================\n"
   mensagem1:		.asciiz " Entre com a quantidade de bits do dado ( 0 < QUANTIDADE < 25 ):  "
   mensagem2:		.asciiz " Entre com a quantidade de bits do gerador (0 < QUANTIDADE < 9 ):  "
   mensagem3:		.asciiz "=========================== \n Entre com os bits do Dado, começando por 1 (SEPARADOS POR ENTER, DA ESQUERDA P/ A DIREITA, 1 OU 0 APENAS!!!):  \n===========================\n"
   mensagem4:		.asciiz "=========================== \n Entre com os bits de Gerador, começando por 1 (SEPARADOS POR ENTER, DA ESQUERDA P/ A DIREITA, 1 OU 0 APENAS!!!):  \n===========================\n"
   mensagem5:		.asciiz "\n Tamanho invalido \n"

.text
	main:
	# ================= ENTRADA DO DADO =======================
	# Pegando do usuário a quantidade de bits do Dado
	li $v0,4
    	la $a0,mensagem1
    	syscall
	li $v0,5
    	syscall
    	
    	# Armazenando o número de bits do dado em $s0 
    	move $s0,$v0
   	
	# Avaliando se a quantidade de bits do dado é aceitável
	add $s4,$zero,4		
	add $s3,$zero,96	
	mul $t0,$s0,$s4		
	bgt $t0,$s3,tamanhoInvalidoDado
	beq $t0,$s3,tamanhoValidoDado
	blt $t0,$s3,tamanhoValidoDado
	
		tamanhoInvalidoDado: # Encerra a execução para entrada inválida
		li $v0,4
    		la $a0,mensagem5
    		syscall
		li $v0,10
    		syscall
	
		tamanhoValidoDado:
		# Pegando e armazenando os elementos no dividendo (processo que ocorre dentro do whileDado)
    		li $v0,4
    		la $a0,mensagem3
    		syscall
    		jal whileDado
    		
			whileDado:    
    			beq $t0,$t1,entradaGerador # Esse entradaGerador é executado ao fim do whileDado
   			li $v0,5
    			syscall
    			sw $v0,dividendo($t1)
    			add $t1,$t1,4
    			j whileDado
   		
   	# ================= ENTRADA DO GERADOR =======================
   	entradaGerador:
   	# Pegando do usuário a quantidade de bits do gerador
	li $v0,4
    	la $a0,mensagem2
    	syscall
	li $v0,5
    	syscall
    	
    	# Armazenando o número de bits do gerador em $s1 
    	move $s1,$v0
   	
	# Avaliando se a quantidade de bits do gerador é aceitável
	add $s5,$zero,32	# $s5 só serve para armazenar 32
	mul $t2,$s1,$s4		# $t2 armazena o produto do nº de bits do gerador por 4
	bgt $t2,$s5,tamanhoInvalidoGerador
	beq $t2,$s5,tamanhoValidoGerador
	blt $t2,$s5,tamanhoValidoGerador
	
		tamanhoInvalidoGerador: # Executada apenas quando o usuário entra com um tamanho de byteVal maior que 24
		li $v0,4
    		la $a0,mensagem5
    		syscall
		li $v0,10
    		syscall
	
		tamanhoValidoGerador:
		# Pegando e armazenando os elementos no dividendo(processo que ocorre dentro do while)
    		li $v0,4
    		la $a0,mensagem4
    		syscall
    		jal whileGerador
    		
			whileGerador:    
    			beq $t3,$t2,concatena # Esse concatena avança pra próxima etapa:
   			li $v0,5
    			syscall
    			sw $v0,gerador($t3)
    			add $t3,$t3,4
    			j whileGerador
    			
    		
  # ================= CONCATENAÇÃO =======================
    	concatena: # concatena o dado com a quantidade devida de zeros p/ formar o dividendo principal
    	add $t5,$t0,$t2 
    	add $t5,$t5,-4
    	jal whileConcatena
    				
    		whileConcatena:
    		beq $t1,$t5,montaPrimeiroResto
    		sw $zero,dividendo($t1)
    		add $t1,$t1,4
    		j whileConcatena
    					
    			# procedimento pra criar o primeiro resto, tudo zerado
    			montaPrimeiroResto:
    			beq $t8,$t3,inicializaT7
    			lw $t6,dividendo($t8)
    			sw $t6,resto($t8)
    			add $t8,$t8,4
    			j montaPrimeiroResto
    					
    				inicializaT7:	# atribui o valor de $t2 a $t7
    				add $t7,$t2,$zero
    				j determinaCRC
    					
    		
  # ============= DETERMINA CRC ====================			
    	determinaCRC: # Procedimento principal no cálculo do CRC
    	bgt $t7,$t5,imprimeCRC
    	beq $t7,$t5,imprimeCRC
 	add $t8,$zero,$zero
    	add $t9,$zero,$zero
    	add $t6,$zero,$zero
    	add $t4,$zero,$zero
    	add $t1,$zero,$zero
    	jal avaliaQuemDesce
    	
    		avaliaQuemDesce: # Avalia quantos bits irão descer do dividendo principal p/ a próx.divisão
    		lw $t1,resto($t9)
    		bne $t1,0,montaSelecaoComResto		
    		add $t9,$t9,4
    		j avaliaQuemDesce
    		
    			montaSelecaoComResto: # Determina quais bits do resto entrarão na próx. divisão
    			beq $t9,$t2,montaSelecaoComDividendo	
    			lw $t1,resto($t9)		
    			sw $t1,selecao($t8)
    			add $t8,$t8,4
    			add $t9,$t9,4
    			j montaSelecaoComResto
    		
    				montaSelecaoComDividendo: # Determina quais bits do dividendo principal entrarão na próx. divisão
    				beq $t8,$t2,zera1
    				lw $t1,dividendo($t7)
    				sw $t1,selecao($t8)
    				add $t8,$t8,4
    				add $t7,$t7,4
    				j montaSelecaoComDividendo
    			
    					zera1: # Zera registradores que precisaremos reutilizar
    					add $t8,$zero,$zero
    					add $t9,$zero,$zero
    					add $t6,$zero,$zero
    					add $t4,$zero,$zero
    					j XOR
    						
    						XOR: # Realiza a operação XOR 
    						bgt $t7,$t5,imprimeCRC
    						beq $t7,$t5,imprimeCRC
    						beq $t8,$t3,zera2
    						lw $t6,selecao($t8) 
    						lw $t4,gerador($t8)
    						beq $t4,$t6,colocaZero
    						bne $t4,$t6,colocaUm
    						
    							colocaZero: # Resultado 0 da operação XOR
    							sw $zero,resto($t8)
    							add $t8,$t8,4
    							j XOR
    							
    							colocaUm: # Resultado 1 da operação XOR 
    							add $t4,$zero,1		
    							sw $t4,resto($t8)
    							add $t8,$t8,4
    							j XOR
    							
    							zera2: # Zera registradores que precisaremos reutilizar
    							add $t8,$zero,$zero
    							add $t9,$zero,$zero
    							add $t6,$zero,$zero
    							add $t4,$zero,$zero
    							j determinaCRC
    							
    							imprimeCRC: # Imprime o CRC ao fim de todo o cálculo
    							beq $t8,$t3,zera3
    							li $v0,1
    							lw $a0,resto($t8)
    							syscall
    							add $t8,$t8,4
    							j imprimeCRC
    								
    								zera3: # Zera registradores que precisaremos reutilizar
    								add $t8,$zero,$zero
    								add $t9,$t3,4
    								move $t1,$zero
    								sw $t1,resto($t3)
    								j concatenaUltimoZero
    								
    									concatenaUltimoZero: # Põe um zero adicional ao fim do CRC
    									beq $t8,$t9,fim
    									li $v0,1
    									lw $a0,resto($t8)
    									add $t8,$t8,4
    									syscall
    								
    										fim: # Encerra a execução
    										li $v0,10
    										syscall