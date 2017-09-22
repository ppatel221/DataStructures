unsigned int factorial (unsigned int n){

	if(n>1)
	{
		return n * factorial(n-1);
	}else
	{
		return 1;
	}

}

double power (double base, unsigned int n){

	if(n>0)
	{
		return (base * power(base ,n-1));
	}else
	{
		return 1;
	}	
}
unsigned int fibonacci (unsigned int n){

	if(n > 2)
	{
		return fibonacci(n-1) + fibonacci(n-2);
	
	}else if(n == 1 || n == 2)
	{
		return 1;
	
	}else if(n == 0)
	{
		return 0;
	}	
}
