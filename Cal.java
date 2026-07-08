import java.util.Scanner;

public class Cal{

	public static void main(String args[]){

		Scanner sc  = new Scanner(System.in);
		System.out.println("Enter Equation : ");
		String str = sc.nextLine();
		str = str.replaceAll(" ","");
		String[] a = str.split("[\\+\\-\\*\\/\\%]",2);
		if (a.length < 2) {
			System.out.print("Enter correct expression (Eg: 2 + 2)");
			return;
		}
		String oper = String.valueOf(str.charAt(a[0].length()));
		int A = Integer.parseInt(a[0]);
		int B = Integer.parseInt(a[1]);
		switch(oper){
			case "+" :
				System.out.print("Result  : " + (A + B));
				break;

			case "-" :
				System.out.print("Result : "+(A - B));
				break;


			case "*" :
				System.out.print("Result : "+(A * B));
				break;
			case "/":
				System.out.print("Result : "+(A / B));
				break;
			case "%" :
				
				System.out.print("Result : "+(A % B));
				break;
			default  : 
				System.out.print("Kindlt choose the available operators : + - * / % ");
				break;
			}



	}
}
