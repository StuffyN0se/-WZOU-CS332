Compiled using gcc -o HW04 HW04.c -lpthread
In child process inserted a delay due to rare case of child process reading numbers faster than 
parent process is writing to the pipe, leading to missing number/ weird averages.