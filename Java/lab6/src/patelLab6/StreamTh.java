package patelLab6;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class StreamTh implements Runnable {
	private Socket s;
	private int start;
	private int stop;
	private int[] result;
	private int prime;

	public StreamTh(Socket s, int str, int st, int[] r) {
		this.s = s;
		this.start = str;
		this.stop = st;
		this.result = r;
		this.prime = 0;
		System.out.println("StreamTh started");
	}

	public synchronized void printResult() {
		System.out.println(prime + " primes on interval [" + start + ", " + stop + "]");
	}

	public synchronized void addResult(int res) {
		this.result[0] += res;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream());
			ObjectInputStream ois = new ObjectInputStream(s.getInputStream());
			
			oos.writeObject(start);
			oos.writeObject(stop);
			
			prime = (int) ois.readObject();
			
			printResult();
			addResult(prime);
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
