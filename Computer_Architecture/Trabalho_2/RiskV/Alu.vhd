library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Alu is
    generic (
        W       :       integer := 32
	);
    port (
        CONTROL : in    std_logic_vector(3 downto 0);
        SRC1    : in    std_logic_vector(W - 1 downto 0);
        SRC2    : in    std_logic_vector(W - 1 downto 0);
        RESULT  : out   std_logic_vector(W - 1 downto 0);
        ZERO    : out   std_logic
    );
end Alu;

architecture arch of Alu is
signal shift_aux, out_aux, result2 : std_logic_vector (w-1 downto 0);
constant All_zeros  : std_logic_vector(w-1 downto 0):= (others => '0');

begin
		
process (SRC1, SRC2, CONTROL)
begin
	shift_aux <= std_logic_vector(shift_left(signed(SRC2), to_integer(unsigned(SRC1))));
                out_aux <= X"00" & shift_aux(15 downto 0);
	
	
		
	case CONTROL is
		when "0000"  => result2 <=  std_logic_vector(unsigned(SRC1) + unsigned (SRC2));
		when "0001"  => result2 <= std_logic_vector(unsigned(SRC1) - unsigned (SRC2));		
		when "0010"  => result2 <= SRC1 and SRC2;
		when "0011"  => result2 <= SRC1 xor SRC2;
		when "0100"  => result2 <= out_aux;
		when "0101"  => result2 <= SRC1;
		when "0101"  => result2 <= SRC2;
		
		when others => result2 <= All_zeros;
	end case;
	
	if result2 =All_zeros then
		ZERO <= '1';
	else
		ZERO <='0';
	end if;
		 
end process;
		
		 RESULT <= result2;
		
end arch;

