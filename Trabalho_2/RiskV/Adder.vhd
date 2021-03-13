-- Implementacao do Somador

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std_unsigned.all;

-- Definicao da entidade
entity Adder is
	port(
		input1		: in std_logic_vector(31 downto 0);
		input2		: in std_logic_vector(31 downto 0);
		output		: out std_logic_vector(31 downto 0);
	);
end entity adder;

-- Definicao da arquitetura
architecture arch_Adder of Adder is
begin
	output <= input1 + input2;
end arch_Adder;