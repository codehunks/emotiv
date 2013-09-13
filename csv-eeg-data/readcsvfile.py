import csv
import math
#reading the csv file
with open('eegs.csv', 'rt') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=' ', quotechar='|')
    a_list = []
    for row in spamreader:
        a_list.append( row[0].split(','))
        #change value of n to number of samples and m to number of columns in csv file
    m = 4
    n = 16
    x = [0]*m
    print ("RMS Corresponding to Engagement, Frustration, Meditation, Excitation are:")
    for j in range(0,m):
        for i in range(1,n):
            x[j] = x[j] + float(a_list[i][j]) * float(a_list[i][j])
         #square root ox x1
        x[j] = math.sqrt(x[j]/n)
        print(x[j])

    
    
        
   
        
