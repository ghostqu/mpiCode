public class Prime {
    int size;
    public Prime(int s) {
	size = s ;
    }
    public int count() {
	int count = 0;
	int[] arr = new int[size + 1];
	arr[1] = 1;
	arr[0] = 1; //0, 1 are not prime number
	for(int i = 2; i < size + 1; i++) {
	    if(arr[i] == 0) // if i is a prime
		for(int j = i * i; j < size + 1; j += i) {
		    arr[j] = 1;
		}
	}
	for(int i = 0; i < size + 1; i++) {
	    if(arr[i] == 0) {
		 count++; // if arr[i] == 0 i is a prime
		 System.out.print(i + " ");
	    }
	}
	System.out.println();
	return count;
    }
    public static void main(String... arg) {
	Prime p = new Prime(20);
	p.count();
    }
}

