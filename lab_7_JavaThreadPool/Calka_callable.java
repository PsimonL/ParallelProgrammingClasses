import java.util.concurrent.Callable;


//public class Calka_callable implements Callable<Double>{
public class Calka_callable implements Callable<Double>{

	private double dx;
	private double xp;
	private double xk;
	private int N;
	public static double threadSum;
	public double sequenceSum;

	private static Object lock = new Object();
	public Calka_callable(double xp, double xk, double dx, int i) {
		this.xp = xp;
		this.xk = xk;
		this.N = (int) Math.ceil((xk-xp)/dx);
		this.dx = (xk-xp)/N;
		System.out.println(i + " Creating an instance of Calka_callable");
		System.out.println("xp = " + xp + ", xk = " + xk + ", N = " + N);
		System.out.println("dx requested = " + dx + ", dx final = " + this.dx);
	}

	private double getFunction(double x) {
		return Math.sin(x);
	}

	public double compute_integral() {
		double calka = 0;
		int i;
		for(i=0; i<N; i++){
			double x1 = xp+i*dx;
			double x2 = x1+dx;
			calka += ((getFunction(x1) + getFunction(x2))/2.)*dx;
		}
		System.out.println("Calka czastkowa: " + calka);
		sequenceSum += calka;
		return calka;
	}

	public double dispaly(){
		return this.compute_integral();
	}

	@Override
	public Double call() throws Exception {
		double integral = compute_integral();
		synchronized (lock){
			threadSum += integral;
		}
		return integral;
	}
}
