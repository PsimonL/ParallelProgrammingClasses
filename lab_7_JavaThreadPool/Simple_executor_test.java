import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class Simple_executor_test {
	static List<Future<Double>> list = new ArrayList<Future<Double>>();
	private static final int NTHREADS = 10;
	static double finalResult;

	public static void main(String[] args) throws ExecutionException, InterruptedException {

		Counter counter = new Counter();
		ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);

		// [0, PI] dla sin(x)
		double xk = 0;
		double xp = Math.PI;
		double dx = 0.00000001;
		Calka_callable obj = new Calka_callable(xk, xp, dx, 0);
		obj.compute_integral();
		Calka_callable.threadSum = 0;


		for (int i = 0; i < NTHREADS; i++) {
			xp = i * Math.PI/NTHREADS;
			Callable worker = new Calka_callable(xp, xp + Math.PI/10, dx, i);
			Future<Double> temp = executor.submit(worker);
			list.add(temp);
		}

		for (Future<Double> el : list) {
			finalResult += el.get();
		}


		// This will make the executor accept no new threads
		// and finish all existing threads in the queue
		executor.shutdown();



		// Wait until all threads finish
		while(!executor.isTerminated()) {}

		System.out.println("Finished all threads");
// System.out.format("\nCounter_1: %d, Counter_2 %d\n\n", counter.get_c1(), counter.get_c2());

		System.out.println();

		System.out.println("Integral_Thread = " + finalResult);
	}
}
