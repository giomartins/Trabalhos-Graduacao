import time
import numpy as np
from fklemint_pi_splx_norm import fkm_pi_splx_norm
from fklemint_pi_splx import fkm_pi_splx
from algpint_gf import algpint_01

# Main part of the script
if __name__ == "__main__":
    # Clear variables and warnings
    from warnings import filterwarnings
    filterwarnings("ignore")

    np.random.seed(42)

    # First call to the problem
    print('  ------------------------------------------------------')
    ndim = int(input('             Dimensão  do  espaço          =  '))
    print('  ------------------------------------------------------')

    # Construction of the optimization problem
    ncode = 1

    print('  ------------------------------------------------------')
    valb = float(input('      Define o vetor b (10 < valb < 100)   =  '))
    print('  ------------------------------------------------------')

    A, B, C, REL, XMIN, XMAX = fkm_pi_splx(ndim, ncode, valb)

    # Calculated rank of matrix A
    IRANK, IR, IC = np.linalg.matrix_rank(A), None, None

    # Number of linearly independent rows
    if IRANK < len(XMIN):
        print('  ------------------------------------------------------------')
        print('     Rank (A) < dim. vet X . The problem is not consistent.   ')
        print('  ------------------------------------------------------------')
    else:
        # Timing execution time
        start_time = time.time()

        # Define the first interior point near the origin
        Xini = (1.0e-11 + 1.0e-08 * np.random.rand(1)) * (XMAX / np.linalg.norm(XMAX))

        # Parameters for Interior Point
        gap = 1.0e-10
        Maxiter = 20 * ndim
        KALPHA = 0.95

        iter, EVOLX, EVOLFOBJ, Xsol_pi, FOBJ, yk, gap_final = algpint_01(
            A, B, C, REL, Xini, XMIN, XMAX, gap, KALPHA, Maxiter
        )

        Xsol = np.concatenate((np.zeros((ndim - 1)), [valb**(ndim-1)])).reshape(-1,1)
        
        print("Xsol ", Xsol)
        print("Xsol_pi ", Xsol_pi)
        print("FOBJ ", FOBJ)
        
        erro_xpi = 100 * np.linalg.norm(Xsol_pi - Xsol) / valb**(ndim - 1)
        erro_fobjpi = 100 * abs(FOBJ / (valb**(ndim - 1)) - 1)

        # Finishing timing
        end_time = time.time()
        elapsed_time = end_time - start_time

        print('  ----------------------------------------------------------------  ')
        print(f'  Theoretical number of iterations for the simplex is = {2**ndim}')
        print(f'  PI number of iterations is                          = {iter}')
        print(f'  PI erro porcentual optimal objective value is       = {erro_fobjpi}')
        print(f'  PI erro porcentual vetor x soluçao                  = {erro_xpi}')
        print('  -----------------------------------------------------------------  ')

        print(f'  Elapsed time is      = {elapsed_time:.6f}')