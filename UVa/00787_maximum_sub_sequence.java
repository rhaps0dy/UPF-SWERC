import java.math.BigInteger;
import java.util.Scanner;

class Main {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		boolean beginning = true;

		BigInteger max, max_positive, max_negative;

		// get the compiler to shut up
		max = max_positive = max_negative = BigInteger.ZERO;

		while(in.hasNextInt()) {
			int n = in.nextInt();
			if(n == -999999) {
				System.out.println(max.toString());
				beginning = true;
			} else {
				BigInteger m = new BigInteger(Integer.toString(n));
				if(beginning) {
					beginning = false;
					max = max_positive = max_negative = m;
					continue;
				}
				BigInteger a = max_positive.multiply(m);
				BigInteger b = max_negative.multiply(m);

				max_positive = m;
				if(max_positive.compareTo(a) == -1)
					max_positive = a;
				if(max_positive.compareTo(b) == -1)
					max_positive = b;

				max_negative = m;
				if(a.compareTo(max_negative) == -1)
					max_negative = a;
				if(b.compareTo(max_negative) == -1)
					max_negative = b;

				if(max.compareTo(max_positive) == -1)
					max = max_positive;
			}
		}
	}
};
