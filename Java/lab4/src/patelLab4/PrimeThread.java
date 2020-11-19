package patelLab4;

public class PrimeThread implements Runnable {

	int start;
	int stop;
	int result[];
	int tnum;

	public PrimeThread(int tnum, int start, int stop, int result[]) {
		this.start = start;
		this.stop = stop;
		this.tnum = tnum;
		this.result = result;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		System.out.println("In thread " + tnum + " " + start + " to " + stop);
		this.result[tnum] = primeRange(start, stop);	
		//System.out.println("Count: " + this.result);
	}

	public boolean isPrime(int p) {

		for (int i = 2; i < p / 2; i++) {

			if (p % i == 0) {
				//System.out.println(p + " is not a prime number");
				return false;
			}
		}
		//System.out.println(p + " is a prime number");
		return true;
	}

	public int primeRange(int start, int stop) {
		int count = 0;
		for (int i = start; i <= stop; i++) {
			if (isPrime(i)) {
				count++;
			}
		}
		
		return count;
	}

}
