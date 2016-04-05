import java.util.Scanner;

public class Eingabe2{
	public static void main(String[] args){
		
		Scanner Tastatur = new Scanner(System.in); 
		
		
	
		System.out.println("Geben Sie bitte eine Zahl");
		int gZahl1 = Tastatur.nextInt (); 

		System.out.println(" Noch eine Zahl, bitte! Ich kann nicht nur 1 Zahl vergleichen ! ");
		int gZahl2 = Tastatur.nextInt ();
	
		if(gZahl1>gZahl2){
		System.out.println("Die Zahl " + gZahl1 + " ist größer als" + gZahl2 );
		}
		if(gZahl1<gZahl2) {
		System.out.println("Die Zahl " + gZahl1 + " ist kleiner als " + gZahl2 );
		}
	}
}
