import java.io.BufferedReader;
import java.io.InputStreamReader;

import static java.lang.Integer.parseInt;
import static java.lang.Math.min;
import static java.lang.Math.max;

public class Palindromes {
	private static int[] daysInMonth;
	static {
		daysInMonth = new int[] { 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	}

	private static String reversed(String s) {
		StringBuilder sb = new StringBuilder(s);
		sb.reverse();
		return sb.toString();
	}

	private static boolean hasValidDate(String year) {
		while (year.length() < 4) {
			year = '0' + year;
		}
		assert (year.length() == 4);
		int m = 0, d = 0;
		StringBuilder sb = new StringBuilder();
		try {
			m = parseInt(year.substring(0, 2));
			d = parseInt(year.substring(2, 4));
		} catch (NumberFormatException nfe) {
			return false;
		}
		return !(m < 1 || m > 12 || d < 1 || d > daysInMonth[m - 1]);
	}

	private static void printAllBetween(int y1, int y2) {
		assert (y1 <= y2);
		for (int y = y1; y <= y2; ++y) {
			String year = Integer.toString(y);
			daysInMonth[2] = (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) ? 29 : 28;
			if (hasValidDate(year)) {
				System.out.println(reversed(year) + year);
			}
		}
	}

	/**
	 * Epic Question 1 -- Palindromes
	 */
	public static void main(String... args) {
		try (BufferedReader reader =
				new BufferedReader(new InputStreamReader(System.in))) {
			System.out.print("Please enter a year: ");
			String input1 = reader.readLine();
			System.out.print("Please enter another year: ");
			String input2 = reader.readLine();
			try {
				int year1 = parseInt(input1);
				int year2 = parseInt(input2);
				printAllBetween(min(year1, year2), max(year1, year2));
			} catch (NumberFormatException nfe) {
				nfe.printStackTrace();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
