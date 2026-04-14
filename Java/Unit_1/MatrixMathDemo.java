package Unit_1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class MatrixMathDemo {

    public static void main(String[] args) {
        String fileName = "resources/matrices.txt";

        try {
            Scanner sc = new Scanner(new File(fileName));

            // a. Read two matrices from file
            int[][] matrixA = readMatrix(sc);
            int[][] matrixB = readMatrix(sc);
            sc.close();

            System.out.println("Matrix A:");
            displayMatrix(matrixA);
            System.out.println("\nMatrix B:");
            displayMatrix(matrixB);

            // b. Perform matrix addition
            System.out.println("\n--- Performing Addition ---");
            try {
                int[][] sum = add(matrixA, matrixB);
                displayMatrix(sum);
            } catch (IllegalArgumentException e) {
                System.out.println("Error: " + e.getMessage());
            }

            // c. Perform matrix multiplication
            System.out.println("\n--- Performing Multiplication ---");
            try {
                int[][] product = multiply(matrixA, matrixB);
                displayMatrix(product);
            } catch (IllegalArgumentException e) {
                System.out.println("Error: " + e.getMessage());
            }

        } catch (FileNotFoundException e) {
            System.out.println("Error: matrices.txt was not found.");
        }
    }

    // Helper to read a matrix from scanner format (rows cols data...)
    private static int[][] readMatrix(Scanner sc) {
        if (!sc.hasNextInt()) return null;
        int r = sc.nextInt();
        int c = sc.nextInt();
        int[][] m = new int[r][c];
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                m[i][j] = sc.nextInt();
            }
        }
        return m;
    }

    // d. Handle invalid dimensions using exception (Addition)
    private static int[][] add(int[][] a, int[][] b) {
        if (a.length != b.length || a[0].length != b[0].length) {
            throw new IllegalArgumentException("Dimension mismatch! Matrices must be the same size for addition.");
        }
        int rows = a.length, cols = a[0].length;
        int[][] res = new int[rows][cols];
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res[i][j] = a[i][j] + b[i][j];
            }
        }
        return res;
    }

    // d. Handle invalid dimensions using exception (Multiplication)
    private static int[][] multiply(int[][] a, int[][] b) {
        if (a[0].length != b.length) {
            throw new IllegalArgumentException("Dimension mismatch! Columns of A must match rows of B.");
        }
        int rA = a.length, cA = a[0].length, cB = b[0].length;
        int[][] res = new int[rA][cB];
        for (int i = 0; i < rA; i++) {
            for (int j = 0; j < cB; j++) {
                for (int k = 0; k < cA; k++) {
                    res[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return res;
    }

    // e. Display result
    private static void displayMatrix(int[][] m) {
        for (int[] row : m) {
            for (int val : row) {
                System.out.printf("%4d ", val);
            }
            System.out.println();
        }
    }
}
