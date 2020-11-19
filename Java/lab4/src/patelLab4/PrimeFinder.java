package patelLab4;

public class PrimeFinder {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
//		boolean a = isPrime(290);
//		
//		int b = primeRange(20, 50);
//		System.out.println(b);

		int range_start = 20;
		int range_stop = 50;
		int numThreads = 4;

		long start_time = System.currentTimeMillis();
		Thread[] ths = new Thread[numThreads];
		int diff_range = range_stop - range_start;
		int[] results = new int[numThreads];

		for (int i = 0; i < numThreads; i++) {

			int start = (int) (range_start + ((diff_range / numThreads) * i));
			if (start != range_start) {
				start++;
			}
			System.out.println("Start " + i + " : " + start);

			int stop = (int) (range_start + ((diff_range / numThreads) * (i + 1)));

			if ((stop + (diff_range / numThreads)) > range_stop) {
				stop = range_stop;
			}

			System.out.println("Stop " + i + " : " + stop);
			PrimeThread pt = new PrimeThread(i, start, stop, results);
			Thread th = new Thread(pt);
			ths[i] = th;
			th.start();
		}

		for (int i = 0; i < numThreads; i++) {

			try {
				ths[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		long stop_time = System.currentTimeMillis();

		int result = 0;

		for (int i = 0; i < results.length; i++) {
			result += results[i];
			System.out.println(results[i]);
		}

		System.out.println(result);
		System.out.println("Time for program to rum: " + (stop_time - start_time) + " ms.");

	}

	public static boolean isPrime(int p) {

		for (int i = 2; i < p / 2; i++) {

			if (p % i == 0) {
				System.out.println(p + " is not a prime number");
				return false;
			}
		}
		System.out.println(p + " is a prime number");
		return true;
	}

	public static int primeRange(int start, int stop) {
		int count = 0;
		for (int i = start; i < stop + 1; i++) {
			if (isPrime(i)) {
				count++;
			}
		}

		return count;
	}

}
