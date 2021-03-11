-- Implementacao do Data Memory:

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity Data_Memory is
	port(
		DM_clk	: in std_logic;
		DM_we		: in std_logic;
		DM_a		: in std_logic_vector(31 downto 0);
		DM_wd		: in std_logic_vector(31 downto 0);
	);
end entity Data_Memory;

architecture arch_Data_Memory of Data_Memory is

end architecture arch_Data_Memory;	
