String regex = BuildRegex();
	Pattern pattern = Pattern.compile (regex);
	
	Scanner s = new Scanner(System.in);

pattern.matcher(removed_period).find() // Boolean

// Matcher documentation
/* Matcher has an internal index, and find() finds the next instance
   of the pattern. */
// int start(): Returns the start index of the previous match.
// int end(): Returns the offset after the last character matched.
/* boolean find(int start): Resets this matcher and then attempts to
   find the next subsequence of the input sequence that matches the
   pattern, starting at the specified index. */
/* boolean matches(): Attempts to match the entire region against the
   pattern. */
// String replaceAll(String replacement)
// String replaceFirst(String replacement)
