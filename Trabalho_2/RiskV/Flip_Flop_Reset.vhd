library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity Flip_Flop_Reset is
	generic (width: integer);
	port(
		clock		: in std_logic;
		reset		: in std_logic;
		input		: in std_logic_vector(width-1 downto 0);
		output 	: out std_logic_vector(width-1 downto 0);
	);
end entity Flip_Flop_Reset;

architecture arch_Flip_Flop of Flip_Flop_Reset is
begin
	process(clock, reset)
	begin
		if reset then 
			output <= (others => '0');
		elsif rising_edge(clock) then
			output <= input;
		end if;
	end process;
end;
