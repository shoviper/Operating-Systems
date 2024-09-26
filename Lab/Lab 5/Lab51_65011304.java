import java.util.Scanner;

class SummationThread extends Thread {
    private int number;
    private int result;

    public SummationThread(int number) {
        this.number = number;
    }

    public void run() {
        result = calculateSummation(2 * number);
    }

    public int getResult() {
        return result;
    }

    private int calculateSummation(int num) {
        int sum = 0;
        for (int i = 1; i <= num; i++) {
            sum += i;
        }
        return sum;
    }
}

public class SummationProgram {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        int number = scanner.nextInt();

        int parentSum = calculateSummation(number);

        SummationThread childThread = new SummationThread(number);
        childThread.start();

        try {
 
            childThread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

     
        int childSum = childThread.getResult();


        int finalResult = parentSum + childSum;

       
        System.out.println("Final result: " + finalResult);
    }

    private static int calculateSummation(int num) {
        int sum = 0;
        for (int i = 1; i <= num; i++) {
            sum += i;
        }
        return sum;
    }
}