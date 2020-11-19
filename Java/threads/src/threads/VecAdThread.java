package threads;

public class VecAdThread implements Runnable {

	int start;
	int stop;
	int[] a;
	int[] b;
	int[] c;
	int tnum;
	
	public VecAdThread(int tnum, int start, int stop, int[] a, int[] b, int[] c) {
		this.start = start;
		this.stop = stop;
		this.a = a;
		this.b = b;
		this.c = c;
		this.tnum = tnum;
	}
	@Override
	public void run() {
		// TODO Auto-generated method stub
		// Vector addition
		System.out.println("In thread " + tnum + " " + start + " to " + stop);
		
		for(int i = start; i < stop; i++) {
			c[i] = a[i] + b[i];
		}
	}

}
