library IEEE; 
use IEEE.STD_LOGIC_1164.all; 
entity Mux2 is 
    generic(WIDTH: integer := 32); 
    port(
        D0, D1: in STD_LOGIC_VECTOR(WIDTH-1 downto 0); 
        S: in STD_LOGIC; 
        Y: out STD_LOGIC_VECTOR(WIDTH-1 downto 0)
    ); 
end; 
architecture behave of Mux2 is 
    begin Y <= D1 when S = '1' else D0; 
end;