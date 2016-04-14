# APUE

1) notice :

very wired :  (if we don't add -lpthread to the compiler, the program can terminate without being blocked by condition)
xiachsh@xiachsh-ThinkPad-X201:/data/learning/github/APUE$ gcc -g -o bq_test bq_test.c 
xiachsh@xiachsh-ThinkPad-X201:/data/learning/github/APUE$ ./bq_test 
Iteration :0
return from bq_get
Iteration :1
return from bq_get
Iteration :2
return from bq_get
Iteration :3
return from bq_get
Iteration :4
	
xiachsh@xiachsh-ThinkPad-X201:/data/learning/github/APUE$ gcc -g -o bq_test bq_test.c -lpthread
xiachsh@xiachsh-ThinkPad-X201:/data/learning/github/APUE$ ./bq_test 
Iteration :0

^C
xiachsh@xiachsh-ThinkPad-X201:/data/learning/github/APUE$ 
