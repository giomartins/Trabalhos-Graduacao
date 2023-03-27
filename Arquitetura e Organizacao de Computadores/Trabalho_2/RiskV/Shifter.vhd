library IEEE;
use IEEE.std_logic_1164.all;

entity Shifter_Left_2 is
	port(
		input		: in std_logic_vector(31 downto 0);
		output	: out std_logic_vector(31 downto 0)
	);
end entity Shifter_Left_2;

architecture arch_Shifter of Shifter_Left_2 is
begin
	output <= input(29 downto 0) & "00";
end;