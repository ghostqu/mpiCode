public class Prime2 {
    public static void main(String... arg) {
	int limit = 20;
	int[] arr = new int[limit + 1];
	int count = 0;
	for(int i = 2; i <= limit; i++) {
	    if(arr[i] == 0) {
		for(int j = i * i; j <= limit; j += i)
		    arr[j] = 1;
	    }
	}
	for(int i = 2; i <= limit; i++) {
	    if(arr[i] == 0) System.out.print(i + " ");
	}
	System.out.println();
    }
}
