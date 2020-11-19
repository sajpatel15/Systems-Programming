package patelLab6;

import java.io.*;
import java.net.*;

public class Node{
	
   public static boolean isPrime(int number)
   {
      int i = 2;
      while(number%i!=0)
      {
         i++;
      }
      if (i==number)
      {
         return true;
      }
      else
      {
         return false;
      }
   }
	
   public static int howManyPrime(int start, int stop)
   {
      int prime = 0;
      for (int i = start; i<stop; i++)
      {
         if (isPrime(i))
         {
            prime++;
         }
      }
      return prime;
   }

   public static void main(String[] args) {
   	// TODO Auto-generated method stub
      try {
         Socket s = new Socket("localhost", 8000); 
         ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream());
         ObjectInputStream ois = new ObjectInputStream(s.getInputStream());
         int start = (int)ois.readObject();
         int stop = (int)ois.readObject();
         int prime = howManyPrime(start,stop);
         oos.writeObject(prime);
         s.close();
      } catch (IOException e) {
      	// TODO Auto-generated catch block
         e.printStackTrace();
      } catch (ClassNotFoundException e) {
      	// TODO Auto-generated catch block
         e.printStackTrace();
      }
   }


}
