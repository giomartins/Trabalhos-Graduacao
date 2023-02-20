library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity Datapath is
	port(
		
	);
end entity;


architecture arch_Datapath of Datapath is
	-- ALU
	component Alu
		generic (
			W : integer := 32
		);
		port (
			CONTROL : in    std_logic_vector(3 downto 0);
			SRC1    : in    std_logic_vector(W - 1 downto 0);
			SRC2    : in    std_logic_vector(W - 1 downto 0);
			RESULT  : out   std_logic_vector(W - 1 downto 0);
			ZERO    : out   std_logic
		);
	end component;
	
	-- REGISTER FILE
	component Register_File
		port (
			RF_clk		: in std_logic;
			RF_we3		: in std_logic;
			RF_a1			: in std_logic_vector(4 downto 0);
			RF_a2			: in std_logic_vector(4 downto 0);
			RF_a3			: in std_logic_vector(4 downto 0);
			RF_wd3		: in std_logic_vector(31 downto 0);
			RF_rd1		: out std_logic_vector(31 downto 0);	
			RF_rd2		: out std_logic_vector(31 downto 0)
		);
	end component;
	
	-- DATA MEMORY
	component Data_Memory
		port (
			DM_clk	: in std_logic;
			DM_we		: in std_logic;
			DM_a		: in std_logic_vector(31 downto 0);
			DM_wd		: in std_logic_vector(31 downto 0);
			DM_rd		: out std_logic_vector(31 downto 0)
		);
	end component;
	
	-- INSTRUCTION MEMORY
	component Instruction_Memory
		port (
			A:  in std_logic_vector(32 downto 0);
			RD: out std_logic_vector(32 downto 0)
		);
	end component;
		
	-- PROGRAM COUNTER
	component Program_Counter
		port (
			PC_in		: in std_logic_vector(31 downto 0);
			PC_clk	: in std_logic;
			PC_rst	: in std_logic;
			PC_out	: out std_logic_vector(31 downto 0)
		);
	end component;
	
	-- MUX
	component Multiplexer 
		port (
			D0, D1: in STD_LOGIC_VECTOR(WIDTH-1 downto 0); 
			S: in STD_LOGIC; 
			Y: out STD_LOGIC_VECTOR(WIDTH-1 downto 0)
		);
	end component;
	
	-- SIGN EXTEND
	component Sign_Extend
		port (
			INPUT: in STD_LOGIC_VECTOR(WIDTH-1 downto 0); 
			OUTPUT: out STD_LOGIC_VECTOR(31 downto 0)
		);
	end component;
	

	-- Fazer a declaracao dos signals a partir daqui
	
end arch_Datapath;