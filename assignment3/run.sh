chmod +x run.sh

gcc -pthread -o test problem_1.c
taskset -c 1 ./problem_1 4 50
taskset -c 1 ./problem_1 3 50

gcc -pthread -o test problem_2.c
taskset -c 1 ./problem_2 4 50
taskset -c 1 ./problem_2 3 50

gcc -pthread -o test problem_3.c
./problem_3 4 20
./problem_3 6 20
./problem_3 8 20

gcc -pthread -o test problem_4.c
./problem_4 3 30
./problem_4 5 30

gcc -pthread -o test problem_5.c
./problem_5 3 30
./problem_5 5 30

gcc -pthread -o test problem_6.c
./problem_6 3 100
./problem_6 2 100

#!/bin/sh 
read -p "Press Enter to continue: "
echo continue