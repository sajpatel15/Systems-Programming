package patelLab6;

import java.io.*;
import java.net.*;

public class StreamTh implements Runnable{
	
   private Socket s;
   private int start;
   private int stop;
   private int[] result;
   private int prime;
	
   public StreamTh(Socket s, int start, int stop, int[] result)
   {
      this.s = s;
      this.start = start;
      this.stop = stop;
      this.result = result;
      prime = 0;
   }
	
   public synchronized void printResult()
   {
      System.out.println(prime + " prime on [" + start + ", " + stop + "]");
   }
	
   public synchronized void addToResult(int localResult)
   {
      result[0]+=localResult;
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
         addToResult(prime);
      	
      } catch (IOException e) {
      	// TODO Auto-generated catch block
         e.printStackTrace();
      } catch (ClassNotFoundException e) {
         e.printStackTrace();
      }
   }

}
