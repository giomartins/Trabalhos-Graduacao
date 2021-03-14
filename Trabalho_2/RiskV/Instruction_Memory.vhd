-- Implementacao do Instruction Memory

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_unsigned.all;

-- Definicao da entidade
entity Instruction_Memory is
	port(
		IM_a		: in std_logic_vector(31 downto 0);
		IM_rd		: out std_logic_vector(31 downto 0)
	);
end entity Instruction_Memory;

-- Definicao da arquitetura 
architecture arch_Instruction_Memory of Instruction_Memory is
begin
	IM_rd <= IM_a;

end architecture arch_Instruction_Memory;