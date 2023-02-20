-- Implementacao do Data Memory:

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_unsigned.all;
use IEEE.numeric_std.all;
use std.textio.all;

entity Data_Memory is
	port(
		DM_clk	: in std_logic;
		DM_we		: in std_logic;
		DM_a		: in std_logic_vector(31 downto 0);
		DM_wd		: in std_logic_vector(31 downto 0);
		DM_rd		: out std_logic_vector(31 downto 0)
	);
end entity Data_Memory;


architecture arch_Data_Memory of Data_Memory is
begin
	process is
		type ramtype is array(63 downto 0) of std_logic_vector(31 downto 0);
		variable mem : ramtype;
		
	begin	-- read or write memory
		loop
			if rising_edge(DM_clk) then
				if (DM_we = '1') then
					mem(to_integer (unsigned (DM_a(7 downto 0)))) := DM_wd;
				end if;
			end if;
			DM_rd <= mem (to_integer(unsigned(DM_a(7 downto 2))));
			wait on DM_clk, DM_a;
		end loop;
	end process;
end architecture arch_Data_Memory;	
