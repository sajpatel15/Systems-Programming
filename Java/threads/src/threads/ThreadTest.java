package threads;

public class ThreadTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		int n = 100;
		int[] a = new int[n];
		int[] b = new int[n];
		int[] c = new int[n];

		for (int i = 0; i < n; i++) {
			a[i] = i;
			b[i] = i;
		}

		int numThreads = 4;
		
		
		Thread[] ths = new Thread[numThreads];
		for (int i = 0; i < numThreads; i++) {

			int start = (n / numThreads) * i;
			int stop = (n / numThreads) * (i + 1);

			VecAdThread va = new VecAdThread(i, start, stop, a, b, c);
			Thread th = new Thread(va);

			ths[i] = th;
			th.start(); // fork
		}

		for (int i = 0; i < numThreads; i++) {
			try {
				ths[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}

		
//		try {
//			Thread.sleep(2000);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}

		for (int i = 0; i < n; i++) {
			System.out.println(c[i]);
		}
		
	}

}
