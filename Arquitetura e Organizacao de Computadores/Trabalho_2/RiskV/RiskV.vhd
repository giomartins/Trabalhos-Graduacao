-- Implementacao do Program Counter:

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_unsigned.all;

-- Definicao da entidade
entity RiskV is
	port(
		PC_In		: in std_logic_vector(31 downto 0);
		PC_clk	: in std_logic;
		PC_rst	: in std_logic;
		PC_out	: out std_logic_vector(31 downto 0)
	);
end entity RiskV;

-- Definicao da arquitetura
architecture arch_RiskV of RiskV is

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
end arch_riskV;