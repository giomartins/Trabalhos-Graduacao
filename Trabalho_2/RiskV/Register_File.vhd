-- Implementacao do Register File

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;

-- Definicao da entidade
entity Register_File is
	port(
		RF_clk		: in std_logic;
		RF_we3		: in std_logic;
		RF_a1			: in std_logic_vector(4 downto 0);
		RF_a2			: in std_logic_vector(4 downto 0);
		RF_a3			: in std_logic_vector(4 downto 0);
		RF_wd3		: in std_logic_vector(31 downto 0);
		RF_rd1		: out std_logic_vector(31 downto 0);	
		RF_rd2		: out std_logic_vector(31 downto 0)
	);
end entity Register_File;

-- Definicao da arquitetura 
architecture arch_Register_File of Register_File is

	type memory is array(0 to 31) of std_logic_vector(31 downto 0);	-- Array de 32 registradores de 32 bits
	signal registers : memory;
	
begin
	process(RF_clk)
	begin
		if rising_edge(RF_clk) then
			if RF_we3 = '1' then 
				registers(to_integer(unsigned(RF_a3))) <= RF_wd3;
			end if;
		end if;
	end process;
	
	process(all)
	begin
		if (to_integer(unsigned(RF_a1)) = 0) then
			RF_rd1 <= X"00000000";
		else
			RF_rd1 <= registers(to_integer(unsigned(RF_a1)));
		end if;	
		if (to_integer(unsigned(RF_a2)) = 0) then
			RF_rd2 <= X"00000000";
		else
			RF_rd2 <= registers(to_integer(unsigned(RF_a2)));
		end if;
	end process;
end arch_Register_File;