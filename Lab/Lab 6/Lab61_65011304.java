class Multiplier extends Thread {
    private int[][] multiplicand;
    private int[][] multiplier;
    private int row;
    private int col;
    private int result;

    public Multiplier(int[][] multiplicand, int[][] multiplier, int row, int col) {
        this.multiplicand = multiplicand;
        this.multiplier = multiplier;
        this.row = row;
        this.col = col;
    }

    @Override
    public void run() {
        result = 0;
        for (int i = 0; i < multiplier.length; i++) {
            result += multiplicand[row][i] * multiplier[i][col];
        }
    }

    public int getResult() {
        return result;
    }
}

public class Inthat_Lab61 {
    public static void main(String[] args) {
        int[][] multiplicand = {
            {5, 6, 7},
            {4, 8, 9}
        };

        int[][] multiplier = {
            {6, 4},
            {5, 7},
            {1, 1}
        };

        int rows = multiplicand.length;
        int cols = multiplier[0].length;
        Multiplier[][] threads = new Multiplier[rows][cols];

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                threads[i][j] = new Multiplier(multiplicand, multiplier, i, j);
                threads[i][j].start();
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                try {
                    threads[i][j].join();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }

        int[][] resultMatrix = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                resultMatrix[i][j] = threads[i][j].getResult();
            }
        }

        System.out.println("Result matrix:");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                System.out.print(resultMatrix[i][j] + " ");
            }
            System.out.println();
        }
    }
}