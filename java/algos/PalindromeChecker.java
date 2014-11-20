import java.util.*;

class PalindromeChecker {
	private boolean isValidUsingTwoWayTraverse(String str) {
		boolean isSame = true;
		for (int fIndex = 0, bIndex = (str.length() - 1); fIndex < bIndex && isSame; ++fIndex, --bIndex) {
			isSame = (str.charAt(fIndex) == str.charAt(bIndex));
		}
		return isSame;
	}

	private boolean isValidUsingReverseCompare(String str) {
		String revStr = new StringBuffer(str).reverse().toString();
		return str.equals(revStr);
	}

	public static void main(String args[]) {
		if (args.length < 1) {
			System.err.println("No input found on invocation");
			System.err.println("Usage: <program> <string> [<string>....]");
		}

		PalindromeChecker pc = new PalindromeChecker();
		for (int i = 0; i < args.length; ++i) {
			// How does it work for odd length string
			// How does it work for event length string
			// How does it work for empty string
			System.out.println("IsPalindrome [\"" + args[i] + "\"] => {UsingReverseCompare: " + pc.isValidUsingReverseCompare(args[i])
					+ ", UsingTwoWayTraverse: " + pc.isValidUsingTwoWayTraverse(args[i]) + "}");
		}
	}
}	
