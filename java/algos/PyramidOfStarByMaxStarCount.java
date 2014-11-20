import java.util.ArrayList;
import java.util.List;


class PyramidOfStarByMaxStarCount {  
	private void constructInvertAndDraw(int n) {
		System.out.println("Drawing pyramid of stars using buildAndInvert [n = " + n + "]");

		List<String> invertedPyramid = new ArrayList<String>();
		for (int i = n; i > 0; i = i - 2) {
			// Create initial space sequence
			StringBuffer row = new StringBuffer();
			for (int j = 0; j < (n - i) / 2; j++) {
				row.append(" ");
			}

			// Create the star sequence, there is no space sequence needed after the last star
			for (int k = 0; k < i; ++k) {
				row.append("*");
			}
			invertedPyramid.add(row.toString());
		}

		// Now print the inverted Pyramid in reverse traversal
		for (int i = invertedPyramid.size() - 1; i >= 0; --i) {
			System.out.println(invertedPyramid.get(i));
		}

		System.out.println();
	}

	private void drawDirect(int n) {
		System.out.println("Drawing pyramid of stars using drawDirect [n = " + n + "]");

		// If even the top level will be 2 stars or else will be 1 star
		int firstRowStarCount = ((n % 2) == 0 ? 2 : 1);

		for (int i = firstRowStarCount; i <= n; i = i + 2) {
			// Create initial space sequence, based on calculated values of empty spaces
			StringBuffer row = new StringBuffer();
			for (int j = 0; j < (((n - i) / 2)); j++) {
				row.append(" ");
			}

			// Create the star sequence, there is no space sequence needed after the last star
			for (int k = 0; k < i; ++k) {
				row.append("*");
			}
			System.out.println(row.toString());
		}
	}

	public static void main(String[] args) {
		// How does it behave for odd stars
		// How does it behave for even stars
		// What is 0 is passed
		PyramidOfStarByMaxStarCount p = new PyramidOfStarByMaxStarCount();
		p.drawDirect(5);
		p.constructInvertAndDraw(5);

		p.drawDirect(10);
		p.constructInvertAndDraw(10);

		p.drawDirect(15);
		p.constructInvertAndDraw(15);

		p.drawDirect(0);
		p.constructInvertAndDraw(0);

	}
}

