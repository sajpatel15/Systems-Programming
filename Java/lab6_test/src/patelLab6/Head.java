package patelLab6;

import java.io.*;
import java.net.*;

public class Head {

   public static void main(String[] args) {
      try {
         int numThreads = 5;
         int startRange = 10;
         int stopRange = 100;
         int n = stopRange - startRange;
         int result[] = new int[1]; 
         result[0]= 0;
         Thread[] ths = new Thread[numThreads];
         ServerSocket ss = new ServerSocket(8000);
         Socket s[] = new Socket[numThreads];
         for (int i = 0; i<s.length; i++)
         {
            System.out.println("Waiting for connection");
            s[i] = ss.accept();
            System.out.println("Node " + i + " Accepted");
         }
         for (int i = 0; i<numThreads; i++)
         {
            int start = ((n/numThreads)*i)+startRange;
            int stop = ((n/numThreads)*(i+1))+startRange;
            StreamTh sth = new StreamTh(s[i], start, stop, result);
            Thread th = new Thread(sth);
            ths[i] = th;
            th.start();
         }
         for (int i=0; i<numThreads; i++) // wait
         {
            try {
               ths[i].join();
            } catch (InterruptedException e) {
            	// TODO Auto-generated catch block
               e.printStackTrace();
            } // blocking operation
         }
         System.out.println(result[0] + " prime on [" + startRange +"," + stopRange + "]");
         for (int i = 0; i<numThreads; i++)
         {
            s[i].close();
         }
         ss.close();
      } catch (IOException e) {
      	// TODO Auto-generated catch block
         e.printStackTrace();
      } 
   
   }

}
