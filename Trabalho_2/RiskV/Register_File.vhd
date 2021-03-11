-- Implementacao do Register File

-- Chamada das bibliotecas
library IEEE;
use IEEE.std_logic_1164.all;
use IEE.std_logic_unsigned.all;

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
		RF_rd2		: out std_logic_vector(31 downto 0);
	);
end entity Register_File;

-- Definicao da arquitetura 
architecture arch_Register_File of Register_File is

	type Memory is array(0 to 31) of std_logic_vector(31 down to 0);	-- Array de 32 registradores de 32 bits
	signal registradores : Memory := (others => (others => '0'));
	
	begin
		process(RF_clk, RF_we3, RF_a1, RF_a2, RF_a3, RF_w3, registradores)
			if rising_edge(RF_clk) then
				if RF_we3 = '1' and RF_a3 /= "00000" then					-- Verifica se o Write Enable esta habilitado e a diferenca de enderecos e zero
					registradores(conv_integer(RF_a3)) <= RF_w3;
				end if;
			end if;
		end process;
		
		-- Escrita assincrona das saidas rd1 e rd2
		RF_rd1 <= registradores(conv_integer(RF_a1)) when RF_a1 /= "00000" else (others => '0');
		RF_rd2 <= registradores(conv_integer(RF_a2)) when RF_a2 /= "00000" else (others => '0');
		

end arch_Register_File;