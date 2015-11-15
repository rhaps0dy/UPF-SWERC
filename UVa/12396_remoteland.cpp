#include <stdio.h>

#define ULL unsigned long long
#define M 1000000007 // days in a year

ULL v[1000001], k = 0;

// Explicacion del problema
// - El dia pedido es el mas grande tal que se puede formar
//   como producto de distintos numeros <= n
//	  --> De aquí viene la idea de hacer algo como un factorial
// - El dia es un cuadrado perfecto: e.g. 9 = 3^2
// - Recordar que cualquier numero puede descomponerse como producto
//   de numeros primos
//    --> Para tener un cuadrado perfecto, necesitamos que la descomposicion
//        del factorial que tenga los numeros primos elevados a una potencia
//        par.
//    --> e.g. n = 10 --> 2*3*4*5*6*7*8*9*10 --> 2^8 * 3^4 * 5^2 * 7
//        el 7 no interesa porque tiene potencia impar --> 2^8 * 3^4 * 5^2
//        esto es un cuadrado perfecto ya que: 2^8 * 3^4 * 5^2 = (2^4 * 3^2 * 5^1)^2

// Podriamos usar la funcion pow pero tendremos un overflow
// en la capacidad del ULL
ULL expo(ULL b, ULL e)
{
	if (e == 0) return 1;
	ULL m = expo(b, e / 2);
	if (e % 2) return m * m % M * b % M;
	else return m * m % M;
}

int main()
{
	// Generar array de primos
	v[k++] = 2;

	for (ULL i = 3; i <= 5000020; i += 2)
	{
		bool b = true;
		for (ULL j = 0; b && v[j] * v[j] <= i; j++)
		{
			b = i%v[j] > 0;
		}

		if (b) v[k++] = i;
	}

	ULL n = 0;

	while (1)
	{
		scanf("%lld", &n);

		if (n == 0) break;

		ULL result = 1;

		// Esencial: http://www.cut-the-knot.org/blue/LegendresTheorem.shtml
		for (ULL i = 0; 2 * v[i] <= n; ++i)
		{
			long long num = 0;

			// Si v[i] = 2, haremos el calculo con 2, 4, 8, 16, 32, ...
			// Estos seran los valores de e
			ULL e = v[i];

			while (e <= n) // Aplicar la formula de la url
			{
				num += n / e;
				e *= v[i];
			}

			if (num % 2 != 0) // Solo nos interesan las potencias pares
			{
				--num;
			}

			// Los habitantes de remoteland quieren los anios no los dias
			result = result * expo(v[i], num) % M;
		}

		printf("%lld\n", result);
	}

	return 0;
}