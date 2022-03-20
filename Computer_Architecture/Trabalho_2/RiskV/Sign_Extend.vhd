library IEEE; 
use IEEE.STD_LOGIC_1164.all; 
entity Signal_Extend is 
    generic(WIDTH: natural := 32); 
    port(
        INPUT: in STD_LOGIC_VECTOR(WIDTH-1 downto 0); 
        OUTPUT: out STD_LOGIC_VECTOR(31 downto 0)
    ); 
end; 

architecture behave of Signal_Extend is 
begin 
    OUTPUT <= (31 downto WIDTH => '1') & INPUT when INPUT(WIDTH-1) ='1'
	 else (31 downto WIDTH => '0') & INPUT;
end;