library IEEE;
use IEEE.std_logic_1164.all;

-- Multiplexador 2x1
entity Multiplexer is
	generic(width: integer := 8);
	port(
		input1	: in std_logic_vector(width - 1 downto 0);
		input2	: in std_logic_vector(width - 1 downto 0);
		selector : in std_logic;
		output	: out std_logic_vector(width - 1 downto 0)
	);
end entity Multiplexer;

architecture arch_Mux of Multiplexer is
begin
	y <= input2 when selector else input1;
end arch_Mux;