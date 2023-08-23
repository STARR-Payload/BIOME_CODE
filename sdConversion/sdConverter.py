#import numpy as np
import matplotlib.pyplot as plt
import csv


#elapsedTime = 0,
#valveOneTemp, valveTwoTemp, valveThreeTemp, valveFourTemp, 
#SPGCO2, SPGEth, SPGVTOL, SPGH2, 
#ACCELx, ACCELy, ACCELz, GYROx, GYROy, GYROz, 
#BMETemp, BMEHumidity, BMEPressure, 
#LIS3MDLcoorX, LIS3MDLcoorY, LIS3MDLcoorZ,
#Valve


f = open("demofile.txt", "r")
#print(f.readline())

x = csv.reader(f.readline())
print(list(x))