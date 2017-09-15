unsigned int factorial (unsigned int n){
	unsigned int f = 1;


		for(int i = 1; i <= n ; i++)
		{
			f = f*i;
		}

		return f;
}


double power (double base, unsigned int n){

	double p=1;

	for(int i = 0; i < n; i++)
	{
		p = p*(base);
	}
	return p;
}
unsigned int fibonacci (unsigned int n){

	unsigned int fib = 0;
	unsigned int a = 0;
	unsigned int b = 1;

	if(n>=3)
	{
		for(int i = 1; i < n; i++)
		{

			fib = a + b;
			a = b;
			b = fib;
		}
	}else if(n == 1 || n == 2)
	{
		return 1;
	}
	return fib;
}
