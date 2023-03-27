library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Instruction_Memory is
    port(
        A:  in std_logic_vector(32 downto 0);
        RD: out std_logic_vector(32 downto 0)
    );
    end entity;
    
architecture Behavior of Instruction_Memory is
    constant rom_depth : natural := 32;
    constant rom_width : natural := 32;
    
    type rom_type is array (0 to rom_depth - 1)
    of std_logic_vector(rom_width - 1 downto 0);

    signal rom: rom_type;

    attribute ram_init_file : string;
    attribute ram_init_file of rom :
    signal is "instructions.hex";

begin

    READ: process(A)
    begin
		  if (unsigned(A) < rom_depth) then
		     RD <= rom(to_integer(unsigned(A)));
		  else
		     RD <= (others => '0');
		  end if;
    end process;


end Behavior;