package sockets;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server{
	public static void main(String[] args) {
		
		try {
			ServerSocket ss = new ServerSocket(7000);

			while(true) {
				System.out.println("Waiting for a call");
				Socket s = ss.accept(); // blocking
				System.out.println("Accepted");

				ObjectInputStream ois = new ObjectInputStream(s.getInputStream());
				ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream());

				int x = (int)ois.readObject();
				x = x * 2;
				
				oos.writeObject(x);
				
			}
			
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	
}