package analyzer;

import java.io.IOException;

import it.unimi.dsi.webgraph.ImmutableGraph;
import it.unimi.dsi.webgraph.algo.HyperBall;
import it.unimi.dsi.webgraph.algo.SumSweepUndirectedDiameterRadius;

public class Measures {
	
	public static int diameter(ImmutableGraph graph) {
		SumSweepUndirectedDiameterRadius dr = new SumSweepUndirectedDiameterRadius(graph, 
		SumSweepUndirectedDiameterRadius.OutputLevel.DIAMETER, null);
		dr.compute();
		return dr.getDiameter();
	}
	
	public static double[] approximateNeighborhoodFunction(ImmutableGraph graph, long upperBound) throws IOException {
		HyperBall hb = new HyperBall(graph, 7, null);
		hb.run(upperBound);
		hb.close();
		return hb.neighbourhoodFunction.toDoubleArray();
	}
	
}
