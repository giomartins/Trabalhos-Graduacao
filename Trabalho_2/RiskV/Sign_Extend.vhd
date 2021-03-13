-- Implementacao do Sign Extend

-- Chamada das Bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;

-- Definicao da entidade
entity Sign_Extend is
	port(
		input		: in std_logic_vector(15 downto 0);
		output		: out std_logic_vector(31 downto 0);
	);
end entity Sign_Extend;

-- Definicao da arquitetura
architecture arch_Sign_Extend of Sign_Extend is
begin
	output <= X"ffff" & input when input(15) else X"0000" & input;

end arch_Sign_Extend;