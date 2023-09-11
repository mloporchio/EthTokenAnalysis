package analyzer;

import java.io.PrintWriter;

import it.unimi.dsi.webgraph.ImmutableGraph;
import it.unimi.dsi.webgraph.Transform;
import it.unimi.dsi.webgraph.algo.ConnectedComponents;
import it.unimi.dsi.webgraph.algo.NeighbourhoodFunction;

public class PathAnalyzer {

	public static void main(String[] args) throws Exception {
		if (args.length < 2) {
			System.err.println("PathAnalyzer <inputPrefix> <outputFile>");
			System.exit(1);
		}
		final String inputPrefix = args[0];
		final String outputFile = args[1];
		long start = System.nanoTime();
		
		// Open the output file.
		PrintWriter out = new PrintWriter(outputFile);
			
		// Load the graph.
		ImmutableGraph graph = ImmutableGraph.load(inputPrefix);
		// Simplify the graph (makes the graph undirected and removes self-loops).
		ImmutableGraph graphS = Transform.simplify(graph, Transform.transpose(graph)); 
		
		// Compute the largest connected component.
		ImmutableGraph comp = ConnectedComponents.getLargestComponent(graphS, 0, null);		
	
		// Compute the diameter of the component.
		int diameter = Measures.diameter(comp);
		// Compute the approximate neighborhood function using HyperBall.
		double[] nf = Measures.approximateNeighborhoodFunction(comp, diameter);
		// Then, use it to estimate the average shortest path length.
		double estLength = NeighbourhoodFunction.averageDistance(nf);
		// Write the computed neighborhood function to the output file.
		for (int i = 0; i < nf.length; i++) out.printf("%.6f\n", nf[i]);
		out.close();
		
		// Print the results.
		long elapsed = System.nanoTime() - start;
		System.out.printf("%d\t%.6f\t%d\n", diameter, estLength, elapsed);
	}
}
