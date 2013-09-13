import csv
import math
import cmath

a_list = []

#reading the csv file
file_name = 'EEG_Data.csv'
with open(file_name, 'rt') as cfile:
    spamreader = csv.reader(cfile, delimiter=' ', quotechar='|')
    
    row_count = 0
    for row in spamreader:
        a_list.append( row[0].split(','))
        row_count += 1

    m = 22
    n = row_count

    x = [0]*m
    k = -1
    # K : deviation factor
    for j in range(0,m):
        for i in range(1,n):
            x[j] = x[j] + float(a_list[i][j])*cmath.exp(complex(0.0,-2*math.pi*i*k/n))
        print(x[j]/n)

    
    
        
   
        
