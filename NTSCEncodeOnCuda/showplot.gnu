set datafile separator ","
plot 'test.csv' using 1:3 with lines,\
     'test.csv' using 1:4 with lines,\
     'test.csv' using 1:2 with lines
pause -1
