-- Implementacao do Somador

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

-- Definicao da entidade
entity Adder is
	port(
		input1		: in std_logic_vector(31 downto 0);
		input2		: in std_logic_vector(31 downto 0);
		output		: out std_logic_vector(31 downto 0)
	);
end entity adder;

-- Definicao da arquitetura
architecture arch_Adder of Adder is

signal aux : unsigned;

begin
	aux <= unsigned (input1) + unsigned (input2);
	output <= std_logic_vector(aux);
end arch_Adder;