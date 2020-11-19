package patelLab6;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Head {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			int range_start = 1000;
			int range_stop = 1000000;
			int numThreads = 5;
			int diff_range = range_stop - range_start;
			int result[] = new int[1];

			Thread[] ths = new Thread[numThreads];
			ServerSocket ss = new ServerSocket(7000);
			Socket s[] = new Socket[numThreads];

			for (int i = 0; i < s.length; i++) {
				System.out.println("Waiting for connection");
				s[i] = ss.accept();
				System.out.println("Accepting connection");
			}
			System.out.println("Starting threads");
			for (int i = 0; i < numThreads; i++) {
				int start = ((diff_range / numThreads) * i) + range_start;
				int stop = ((diff_range / numThreads) * (i + 1)) + range_start;

				StreamTh sth = new StreamTh(s[i], start, stop, result);

				Thread th = new Thread(sth);
				ths[i] = th;
				th.start();
				System.out.println("Started thread: " + i);
			}

			for (int i = 0; i < numThreads; i++) // wait
			{
				try {
					System.out.println("Joining thread: " + i);
					ths[i].join();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}

			System.out.println(result[0] + " primes on [" + range_start + "," + range_stop + "]");

			for (int i = 0; i < numThreads; i++) {

				System.out.println("Closing thread: " + i);
				s[i].close();
			}
			ss.close();

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
