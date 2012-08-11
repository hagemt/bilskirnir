package edu.rpi.sdd.hagemt;

/**
 * Main class for composition example code
 * @author Tor E Hagemann <hagemt@rpi.edu>
 */
public class CompositeExample {
	/**
	 * A Book is an amalgamation of its Text(s)
	 */
	private static class Book extends Tree<String> {
		private boolean valid = false;
		private String cache;
		
		@Override
		public boolean addChild(Composite<String> e) {
			if (super.addChild(e)) {
				valid = false;
				return true;
			}
			return false;
		}
		
		@Override
		public boolean removeChild(Composite<String> e) {
			if (super.removeChild(e)) {
				valid = false;
				return true;
			}
			return false;
		}

		@Override
		public String toString() {
			if (!valid) {
				// The parentheses make the nesting more clear
				StringBuilder sb = new StringBuilder();
				// sb.append("( ");
				for (Composite<String> s : elements) {
					sb.append(s.toString());
					sb.append(' ');
				}
				// sb.append(")");
				cache = sb.toString();
				valid = true;
			}
			return cache;
		}
	}
	
	public static void main(String... args) {
		// A Book composed of Texts
		Book book1 = new Book();
		book1.addChild("this");
		book1.addChild("is");
		book1.addChild("an");
		book1.addChild("example");
		System.out.println("String 1: " + book1);
		
		// A Book containing a Book
		Book book2 = new Book();
		book2.addChild(book1);
		System.out.println("String 2: " + book2);
		
		// A Book containing both
		Book book3 = new Book();
		book3.addChild(book2);
		book3.addChild("example");
		// Gotcha? Nope. Try it.
		book3.addChild(book3);
		System.out.println("String 3: " + book3);
	}
}
