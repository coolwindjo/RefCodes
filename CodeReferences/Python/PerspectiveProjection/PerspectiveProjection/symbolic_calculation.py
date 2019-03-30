# -*- coding: utf-8 -*-
##  @package Homography
#   Documentation for this module
#
#   More details
import sys
import numpy as np
import sympy as sp

class SymbolicCalcuation(object):
    """A class for making a homography matrix"""
    
    def __init__(self, *args, **kwargs):
        return super(SymbolicCalcuation, self).__init__(*args, **kwargs)
    
    def test(self):

        try:
            print("sp.solve_linear")

        except :
            print("[Error] Unexpected error at test().", sys.exc_info()[0])

        return 


    def RPYTest(self):

        try:
            phi, theta, psi = sp.symbols('Roll Pitch Yaw')
            Cph = sp.cos(phi)
            Sph = sp.sin(phi)

            Cth = sp.cos(theta)
            Sth = sp.sin(theta)

            Cps = sp.cos(psi)
            Sps = sp.sin(psi)

            # Solution Matrix
            CphSps = Cph*Sps
            SphSps = Sph*Sps
            CphCps = Cph*Cps
            SphCps = Sph*Cps
            M = sp.Matrix([[Cps*Cth, Sps*Cth, -Sth], 
                            [(SphCps*Sth) - CphSps, (SphSps*Sth) + CphCps, Sph*Cth],
                            [(CphCps*Sth) + SphSps, (CphSps*Sth) - SphCps, Cph*Cth]])

            print(M)

            R_roll = sp.Matrix([[1, 0, 0], 
                                [0, Cph, -Sph],
                                [0, Sph, Cph]])
            R_pitch = sp.Matrix([[Cth, 0, Sth], 
                                [0, 1, 0],
                                [-Sth, 0, Cth]])
            R_yaw = sp.Matrix([[Cps, -Sps, 0], 
                                [Sps, Cps, 0],
                                [0, 0, 1]])
            R_rpy = R_roll*R_pitch*R_yaw
            print(R_rpy)
            R_ypr = R_yaw*R_pitch*R_roll
            print(R_ypr)
            R_pry = R_pitch*R_roll*R_yaw
            print(R_pry)
        except :
            print("[Error] Unexpected error at RPYTest().", sys.exc_info()[0])

        return 

def main():
    
    import symbolic_calculation

    try:
        sc = symbolic_calculation.SymbolicCalcuation()
        #sc.RPYTest()

    except :
        print("[Error] Unexpected error at main().", sys.exc_info()[0])

    return

if __name__ == "__main__":
    main()