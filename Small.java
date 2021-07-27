import java.util.*;
class Big extends Thread {
        public int predict; 

        public void run() {
            synchronized(this) {
                for (int i = 0; i<100; i++) 
                    predict++; 
                this.notifyAll();
            }
        }
    }

    public class Small implements Runnable {
        public static void main(String args[]) throws Exception {
            Thread t = new Thread(new Small());
            t.start();
            System.out.print("A");
            Big b1 = new Big();
            b1.start();
            synchronized(b1){
                b1.wait();
            }
            t.join();
            System.out.print("B");
            System.out.println(b1.predict);
        }
        public void run(){
            for(int i=0;i<3;i++)
            System.out.print(i);
        }
    }