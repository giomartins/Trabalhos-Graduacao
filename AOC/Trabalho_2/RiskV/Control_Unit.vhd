library IEEE;
use IEEE.std_logic_1164.all;

entity Control_Unit is
	port(
		OPCODE			: in std_logic_vector(6 downto 0) := (others => '0');
		FUNCT3			: in std_logic_vector(3 downto 0) := (others => '0');
		FUNCT7			: in std_logic_vector(6 downto 0) := (others => '0');
		
		MEMTOREG			: out std_logic := '0';
		MEMWRITE			: out std_logic := '0';
		BRANCH			: out std_logic := '0';
		ALUCONTROL		: out std_logic_vector(3 downto 0) := (others => '0'); -- Controlador da nossa ALU tem 4 bits
		ALUSRC			: out std_logic := '0';
		JUMP				: out std_logic := '0';
		REGWRITE			: out std_logic := '0';
		IMMSELECT		: out std_logic_vector(1 downto 0)
	);
end entity Control_Unit;