class PyramidOfStarByRowCount {  
	private void drawDirect(int n) {
		System.out.println("Drawing pyramid of stars [n = " + n + "]");

		for (int i = 1; i <= n; i++) {
			StringBuffer sb = new StringBuffer();
			// Add the prefix spaces needed for this level
			for (int j = 0; j < (n - i); j++) {
				sb.append(" ");
			}

			// Append all the needed stars for this level
			for (int j = 0; j < (2 * i - 1); j++) {
				sb.append("*");
			}
			System.out.println(sb.toString());
		}
	}

	public static void main(String[] args) {
		PyramidOfStarByRowCount p = new PyramidOfStarByRowCount();
		p.drawDirect(5);
		p.drawDirect(10);
		p.drawDirect(15);
		p.drawDirect(0);
	}
}
