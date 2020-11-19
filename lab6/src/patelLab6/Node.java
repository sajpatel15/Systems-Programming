package patelLab6;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class Node {

	public static boolean isPrime(int p) {
		for (int i = 2; i < p / 2; i++) {

			if (p % i == 0) {
				// System.out.println(p + " is not a prime number");
				return false;
			}
		}
		// System.out.println(p + " is a prime number");
		return true;
	}

	public static int primeRange(int start, int stop) {
		int count = 0;
		for (int i = start; i <= stop; i++) {
			if (isPrime(i)) {
				count++;
			}
		}
		return count;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		try {
			System.out.println("About to call");
			Socket s = new Socket("localhost", 7000);
			System.out.println("Connected");

			ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream());
			ObjectInputStream ois = new ObjectInputStream(s.getInputStream());

			System.out.println("Reading objects");
			int start = (int) ois.readObject();
			int stop = (int) ois.readObject();
			System.out.println("Finished reading objects");

			System.out.println("Writing object");
			int prime = primeRange(start, stop);
			oos.writeObject(prime);
			System.out.println("Finished writing object");

			s.close();
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
