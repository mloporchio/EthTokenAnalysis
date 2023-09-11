package builder;

import it.unimi.dsi.webgraph.BVGraph;

public class GraphBuilder {

	public static void main(String[] args) {
		if (args.length < 2) {
			System.err.println("GraphBuilder <inputFile> <outputPrefix>");
			System.exit(1);
		}
		final String inputFile = args[0];
		final String outputPrefix = args[1];
		try {
			BVGraph.main(("-g ArcListASCIIGraph " + inputFile + " " + outputPrefix).split(" "));
		}
		catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

}
