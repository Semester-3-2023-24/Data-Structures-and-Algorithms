package psa.naloga0;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Naloga {
	boolean[] podatki;
	String hashName = "MD5";
	final MessageDigest digestFunc;
	int k;
	int velikost;

	// Constructor
	public Naloga(int velikost, int k) {
		this.velikost = velikost;
		this.k = k;
		podatki = new boolean[velikost]; // Initialize the bit array with false
		MessageDigest tmp;
		try {
			tmp = java.security.MessageDigest.getInstance(hashName);
		} catch (NoSuchAlgorithmException e) {
			tmp = null;
		}
		digestFunc = tmp;
	}

	// Clear method to reset the filter
	public void clear() {
		for (int i = 0; i < podatki.length; i++) {
			podatki[i] = false; // Set each bit to false manually
		}
	}

	// Add method to add an element to the filter
	public void add(String input) {
		byte[] inputData = input.getBytes(); // Convert the input string to bytes
		int[] positions = createHashes(inputData, k); // Get the hash positions

		// Set the positions to true in the bit array
		for (int position : positions) {
			podatki[position] = true;
		}
	}

	// Contains method to check if an element is in the filter
	public boolean contains(String input) {
		byte[] inputData = input.getBytes(); // Convert the input string to bytes
		int[] positions = createHashes(inputData, k); // Get the hash positions

		// Check if all the hash positions are true
		for (int position : positions) {
			if (!podatki[position]) {
				return false; // If any position is false, the element is not in the set
			}
		}
		return true; // All positions are true, so the element might be in the set
	}

	// Create hash positions based on the data and number of hash functions
	public int[] createHashes(byte[] data, int hashes) {
		int[] result = new int[hashes];
		int k = 0;

		// Loop to create k hash positions
		while (k < hashes) {
			byte[] digest = digestFunc.digest(data); // Get the MD5 hash

			// Create hash positions and ensure they fit within the bit array size
			for (int i = 0, j = 0; i < digest.length && k < hashes; i += 2, j++) {
				result[j] = Math.abs(((int) digest[i] << 8) | ((int) digest[i + 1] & 0xFF)) % velikost;
				k++;
			}
		}
		return result;
	}
}
