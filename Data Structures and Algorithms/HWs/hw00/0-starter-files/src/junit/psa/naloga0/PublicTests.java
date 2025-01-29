package psa.naloga0;

import junit.framework.TestCase;

public class PublicTests extends TestCase {
	Naloga bloom; // Bloom filter instance

	// This method is run before each test. It initializes the Bloom filter with size 255 and 4 hash functions.
	protected void setUp() throws Exception {
		bloom = new Naloga(255, 4);
	}

	// Test whether adding the element 'test' results in the correct bits being set in the bit array
	public void testAddElement() {
		bloom.add("test");

		// Loop through the bit array and check that the expected bits are set to true
		for (int i = 0; i < bloom.podatki.length; i++) {
			if (i == 152 || i == 57 || i == 103 || i == 185) { // These are expected positions
				assertTrue(bloom.podatki[i]); // The bit should be true at these positions
			} else {
				assertFalse(bloom.podatki[i]); // The bit should remain false at all other positions
			}
		}
	}

	// Test whether the Bloom filter correctly identifies if elements are present or not
	public void testContainsElement() {
		bloom.add("test"); // Add the string "test" to the filter
		assertTrue(bloom.contains("test")); // "test" should be found in the filter
		assertFalse(bloom.contains("test2")); // "test2" should not be found in the filter
	}
}
