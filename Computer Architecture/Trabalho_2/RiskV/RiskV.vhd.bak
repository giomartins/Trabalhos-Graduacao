-- Implementacao do Program Counter:

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_unsigned.all;

-- Definicao da entidade
entity Program_Counter is
	port(
		PC_In		: in std_logic_vector(31 downto 0);
		PC_clk	: in std_logic;
		PC_rst	: in std_logic;
		PC_out	: out std_logic_vector(31 downto 0);
	);
end entity Program_Counter;

-- Definicao da arquitetura
architecture arch_Program_Counter of Program_Counter is

begin
	process(PC_clk, PC_rst)
	begin
		if PC_rst = '0' then
			PC_out <= (others => '0');
		else
			if rising_edge(PC_clk) then
				PC_out <= PC_In;
			end if;
		end if;
	end process;
end arch_Program_Counter